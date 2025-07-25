#include "BMI088.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "Adafruit_BMP3XX.h"
#include <utility/imumaths.h>
#include <cmath>
#include <Servo.h>
#include <SPI.h>
#include <SD.h>
#define SEALEVELPRESSURE_HPA (1016.8)
enum RocketState {
  BOOT,
  CALIBRATION,
  POSTCALIBRATION,
  ARMED,
  ASCENT,
  DESCENT,
  RETROBURN,
  LANDED
};
volatile bool newdata = false;
volatile bool reading = false;
volatile double loggedAlt = 0;
volatile double loggedAccelAlt = 0;
volatile double loggedOrientationY = 0;
volatile double loggedOrientationZ = 0;
volatile double loggedBaroAlt = 0;
volatile double loggedAccel = 0;
volatile int loggedState = 0;

const int _MISO = 20;
const int _MOSI = 19;
const int _CS = 17;
const int _SCK = 18;
Adafruit_BMP3XX bmp;
RocketState state;
Bmi088Accel accel(Wire,0x19);
Bmi088Gyro gyro(Wire,0x69);
Servo innerServo;
Servo outerServo;
int cycleCounter;
double prevtime;
double curtime;
double deltatime;
double gyroFilter; 
double perSecToMicros;
double gyroOffsetX;
double gyroOffsetY;
double gyroOffsetZ;
double baroOffset;
double innerServoOffset;
double outerServoOffset;
double baroAlt;
double verticalVelocity;
double Alt;
double accelAlt;
double G;
double altFilterCoeff;
double kP;
double kD;
double maxAlt;
double landingP;
double landingC;
double PIDXangularvelocity;
double PIDZangularvelocity;
double Xangularvelocitysum[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
double Zangularvelocitysum[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
double zGimbalTarget;
double yGimbalTarget;
double mass;
double thrust;
int launchTimeoutTimer;
int LED1;
int LED2;
int pyroFire1;
int pyroSense1;
int caseNum;
File dataFile;
imu::Quaternion quatOrientation;
imu::Vector<3> angularVelocity;
imu::Vector<3> linearAccel;
imu::Vector<3> eulerOrientation;

void logData()
{
  if(!reading)
  {
    loggedAccel = imu::Vector<3>(accel.getAccelZ_mss(),accel.getAccelX_mss(),accel.getAccelY_mss()).magnitude();
    loggedOrientationY = eulerOrientation.y();
    loggedOrientationZ = eulerOrientation.z();
    loggedAlt = Alt;
    loggedAccelAlt = accelAlt;
    loggedBaroAlt = baroAlt;
    loggedState = caseNum;
    newdata = true;
  }
}
void testPyro()
{
  if(digitalRead(pyroSense1) == HIGH)
  {
    return;
  }
  else
  {
    while(true)
    {
      digitalWrite(LED1, HIGH);
      delay(250);
      digitalWrite(LED1, LOW);
      delay(250);
    }
  }
}

void firePyro()
{
  digitalWrite(pyroFire1, HIGH);
}

void outerServoPos(double gimbalAngle)
{
  outerServoOffset = 86;
  if(gimbalAngle > 5)
  {
    gimbalAngle = 5;
  }
  if(gimbalAngle < -5)
  {
    gimbalAngle = -5;
  }
  outerServo.write(outerServoOffset - 1.42857*((-0.0854554) * pow(gimbalAngle,2) + (3.93881) * gimbalAngle));
}

void innerServoPos(double gimbalAngle)
{
  innerServoOffset = 94;
  if(gimbalAngle > 5)
  {
    gimbalAngle = 5;
  }
  if(gimbalAngle < -5)
  {
    gimbalAngle = -5;
  }
  innerServo.write(innerServoOffset + 1.42857*((0.0715056) * pow(gimbalAngle,2) + (4.22752) * gimbalAngle));
}

void calibrateAccel()
{
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  accel.readSensor();
  for(int i = 0; i < 1000; i++)
  {
    G += accel.getAccelY_mss();
  }
  G /= 1000.0;
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
}

void calibrateBaro()
{
  bmp.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_100_HZ);
  bmp.prepareReading();
  baroOffset += bmp.readAltitude(SEALEVELPRESSURE_HPA);
  bmp.prepareReading();
  delay(6);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  for(int i = 0; i < 1000; i++)
  {
    baroOffset += bmp.readAltitude(SEALEVELPRESSURE_HPA);
    bmp.prepareReading();
  }
  baroOffset /= 1000.0;
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
  Serial.println(baroOffset);
}

void calibrateGyro()
{
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  for(int i = 0; i < 1000; i++)
  {
    gyro.readSensor();
    gyroOffsetX += gyro.getGyroX_rads();
    gyroOffsetY += gyro.getGyroY_rads();
    gyroOffsetZ += gyro.getGyroZ_rads();
  }
  gyroOffsetX /= 1000.0;
  gyroOffsetY /= 1000.0;
  gyroOffsetZ /= 1000.0;
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
}

void integrateForOrientation()
{
  gyro.readSensor();
  angularVelocity = imu::Vector<3>(gyro.getGyroX_rads()-gyroOffsetX,gyro.getGyroY_rads()-gyroOffsetY,gyro.getGyroZ_rads()-gyroOffsetZ);
  angularVelocity = angularVelocity*perSecToMicros;
  double AVL = sqrt(pow(angularVelocity.x(),2)+pow(angularVelocity.y(),2)+pow(angularVelocity.z(),2));
  double mult = AVL*deltatime/2.0;
  double smult = sin(mult);
  if(AVL > gyroFilter){
    double Qw = cos(mult);
    double Qx = smult*(angularVelocity.z()/AVL);
    double Qy = smult*(angularVelocity.x()/AVL);
    double Qz = smult*(angularVelocity.y()/AVL);
    imu::Quaternion quat = imu::Quaternion(Qw,Qx,Qy,Qz);
    quatOrientation = quatOrientation * quat;
    quatOrientation.normalize();
  }
  for(int i = 0; i<4; i++)
  {
    Xangularvelocitysum[i] = Xangularvelocitysum[i+1];
    Zangularvelocitysum[i] = Zangularvelocitysum[i+1];
  }
  Xangularvelocitysum[4] = gyro.getGyroX_rads();
  Zangularvelocitysum[4] = gyro.getGyroZ_rads();
  PIDXangularvelocity = 0;
  PIDZangularvelocity = 0;
  for(int i = 0; i<5; i++)
  {
    PIDXangularvelocity += Xangularvelocitysum[i];
    PIDZangularvelocity += Zangularvelocitysum[i];
  }
  PIDXangularvelocity /= 5;
  PIDZangularvelocity /= 5; 
}

void integrateForAltitude()
{
  accel.readSensor();
  linearAccel = imu::Vector<3>(accel.getAccelZ_mss(),accel.getAccelX_mss(),accel.getAccelY_mss());
  linearAccel = quatOrientation.rotateVector(linearAccel);
  linearAccel.z() -= G;
  linearAccel = linearAccel * perSecToMicros;
  verticalVelocity += linearAccel.z() * deltatime;
  if(cycleCounter==10)
      {
        baroAlt=bmp.readAltitude(SEALEVELPRESSURE_HPA) - baroOffset;
        bmp.prepareReading();
        cycleCounter = 0;
      }
      else 
      {
        cycleCounter ++;
      }
  Alt = altFilterCoeff*(Alt + verticalVelocity * deltatime * perSecToMicros) + (1-altFilterCoeff)*(baroAlt);
  accelAlt += verticalVelocity * deltatime * perSecToMicros;
  /*Serial.print(Alt,6);
  Serial.print(" ");
  Serial.print(baroAlt,6);
  Serial.print(" ");
  Serial.print(verticalVelocity);
  Serial.print(" ");
  Serial.println();*/
}

void runPID()
{
  thrust = imu::Vector<3>(accel.getAccelZ_mss(),accel.getAccelX_mss(),accel.getAccelY_mss()).magnitude();
  thrust = thrust/mass;
  if(thrust>30)
  {
    thrust = 30;
  }
  eulerOrientation = quatOrientation.toEuler();
  eulerOrientation.toDegrees();
  zGimbalTarget = (kP * eulerOrientation.z() + kD * (PIDZangularvelocity) * (180.0/3.14159))/thrust;
  yGimbalTarget = (-kP * eulerOrientation.y() - kD * (PIDXangularvelocity) * (180.0/3.14159))/thrust;
  outerServoPos(zGimbalTarget);
  innerServoPos(yGimbalTarget);
}

void timeStep()
{
  curtime = micros();
  deltatime = (curtime-prevtime);
  prevtime = curtime;
}

void startSensors()
{
  bool baroTest = bmp.begin_I2C(0x77, &Wire1);
  int status;
  status = accel.begin();
  if (status < 0) {
    Serial.println("Accel Initialization Error");
    Serial.println(status);
  }
  status = gyro.begin();
  if (status < 0) {
    Serial.println("Gyro Initialization Error");
    Serial.println(status);
  }
  while(status<0||!baroTest)
  {
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW); 
    delay(250);
    digitalWrite(LED2, LOW);
    digitalWrite(LED1, HIGH);
    delay(250); 
  }
  bmp.prepareReading();
}

void setup() {
  //Serial.begin(115200);
  //while(!Serial) {}
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  innerServo.attach(14);
  outerServo.attach(4);
  launchTimeoutTimer = 0;
  kP = 7;
  kD = 2.5;
  zGimbalTarget = 0;
  yGimbalTarget = 0;
  cycleCounter = 0;
  maxAlt = 0;
  landingP = 0.644994;
  landingC = 1.0081;
  LED1 = 22;
  LED2 = 23;
  pyroFire1 = 9;
  pyroSense1 = 11;
  gyroOffsetX = 0;
  gyroOffsetY = 0;
  gyroOffsetZ = 0;
  baroOffset = 0;
  thrust = 0;
  altFilterCoeff = 0.94;
  baroAlt = 0;
  mass = 0.867;
  accelAlt = 0;
  gyroFilter = 1 * pow(10,-13);
  perSecToMicros = 0.000001;
  linearAccel = imu::Vector<3>(0,0,0);
  quatOrientation = imu::Quaternion(1,0,0,0);
  eulerOrientation = imu::Vector<3>(0,0,0);
  verticalVelocity = 0;
  Alt = 0;
  caseNum = 1;
  state = BOOT;
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(pyroFire1, OUTPUT);
  pinMode(pyroSense1, INPUT);
}

void loop() {
  timeStep();
  switch(state)
  {
    case (BOOT): 
    {
      testPyro();
      startSensors();
      state = CALIBRATION;
      caseNum = 2;
      break;
    }
    case (CALIBRATION):
    {
      delay(50000);
      calibrateAccel();
      calibrateBaro();
      calibrateGyro();
      state = POSTCALIBRATION;
      caseNum = 3;
      break;
    }
    case (POSTCALIBRATION):
    { 
      state = ARMED;
      caseNum = 4;
      break;
    }
    case (ARMED):
    {
      integrateForOrientation();
      integrateForAltitude();
      runPID();
      logData();
      if(13 < loggedAccel)
      {
        digitalWrite(LED2, HIGH);
        launchTimeoutTimer = millis();
        state = ASCENT;
        caseNum = 5;
      }
      break;
    }
    case (ASCENT):
    {
      integrateForOrientation();
      integrateForAltitude();
      runPID();
      logData();
      if(Alt>maxAlt)
      {
        maxAlt=Alt;
      }
      if((millis()-launchTimeoutTimer)>1800)
      {
        state = DESCENT;
        caseNum = 6;
      }
      break;
    }
    case (DESCENT):
    {
      integrateForOrientation();
      integrateForAltitude();
      runPID();
      logData();
      if(Alt>maxAlt)
      {
        maxAlt=Alt;
      }
      if(Alt<(landingP*maxAlt+landingC)&&Alt>3.5)
      {
        firePyro();
        state = RETROBURN;
        caseNum = 7;
      }
      break;
    }
    case (RETROBURN):
    {
      integrateForOrientation();
      integrateForAltitude();
      runPID();
      logData();
      break;
    }
    case (LANDED):
    {
      break;
    }
  }

}

void setup1(){
  bool sdInitialized = false;
  SPI.setRX(_MISO);
  SPI.setTX(_MOSI);
  SPI.setSCK(_SCK);
  sdInitialized = SD.begin(_CS);
  File dataFile = SD.open("datalog.csv", FILE_WRITE);
  dataFile.println("\"Case\",\"Alt\",\"BaroAlt\",\"AccelAlt\",\"Pitch\",\"Yaw\",\"AccelMag\",\"Time(millis)\"");
  dataFile.close();
}
void loop1(){
  if(newdata)
  {
    reading = true;
    newdata = false;
    File dataFile = SD.open("datalog.csv", FILE_WRITE);
    dataFile.print("\"");
    dataFile.print(loggedState);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedAlt);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedBaroAlt);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedAccelAlt);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedOrientationY);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedOrientationZ);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(loggedAccel);
    dataFile.print("\",");
    dataFile.print("\"");
    dataFile.print(millis());
    dataFile.println("\"");
    dataFile.close();
    reading = false;
  }
}
