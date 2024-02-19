#include "controller.h"

Controller::Controller(Matrix<1, systemOrder> gains){
   this->K = gains;
};

Controller::~Controller(){};

float Controller::controlLaw(Matrix<systemOrder,1> currentState){
  
  return (this->K * currentState)(0);
}

void saturate(float* input, float lowerLimit, float upperLimit){
  if(*input < lowerLimit) *input = lowerLimit;
  if(*input > upperLimit) *input = upperLimit;
}
