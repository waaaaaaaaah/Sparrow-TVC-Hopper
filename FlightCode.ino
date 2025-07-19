#include "BMI088.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include "Adafruit_BMP3XX.h"
#include <utility/imumaths.h>
#include <cmath>
#define SEALEVELPRESSURE_HPA (1016.8)
enum RocketState {
  BOOT,
  PRECALIBRATION,
  CALIBRATION,
  POSTCALIBRATION,
  ARMED,
  ASCENT,
  DESCENT,
  RETROBURN,
  LANDED
};
Adafruit_BMP3XX bmp;
RocketState state;
Bmi088Accel accel(Wire,0x19);
Bmi088Gyro gyro(Wire,0x69);
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
double baroAlt;
double verticalVelocity;
double Alt;
double accelAlt;
double G;
int LED1;
int LED2;
imu::Quaternion quatOrientation;
imu::Vector<3> angularVelocity;
imu::Vector<3> linearAccel;

void calibrateAccel()
{
  digitalWrite(LED2, HIGH);
  digitalWrite(LED1, HIGH);
  accel.readSensor();
  for(int i = 0; i < 1000; i++)
  {
    G += accel.getAccelY_mss();
  }
  G /= 1000;
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
  baroOffset /= 1000;
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
  gyroOffsetX /= 1000;
  gyroOffsetY /= 1000;
  gyroOffsetZ /= 1000;
  digitalWrite(LED2, LOW);
  digitalWrite(LED1, LOW);
}

void integrateForOrientation()
{
  gyro.readSensor();
  angularVelocity = imu::Vector<3>(gyro.getGyroX_rads()-gyroOffsetX,gyro.getGyroY_rads()-gyroOffsetY,gyro.getGyroZ_rads()-gyroOffsetZ);
  angularVelocity = angularVelocity*perSecToMicros;
  double AVL = sqrt(pow(angularVelocity.x(),2)+pow(angularVelocity.y(),2)+pow(angularVelocity.z(),2));
  double mult = AVL*deltatime/2;
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
}

void integrateForAltitude()
{s
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
  Alt = 0.98*(Alt + verticalVelocity * deltatime * perSecToMicros) + 0.02*(baroAlt);
  accelAlt += verticalVelocity * deltatime * perSecToMicros;
 /* if(Alt<0)
  {
    Alt = 0;
    verticalVelocity = 0;
  }*/
  Serial.print(Alt,6);
  Serial.print(" ");
  Serial.print(baroAlt,6);
  Serial.print(" ");
  Serial.print(verticalVelocity);
  Serial.print(" ");
  Serial.print(deltatime);
  Serial.print(" ");
  Serial.println();
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
  Serial.begin(115200);
  while(!Serial) {}
  Wire.setSDA(0);
  Wire.setSCL(1);
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  cycleCounter = 0;
  LED1 = 22;
  LED2 = 23;
  gyroOffsetX = 0;
  gyroOffsetY = 0;
  gyroOffsetZ = 0;
  baroOffset = 0;
  baroAlt = 0;
  accelAlt = 0;
  gyroFilter = 1 * pow(10,-13);
  perSecToMicros = 0.000001;
  linearAccel = imu::Vector<3>(0,0,0);
  quatOrientation = imu::Quaternion(1,0,0,0);
  verticalVelocity = 0;
  Alt = 0;
  state = BOOT;
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  timeStep();
  switch(state)
  {
    case (BOOT): 
    {
      startSensors();
      state = CALIBRATION;
      break;
    }
    case (PRECALIBRATION)://wait for a good chunk of time or something
    {
      break;
    }
    case (CALIBRATION):
    {
      //delay(5000);
      calibrateAccel();
      calibrateBaro();
      calibrateGyro();
      state = POSTCALIBRATION;
      break;
    }
    case (POSTCALIBRATION):
    {   
      state = ARMED;
      break;
    }
    case (ARMED):
    {
      //bmp.performReading();
      integrateForOrientation();
      integrateForAltitude();
      imu::Vector<3> billy = quatOrientation.toEuler();
      billy.toDegrees();
      /*Serial.print(billy.x());
      Serial.print(" ");
      Serial.print(billy.y());
      Serial.print(" ");
      Serial.print(billy.z());
      Serial.print(" ");
      Serial.println(deltatime/1000);*/
      /*Serial.print(quatOrientation.w());
      Serial.print(" ");
      Serial.print(quatOrientation.x());
      Serial.print(" ");
      Serial.print(quatOrientation.y());
      Serial.print(" ");
      Serial.print(quatOrientation.z());
      Serial.print(" ");
      Serial.println(deltatime/1000);*/
      break;
    }
    case (ASCENT):
    {
      break;
    }
    case (DESCENT):
    {
      break;
    }
    case (RETROBURN):
    {
      break;
    }
    case (LANDED):
    {
      break;
    }
  }

}
