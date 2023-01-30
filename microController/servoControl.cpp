#include "servoControl.h"

ServoControl::ServoControl(int servoPin1, int servoPin2, int servoPin3){

  Serial.println("Attaching servos");
  this->servo1.attach(servoPin1);
  this->servo2.attach(servoPin2);
  this->servo3.attach(servoPin3);
};

ServoControl::~ServoControl(){/* ¯\_(ツ)_/¯ */};

void ServoControl::startPosition(int startPositionServo1, int startPositionServo2, int startPositionServo3){

  this->moveServo("servo1", startPositionServo1);
  this->moveServo("servo2", startPositionServo2);
  this->moveServo("servo3", startPositionServo3);
};


void ServoControl::moveServo(String servo, int angle){

  if(servo == "1"){
    this->servo1.write(angle);
  }

  if(servo == "2"){
    this->servo2.write(angle);
  }

  if(servo == "3"){
    this->servo3.write(angle);
  }

};