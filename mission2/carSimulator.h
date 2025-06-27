#pragma once
#include "car.h"

class CarSimulator {
public:
    void run(const Car& car);
    void test(const Car& car);
    const char* getCarTypeName(CarType carType);
    const char* getEngineName(Engine engine);
    const char* getbrakeSystemName(brakeSystem brakesystem);
    const char* getSteerinSystemName(SteeringSystem steeringsystem);
    const char* getCarCheckResult(int ErrorCode);

    void delay(int ms)
    {
        volatile int sum = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < 1000; j++)
            {
                for (int t = 0; t < ms; t++)
                {
                    sum++;
                }
            }
        }
    }
}; 
