
#include <stdio.h>
#include "carSimulator.h"

const char* CarSimulator::getCarTypeName(CarType carType) {
    switch (carType) {
    case CarType::SEDAN: return "SEDAN";
    case CarType::SUV: return "SUV";
    case CarType::TRUCK: return "TRUCK";
    default: return "";
    }
}

const char* CarSimulator::getEngineName(Engine engine) {
    switch (engine) {
    case Engine::GM: return "GM";
    case Engine::TOYOTA: return "TOYOTA";
    case Engine::WIA: return "WIA";
    case Engine::BROKEN_ENGINE: return "고장난";
    default: return "";
    }
}

const char* CarSimulator::getbrakeSystemName(brakeSystem brakesystem) {
    switch (brakesystem) {
    case brakeSystem::MANDO: return "MANDO";
    case brakeSystem::CONTINENTAL: return "CONTINENTAL";
    case brakeSystem::BOSCH_B: return "BOSCH_B";
    default: return "";
    }
}

const char* CarSimulator::getSteerinSystemName(SteeringSystem steeringsystem) {
    switch (steeringsystem) {
    case SteeringSystem::BOSCH_S: return "BOSCH";
    case SteeringSystem::MOBIS: return "MOBIS";
    default: return "";
    }
}

const char* CarSimulator::getCarCheckResult(int ErrorCode) {
    switch (ErrorCode) {
    case CASE_NORMAL: return "PASS";
    default: return "FAIL";
    }
}

void CarSimulator::run(const Car& car)
{
    ErrorType ErrorCode = car.carValidCheck();

    if (ErrorCode == CASE_BROKEN_ENGINE) {
        printf("엔진이 고장나있습니다.\n");
        printf("자동차가 움직이지 않습니다.\n");
        return;
    }

    if (ErrorCode != CASE_NORMAL) {
        printf("자동차가 동작되지 않습니다\n");
        return;
    }

    printf("Car Type : %s\n", getCarTypeName(car.getCarType()));
    printf("Engine : %s\n", getEngineName(car.getEngine()));
    printf("Brake System : %s\n", getbrakeSystemName(car.getBrakeSystem()));
    printf("SteeringSystem : %s\n", getSteerinSystemName(car.getSteeringSystem()));
    printf("자동차가 동작됩니다.\n");
}

void CarSimulator::test(const Car& car)
{
    ErrorType ErrorCode = car.carValidCheck();
    printf("Test...\n");
    delay(1500);
    printf("자동차 부품 조합 테스트 결과 : %s\n", getCarCheckResult(ErrorCode));

    if (ErrorCode == CASE_NORMAL) return;

    switch (ErrorCode) {
    case CASE_SEDAN_CONTINENTAL_B:
    case CASE_TRUCK_MANDO_B:
        printf("%s 에는 ", getCarTypeName(car.getCarType()));
        printf("%s 제동장치 ", getbrakeSystemName(car.getBrakeSystem()));
        break;
    case CASE_SUV_TOYOTA_ENGINE:
    case CASE_TRUCK_WIA_ENGINE:
        printf("%s 에는 ", getCarTypeName(car.getCarType()));
        printf("%s 엔진 ", getEngineName(car.getEngine()));
        break;
    case CASE_BOSCH_B_NOT_BOSCH_S:
        printf("%s 제동장치 에는 ", getbrakeSystemName(car.getBrakeSystem()));
        printf("%s 조향장치 이외 ", getSteerinSystemName(car.getSteeringSystem()));
        break;
    default:
        break;
    }
    printf("사용불가 \n");
}

