#pragma once
#include <pigpio.h>
#include <pigpiod_if2.h>
#include <thread>
#include <chrono>

class Motor
{
    private:
        int clkPin;
        int cwPin;
        std::string joint;
    public:
        Motor(const int& clk, const int& cw, const std::string joint);
        Motor();
        int rotate(const int& mm);
};