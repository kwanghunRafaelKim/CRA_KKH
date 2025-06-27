
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
    case Engine::BROKEN_ENGINE: return "���峭";
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
        printf("������ ���峪�ֽ��ϴ�.\n");
        printf("�ڵ����� �������� �ʽ��ϴ�.\n");
        return;
    }

    if (ErrorCode != CASE_NORMAL) {
        printf("�ڵ����� ���۵��� �ʽ��ϴ�\n");
        return;
    }

    printf("Car Type : %s\n", getCarTypeName(car.getCarType()));
    printf("Engine : %s\n", getEngineName(car.getEngine()));
    printf("Brake System : %s\n", getbrakeSystemName(car.getBrakeSystem()));
    printf("SteeringSystem : %s\n", getSteerinSystemName(car.getSteeringSystem()));
    printf("�ڵ����� ���۵˴ϴ�.\n");
}

void CarSimulator::test(const Car& car)
{
    ErrorType ErrorCode = car.carValidCheck();
    printf("Test...\n");
    delay(1500);
    printf("�ڵ��� ��ǰ ���� �׽�Ʈ ��� : %s\n", getCarCheckResult(ErrorCode));

    if (ErrorCode == CASE_NORMAL) return;

    switch (ErrorCode) {
    case CASE_SEDAN_CONTINENTAL_B:
    case CASE_TRUCK_MANDO_B:
        printf("%s ���� ", getCarTypeName(car.getCarType()));
        printf("%s ������ġ ", getbrakeSystemName(car.getBrakeSystem()));
        break;
    case CASE_SUV_TOYOTA_ENGINE:
    case CASE_TRUCK_WIA_ENGINE:
        printf("%s ���� ", getCarTypeName(car.getCarType()));
        printf("%s ���� ", getEngineName(car.getEngine()));
        break;
    case CASE_BOSCH_B_NOT_BOSCH_S:
        printf("%s ������ġ ���� ", getbrakeSystemName(car.getBrakeSystem()));
        printf("%s ������ġ �̿� ", getSteerinSystemName(car.getSteeringSystem()));
        break;
    default:
        break;
    }
    printf("���Ұ� \n");
}

