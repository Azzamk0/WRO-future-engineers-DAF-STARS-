
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <RN.h>
#include <Servo.h>


// Define the pin connected to the servo motor
const int servoPin = 2;
Servo Servo1;

RN sensor(15, 14); // create an instance of RN class with trig pin 14 and echo pin 15
RN sensor1(17, 16);
RN sensor2(19, 18);

RN motor(8, 9, 10); // create a new instance of the RN class

int correction = 0;

MPU6050 mpu6050(Wire);
int counter = 0;

long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  Servo1.attach(servoPin);
}


int count = 0; 
int previousAngle = 0;
bool inDeadZone = false;
const int deadZone = 5;  // Dead zone of +/-5 degrees around multiples of 360

void loop() {

  while(count < 6){
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

    motor.setMotorDirection(-1); // rotate the motor in one direction
    motor.setMotorSpeed(200); // set the motor speed to maximum
  
  // Short delay before the next loop iteration.
  delay(50);
}
Servo1.write(95);
motor.stopMotor();
delay(500);
motor.setMotorDirection(-1); // keep the motor direction
motor.setMotorSpeed(200); // Keep the motor speed at maximum
delay(750);
motor.setMotorSpeed(0); 
exit(0);
}
