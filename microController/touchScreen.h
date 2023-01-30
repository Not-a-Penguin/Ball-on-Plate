#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

/*
 * Library for interfacing with a 5-wire resistive touchScreen. 
 */

//definition of struct where the current values of x and y will be stored:
struct screenCoordinates{
  int x = 0;
  int y = 0;  
};

class TouchScreen{

  public:

    TouchScreen(int upperLeft, int upperRight, int lowerLeft, int lowerRight, int sensorPin);
    
    ~TouchScreen();
    screenCoordinates getCoordinates();
    void setScreenDelay(int milliseconds);

  private:

    //functions

    //Analog read of specified axis. Also takes care of setting the correct pins HIGH or LOW
    int readCoordinate(String coordinate);
    void alternateReading();
    void setPins();

    //variables
    //flag for whether to read x or y axis
    bool _alternateReading = false;

    //variables for calculating when the screen should be read
    int _interval= 30; //in milliseconds -> can be set in setScreenDelay()
    unsigned long _previousMillis = 0;

    //Struct where current reading is stored. Accessed by the return of getCoordinates()
    screenCoordinates _currentScreenCoordinates;
    
    //Variables for the digital pins corresponding to the four corners of the display.
    int _upperLeftPin;
    int _upperRightPin;
    
    int _lowerLeftPin;
    int _lowerRightPin;

    //ADC
    //The middle pin of the display which corresponds to the analog value of the voltage divider when there
    //is a voltage gradient in the screen
    int _sensorPin; 
};

#endif
