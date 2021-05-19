#pragma once 
#include "Arduino.h"
#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include "Constants.h"

class Motor
{
  public:
    int clkPin;
    int cwPin;
    String joint;
    Motor();
    Motor(const int& clkPin, const int& cwPin, const String& joint);
    void MoveMotor(const int& speed, const String& dir);
};