#include <Arduino.h>
#include "touchScreen.h"

TouchScreen::TouchScreen(int upperLeft, int upperRight, int lowerLeft, int lowerRight, int sensorPin){

  //Set the pins according to the corners of the screen
  this->_upperLeftPin = upperLeft;
  this->_upperRightPin = upperRight;
  
  this->_lowerLeftPin = lowerLeft;
  this->_lowerRightPin = lowerRight;

  this->_sensorPin = sensorPin;

  this->setPins();
  
};

TouchScreen::~TouchScreen(){/* 
  (づ｡◕‿‿◕｡)づ no destructor
*/}

screenCoordinates TouchScreen::getCoordinates(){ 

  this->_currentScreenCoordinates.x = this->readCoordinate("x");
  this->_currentScreenCoordinates.y = this->readCoordinate("y");
  this->_newReading = true;

  return this->_currentScreenCoordinates; 
};

int TouchScreen::readCoordinate(String coordinate){

  /*  
   *  In order to read the coordinates, the corners of the screen must be set to HIGH or LOW 
   *  in a certain way to create a voltage gradient across the screen, then when a touch occurs
   *  and the voltage divider is made, the voltage across that gradient with change and can be read
   *  with the middle pin.
   *  
   *  The corner signals are explained in the table bellow
   *   
   *  ______________________________________________________________________
   * |  function      | upper-left | lower-left | upper-right | lower-right |
   * |read x-position |     Vss    |    Vss     |      Vdd    |     Vdd     |
   * |read y-position |     Vss    |    Vdd     |      Vss    |     Vdd     |
   * |______________________________________________________________________|
   */
   
  if(coordinate == "x"){
    digitalWrite(this->_lowerLeftPin, HIGH);
    digitalWrite(this->_upperRightPin, LOW);
  }
  
  else if(coordinate == "y"){
    digitalWrite(this->_lowerLeftPin, LOW);
    digitalWrite(this->_upperRightPin, HIGH); 
  }
  
  delay(this->_interval);
  return analogRead(this->_sensorPin);
};

screenCoordinatesCm TouchScreen::getCoordinatesCm(float xValue, float yValue){

  this->_currentScreenCoordiantesCm.xCm = 1.6298789841486278e-002 * xValue - 3.0054968467700697e+001 + 0.4;
  this->_currentScreenCoordiantesCm.yCm = 1.2133349039934032e-002 * yValue - 2.4024031099069383e+001 + 0.2 ;

  return this->_currentScreenCoordiantesCm;
  
};

bool TouchScreen::screenUpdated(){
  if(this->_newReading == true){
    this->_newReading = false;
    return true;
  } else return false;
}

void TouchScreen::setSamplingTime(int milliseconds){
  this->_interval = milliseconds >> 1;  
};

void TouchScreen::setPins(){

  //All corner pins are output
  pinMode(this->_upperLeftPin, OUTPUT);
  pinMode(this->_upperRightPin, OUTPUT);
  
  pinMode(this->_lowerLeftPin, OUTPUT);
  pinMode(this->_lowerRightPin, OUTPUT);

  pinMode(this->_sensorPin, INPUT);  

  digitalWrite(this->_upperLeftPin, HIGH);
  digitalWrite(this->_lowerRightPin, LOW);
};
