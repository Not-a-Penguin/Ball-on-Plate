#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include "ESP32Servo.h"
#include <Arduino.h>

class ServoControl{

  public:
    ServoControl(int servoPin1, int servoPin2, int servoPin3);
    ~ServoControl();
    void attachServos();
    void startPosition(int startPositionServo1, int startPositionServo2, int startPositionServo3);
    void moveServo(String servo, int angle);

  private:
    Servo servo1;
    Servo servo2;
    Servo servo3;   
};
#endif