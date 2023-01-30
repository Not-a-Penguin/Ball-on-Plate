//#include <Arduino.h>
#include "touchScreen.h"
#include "servoControl.h"

//TODO: implement indicator to see actual sampling interval 
//TODO: implement self-calibration for screen at startup to set servo start position

//instantiate servo control. Attach is done inside constructor
ServoControl servos(24, 25, 26);


//Pins in the order: upperLeft upperRight lowerLeft lowerRight sensorPin. Internally the library will set the pinMode accordingly.
TouchScreen screen(27, 26, 32, 33, 25);


//struct where the coordinate is returned
//The srtuct is defined in the touchScreen library
screenCoordinates coordinates;

void setup(){
  //Initialize serial connection
  Serial.begin(115200);

  //Optionally, move servos to a predetermined start position
  servos.startPosition(90, 90, 90);
  //screen.setScreenDelay(30); 
  
}

void loop(){
  
  /*
   * In order to get the current value of the xy pair of coordinates
   * you simply run the getCoordinates(); in the loop without any delays
   * because internally the function only does the reading operation every n milliseconds 
   * wich by default is 30 but can be changed with setScreenDelay(int milliseconds)
   * 
   * the return of getCoordinates is a struct with 2 elements: screen.x and screen.y
   * 
   */
   coordinates = screen.getCoordinates();
   //after calling the function the coordinate.x and coordinate.y will be populated with the current reading

  Serial.print("x:");
  Serial.print(coordinates.x);
  Serial.print(",");
  Serial.print("y:");
  Serial.println(coordinates.y);
  // sendXYData(x, y); */
}
