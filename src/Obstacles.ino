#include <Wire.h>
#include <Servo.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(13, 12); // RX, TX

Servo myServo;  // create servo object to control a servo

void setup() {
  // Begin serial communication
  Serial.begin(115200);
  mySerial.begin(9600);
  Wire.begin();
  // Attach the servo on pin 2 to the servo object
  myServo.attach(2);
  // Initialize HuskyLens
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("HUSKYLENS Not Detected! Please Check the Connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
}

int xAxis = 0;
int yAxis = 0;
int ID = -1;

void loop() {
  while(huskylens.requestBlocks()){
    HUSKYLENSResult result = huskylens.read();

    xAxis = result.xCenter;
    yAxis = result.yCenter;
    ID = result.ID;
    Serial.println(ID);
    
    if(ID == -1){
      myServo.write(90);
      Serial.println("I see nothing"); 
    }
    else if(ID == 1){
      myServo.write(60);
      Serial.println("I see Red"); 
    }
    else if(ID == 2){
      myServo.write(120);
      Serial.println("I see Green"); 
    }
    delay(500);
   }
  Serial.println("End Loop");
}

//  if (!huskylens.request()) return;
//
//  // If a green object (ID 2) is detected, steer away to the left
//  // If a red object (ID 1) is detected, steer away to the right
//  if (huskylens.isLearned()) {
//    HUSKYLENSResult result = huskylens.read();
//    if (result.ID == 2) {
//      int xAxis = result.xCenter;
//      int yAxis = result.xCenter;
//      int distance = result.xCenter;
//      while(xAxis > 140){
//        Serial.println("ys");
//        myServo.write(60);  // adjust the angle as needed
//      }
//    }
//    }
//    if (result.ID == 1) {
//      while (result.ID == 1) {
//        int xAxis = result.xCenter;
//        int yAxis = result.xCenter;
//        int distance = result.xCenter;
//        while(xAxis > 140){
//          Serial.println("ys");
//          myServo.write(60);  // adjust the angle as needed
//        }
//      }
//    }
//  }
//  else{
//    // No red or green object - move straight
//    myServo.write(90);  // adjust the angle as needed
//  }
//}
//}



//void printResult(HUSKYLENSResult result){
//  if (result.command == COMMAND_RETURN_BLOCK){
//    Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
//  }
//  else if (result.command == COMMAND_RETURN_ARROW){
//    Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
//  }
//  else{
//    Serial.println("Object unknown!");
//  }
//}
