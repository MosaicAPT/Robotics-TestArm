#pragma once
#include <pigpio.h>
#include <pigpiod_if2.h>
#include <thread>
#include <chrono>

class MotorController
{
    private:
    public:
        unsigned int pulseWidth; // 0-2000ms 
        MotorController();
        
};