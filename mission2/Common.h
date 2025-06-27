#pragma once

#pragma once

#define CLEAR_SCREEN "\033[H\033[2J"

typedef enum QuestionType
{
    CarType_Q,
    Engine_Q,
    brakeSystem_Q,
    SteeringSystem_Q,
    Run_Test,
    MaxNum_Question
}QuestionType_t;

enum class CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    MaxNum_CarType
};

enum class Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    BROKEN_ENGINE,
    MaxNum_Engine
};

enum class brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    MaxNum_brakeSystem
};

enum class SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    MaxNum_SterringSystem
};

enum RunType
{
    RUN = 1,
    TEST = 2
};

enum ErrorType
{
    CASE_NORMAL,
    CASE_SEDAN_CONTINENTAL_B,
    CASE_TRUCK_MANDO_B,
    CASE_SUV_TOYOTA_ENGINE,
    CASE_TRUCK_WIA_ENGINE,
    CASE_BOSCH_B_NOT_BOSCH_S,
    CASE_BROKEN_ENGINE
};