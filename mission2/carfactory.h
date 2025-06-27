#pragma once

#include "car.h"

class CarFactory {
private:
    Car car;

public:
    void makeCar(QuestionType_t step, int answer);

    Car getCar() const { return car; }
};
