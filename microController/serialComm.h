#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

#include <ArduinoJson.h>
#include <Arduino.h>

class SerialComm{
  
  private:

  public:
    SerialComm();
    ~SerialComm();

    StaticJsonDocument<128> jsonFromSerial;

    int jsonUpdated = 0;
    
    void getJson();
    void sendJson(String xValue, String yValue);
};

#endif