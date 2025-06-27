#include "car.h"

ErrorType Car::carValidCheck() const
{
    if (carType == CarType::SEDAN && brake == brakeSystem::CONTINENTAL)
        return CASE_SEDAN_CONTINENTAL_B;
    if (carType == CarType::SUV && engine == Engine::TOYOTA)
        return CASE_SUV_TOYOTA_ENGINE;
    if (carType == CarType::TRUCK && engine == Engine::WIA)
        return CASE_TRUCK_WIA_ENGINE;
    if (carType == CarType::TRUCK && brake == brakeSystem::MANDO)
        return CASE_TRUCK_MANDO_B;
    if (brake == brakeSystem::BOSCH_B && steering != SteeringSystem::BOSCH_S)
        return CASE_BOSCH_B_NOT_BOSCH_S;
    if (engine == Engine::BROKEN_ENGINE)
        return CASE_BROKEN_ENGINE;
    return CASE_NORMAL;
}
