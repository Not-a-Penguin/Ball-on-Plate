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

TouchScreen::~TouchScreen(){/*(づ｡◕‿‿◕｡)づ */}

screenCoordinates TouchScreen::getCoordinates(){ 

  /* 
   *  Since both coordinates can't be read at the same time, the readings are done
   *  alternating between x and y, so every 30 ms a reading of the x axis is made and then
   *  the next reading is for the y axis and x again and then y again and so on and so forth
   */

  screenCoordinates currentCoordinates;
   
  unsigned long currentMillis = millis();
  
  if(currentMillis - this->_previousMillis > this->_interval){

    if(this->_alternateReading){
      this->_currentScreenCoordinates.y = this->readCoordinate("y");  
    }
    
    this->_currentScreenCoordinates.x = this->readCoordinate("x");
    this->alternateReading();
    this->_previousMillis = currentMillis;
  }

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
   *   ______________________________________________________________________
   * |  function      | upper-left | lower-left | upper-right | lower-right |
   * |read x-position |     Vss    |    Vss     |      Vdd    |     Vdd     |
   * |read y-position |     Vss    |    Vdd     |      Vss    |     Vdd     |
   * |______________________________________________________________________|
   */
   
  if(coordinate == "x"){
    digitalWrite(this->_upperLeftPin, HIGH);
    digitalWrite(this->_lowerLeftPin, HIGH);
  
    digitalWrite(this->_upperRightPin, LOW);
    digitalWrite(this->_lowerRightPin, LOW);
  }
  
  else if(coordinate == "y"){
    digitalWrite(this->_upperLeftPin, HIGH);
    digitalWrite(this->_lowerLeftPin, LOW);
  
    digitalWrite(this->_upperRightPin, HIGH);
    digitalWrite(this->_lowerRightPin, LOW);  
  }

  return analogRead(this->_sensorPin);
};

void TouchScreen::setScreenDelay(int milliseconds){
  this->_interval = milliseconds;  
};

void TouchScreen::alternateReading(){
  this->_alternateReading = !this->_alternateReading;  
};

void TouchScreen::setPins(){

  //All corner pins are output
  pinMode(this->_upperLeftPin, OUTPUT);
  pinMode(this->_upperRightPin, OUTPUT);
  
  pinMode(this->_lowerLeftPin, OUTPUT);
  pinMode(this->_lowerRightPin, OUTPUT);

  pinMode(this->_sensorPin, INPUT);  
};
