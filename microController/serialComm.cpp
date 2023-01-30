#include "serialComm.h"

SerialComm::SerialComm() {};

SerialComm::~SerialComm(){};

void SerialComm::sendJson(String xValue, String yValue){
  StaticJsonDocument<64> doc;
  doc["xValue"] = xValue;
  doc["yValue"] = yValue;
  serializeJson(doc, Serial); 
  Serial.println();
};

void SerialComm::getJson(){
  if (Serial.available() > 2) {

    DeserializationError err = deserializeJson(this->jsonFromSerial, Serial);
    
    if (err == DeserializationError::Ok){
      this->jsonUpdated = 1;
    }

    else {
      while (Serial.available() > 0){
        Serial.read();
      };
    }
  }
};