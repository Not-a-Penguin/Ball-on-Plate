//#include <Arduino.h>
#include "touchScreen.h"
#include "servoControl.h"
#include "serialComm.h"

//TODO: implement indicator to see actual sampling interval 
//TODO: implement self-calibration for screen at startup to set servo start position

//instantiate servo control. Attach is done inside constructor
ServoControl servos(24, 25, 26);

//Pins in the order: upperLeft upperRight lowerLeft lowerRight sensorPin. Internally the library will set the pinMode accordingly.
TouchScreen screen(27, 26, 32, 33, 25);

//instantiate serial comm object
SerialComm serial;

//struct where the coordinate is returned
//The srtuct is defined in the touchScreen library
screenCoordinates coordinates;

void setup(){

  Serial.begin(115200);

  //Optionally, move servos to a predetermined start position
  servos.startPosition(90, 90, 90);
  //screen.setScreenDelay(30); 
  Serial.println("End of setup");
  serial.sendJson("apple", "banana");
  
}

void loop(){
  serial.getJson();
  if(serial.jsonUpdated){
    serial.jsonUpdated = 0;
    int updateServo = serial.jsonFromSerial["updateServo"]; // 1 or 0
    int s1 = serial.jsonFromSerial["s1"]; // 0 to 180 degrees
    int s2 = serial.jsonFromSerial["s2"];  
    int s3 = serial.jsonFromSerial["s3"]; 

    Serial.printf("s1: %i - s2: %i - s3: %i -- updateServo: %i \n\r", s1, s2, s3, updateServo);
  }
  delay(0.5);

}
