#include "carfactory.h"

void CarFactory::makeCar(QuestionType_t step, int answer) {
    switch (step) {
    case CarType_Q:
        car.setCarType(static_cast<CarType>(answer));
        break;
    case Engine_Q:
        car.setEngine(static_cast<Engine>(answer));
        break;
    case brakeSystem_Q:
        car.setBrakeSystem(static_cast<brakeSystem>(answer));
        break;
    case SteeringSystem_Q:
        car.setSteeringSystem(static_cast<SteeringSystem>(answer));
        break;
    default:
        break;
    }
}
