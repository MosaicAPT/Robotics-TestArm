#pragma once
#include <ros.h>

class Motor()
{
  public:
    int clkPin;
    int cwPin;
    String joint;  
    Motor(int clkPin, int cwPin, String joint);
  
}
