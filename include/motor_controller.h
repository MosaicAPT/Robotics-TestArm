#pragma once
#include <pigpio.h>
#include <pigpiod_if2.h>
#include <thread>
#include <chrono>
#include "motor.h"

class MotorController
{
    private:
    public:
        unsigned int pulseWidth; // 0-2000ms 
        MotorController();
        
};