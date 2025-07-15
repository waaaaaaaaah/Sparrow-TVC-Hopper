#include "BMI088.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <cmath>
Bmi088Accel accel(Wire,0x19);
Bmi088Gyro gyro(Wire,0x69);
double prevtime;
double curtime;
double deltatime;
double filter; 
imu::Quaternion quatOrientation;
imu::Vector<3> angularVelocity;
imu::Vector<3> linearAccel;
void setup() {
  int status;
  Serial.begin(115200);
  while(!Serial) {}
  Wire.setSDA(0);
  Wire.setSCL(1);
  filter = 1 * pow(10,-13);
  quatOrientation = imu::Quaternion(1,0,0,0);
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
}

void loop() {
  curtime = micros();
  deltatime = (curtime-prevtime);
  prevtime = curtime;
  gyro.readSensor();
  accel.readSensor();
  linearAccel = imu::Vector<3>(accel.getAccelZ_mss(),accel.getAccelX_mss(),accel.getAccelY_mss());
  angularVelocity = imu::Vector<3>(gyro.getGyroX_rads(),gyro.getGyroY_rads(),gyro.getGyroZ_rads());
  angularVelocity = angularVelocity*0.000001;
  double AVL = sqrt(pow(angularVelocity.x(),2)+pow(angularVelocity.y(),2)+pow(angularVelocity.z(),2));
  double mult = AVL*deltatime/2;
  double smult = sin(mult);
  if(AVL > filter){
    double Qw = cos(mult);
    double Qx = smult*(angularVelocity.z()/AVL);
    double Qy = smult*(angularVelocity.x()/AVL);
    double Qz = smult*(angularVelocity.y()/AVL);
    imu::Quaternion quat = imu::Quaternion(Qw,Qx,Qy,Qz);
    quatOrientation = quatOrientation * quat;
    quatOrientation.normalize();
  }
  linearAccel = quatOrientation.rotateVector(linearAccel);
  Serial.print(linearAccel.x());
  Serial.print(" ");
  Serial.print(linearAccel.y());
  Serial.print(" ");
  Serial.print(linearAccel.z());
  Serial.println(" ");


}
