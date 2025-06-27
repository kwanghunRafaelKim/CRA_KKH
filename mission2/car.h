#pragma once

#include "Common.h"

class Car {
private:
    CarType carType = CarType::SEDAN;
    Engine engine = Engine::GM;
    brakeSystem brake = brakeSystem::MANDO;
    SteeringSystem steering = SteeringSystem::BOSCH_S;

public:
    void setCarType(CarType type) { carType = type; }
    void setEngine(Engine e) { engine = e; }
    void setBrakeSystem(brakeSystem b) { brake = b; }
    void setSteeringSystem(SteeringSystem s) { steering = s; }

    CarType getCarType() const { return carType; }
    Engine getEngine() const { return engine; }
    brakeSystem getBrakeSystem() const { return brake; }
    SteeringSystem getSteeringSystem() const { return steering; }

    ErrorType carValidCheck() const;
};