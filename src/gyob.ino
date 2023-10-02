#include <Wire.h>
#include <Servo.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <MPU6050_tockn.h>
#include <RN.h>

HUSKYLENS huskylens;
SoftwareSerial mySerial(13, 12); // RX, TX

const int servoPin = 2;
Servo Servo1;

MPU6050 mpu6050(Wire);

RN sensor(15, 14); // create an instance of RN class with trig pin 14 and echo pin 15
RN sensor1(17, 16);
RN sensor2(19, 18);

RN motor(8, 9, 10); // create a new instance of the RN class


int correction = 0;
int xAxis = 0;
int yAxis = 0;
int ID = -1;
int count = 0; 
int previousAngle = 0;
bool inDeadZone = false;
const int deadZone = 5;  // Dead zone of +/-5 degrees around multiples of 360

void setup() {
  // Begin serial communication
  Serial.begin(115200);
  mySerial.begin(9600);
  Servo1.attach(servoPin);
  // Initialize HuskyLens
    
}

void loop() {
  while (count < 6){
    while(huskylens.requestBlocks()){
      motor.setMotorDirection(-1); // rotate the motor in one direction
      motor.setMotorSpeed(200); // set the motor speed to maximum
    
      HUSKYLENSResult result = huskylens.read();
  
      xAxis = result.xCenter;
      yAxis = result.yCenter;
      ID = result.ID;
      Serial.println(ID);
      
      if(ID == -1){
        float distance2 = sensor2.getDistance();
        mpu6050.update();
        int currentAngle = mpu6050.getGyroAngleZ();
      
        // Calculate the threshold for the next full rotation based on the current count
        int nextRotationThreshold = 360 * (count + 1);
      
        if(previousAngle < (nextRotationThreshold - deadZone) && currentAngle >= (nextRotationThreshold - deadZone)) {
          // If the robot was below the dead zone and has now entered or crossed it, 
          // we set the inDeadZone flag to true.
          inDeadZone = true;
        }
  
        if(inDeadZone && currentAngle >= (nextRotationThreshold + deadZone)) {
          // If the robot was in the dead zone and has now exited it from above, 
          // we increment the count and set the inDeadZone flag to false.
          // This means the robot has made a valid full rotation.
          count++;
          inDeadZone = false;
      }
    
      // Update the previous angle for the next loop iteration.
      previousAngle = currentAngle;
  
      correction = (1.5 * (distance2 - 30) + 90);
      if (correction > 120) {
        correction = 120 ;
      }
      if (correction < 60) {
        correction = 60;
      }
      Servo1.write(correction);
  
      // Short delay before the next loop iteration.
      delay(50);
    }
    else if(ID == 1){
      Servo1.write(60);
      Serial.println("I see Red"); 
    }
    else if(ID == 2){
      Servo1.write(120);
      Serial.println("I see Green"); 
    }
    delay(500);
   }
  Serial.println("End Loop");
  }
  exit(0);
}
