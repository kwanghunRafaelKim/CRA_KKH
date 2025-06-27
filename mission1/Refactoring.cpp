#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

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

int QuestionStep[MaxNum_Question];

void selectCarType(CarType answer);
void selectEngine(Engine answer);
void selectbrakeSystem(brakeSystem answer);
void selectSteeringSystem(SteeringSystem answer);
int CarValidCheck();
void runProducedCar(int answer);

void delay(int ms);

const char* getCarTypeName(CarType carType) {
    switch (carType) {
    case CarType::SEDAN: return "SEDAN";
    case CarType::SUV: return "SUV";
    case CarType::TRUCK: return "TRUCK";
    default: return "";
    }
}

const char* getEngineName(Engine engine) {
    switch (engine) {
    case Engine::GM: return "GM";
    case Engine::TOYOTA: return "TOYOTA";
    case Engine::WIA: return "WIA";
    case Engine::BROKEN_ENGINE: return "고장난";
    default: return "";
    }
}

const char* getbrakeSystemName(brakeSystem brakesystem) {
    switch (brakesystem) {
    case brakeSystem::MANDO: return "MANDO";
    case brakeSystem::CONTINENTAL: return "CONTINENTAL";
    case brakeSystem::BOSCH_B: return "BOSCH_B";
    default: return "";
    }
}

const char* getSteerinSystemName(SteeringSystem steeringsystem) {
    switch (steeringsystem) {
    case SteeringSystem::BOSCH_S: return "BOSCH";
    case SteeringSystem::MOBIS: return "MOBIS";
    default: return "";
    }
}

const char* getCarCheckResult(int ErrorCode) {
    switch (ErrorCode) {
    case CASE_NORMAL: return "PASS";
    default: return "FAIL";
    }
}

void selectCarType(CarType answer)
{
    QuestionStep[CarType_Q] = (int)answer;
    printf("차량 타입으로 %s을 선택하셨습니다.\n", getCarTypeName(answer));
}

void selectEngine(Engine answer)
{
    QuestionStep[Engine_Q] = (int)answer;
    printf("%s 엔진을 선택하셨습니다.\n", getEngineName(answer));
}

void selectbrakeSystem(brakeSystem answer)
{
    QuestionStep[brakeSystem_Q] = (int)answer;
    printf("%s 제동장치를 선택하셨습니다.\n", getbrakeSystemName(answer));
}

void selectSteeringSystem(SteeringSystem answer)
{
    QuestionStep[SteeringSystem_Q] = (int)answer;
    printf("%s 조향장치를 선택하셨습니다.\n", getSteerinSystemName(answer));
}

int CarValidCheck()
{
    if (QuestionStep[CarType_Q] == (int)CarType::SEDAN && QuestionStep[brakeSystem_Q] == (int)brakeSystem::CONTINENTAL)
    {
        return CASE_SEDAN_CONTINENTAL_B;
    }
    else if (QuestionStep[CarType_Q] == (int)CarType::SUV && QuestionStep[Engine_Q] == (int)Engine::TOYOTA)
    {
        return CASE_SUV_TOYOTA_ENGINE;
    }
    else if (QuestionStep[CarType_Q] == (int)CarType::TRUCK && QuestionStep[Engine_Q] == (int)Engine::WIA)
    {
        return CASE_TRUCK_WIA_ENGINE;
    }
    else if (QuestionStep[CarType_Q] == (int)CarType::TRUCK && QuestionStep[brakeSystem_Q] == (int)brakeSystem::MANDO)
    {
        return CASE_TRUCK_MANDO_B;
    }
    else if (QuestionStep[brakeSystem_Q] == (int)brakeSystem::BOSCH_B && QuestionStep[SteeringSystem_Q] != (int)SteeringSystem::BOSCH_S)
    {
        return CASE_BOSCH_B_NOT_BOSCH_S;
    }
    else if(QuestionStep[Engine_Q] == (int)Engine::BROKEN_ENGINE)
    {
        return CASE_BROKEN_ENGINE;
    }
    return CASE_NORMAL;
}

void runProducedCar(int answer)
{
    int ErrorCode = CarValidCheck();
    switch (answer) {
    case RUN: {
        if (ErrorCode == CASE_BROKEN_ENGINE)
        {
            printf("엔진이 고장나있습니다.\n");
            printf("자동차가 움직이지 않습니다.\n");
            return;
        }
        if (ErrorCode != CASE_NORMAL)
        {
            printf("자동차가 동작되지 않습니다\n");
            return;
        }

        printf("Car Type : %s\n", getCarTypeName((CarType)QuestionStep[CarType_Q]));
        printf("Engine : %s\n", getEngineName((Engine)QuestionStep[Engine_Q]));
        printf("Brake System : %s\n", getbrakeSystemName((brakeSystem)QuestionStep[brakeSystem_Q]));
        printf("SteeringSystem : %s\n", getSteerinSystemName((SteeringSystem)QuestionStep[SteeringSystem_Q]));

        printf("자동차가 동작됩니다.\n");

        break;

    }
    case TEST: {
        printf("Test...\n");
        delay(1500);
        printf("자동차 부품 조합 테스트 결과 : %s\n", getCarCheckResult(ErrorCode));
        if (ErrorCode == CASE_NORMAL) return;
        switch (ErrorCode) {

        case CASE_SEDAN_CONTINENTAL_B:
        case CASE_TRUCK_MANDO_B:
            printf("%s 에는 ", getCarTypeName((CarType)QuestionStep[CarType_Q]));
            printf("%s ", getbrakeSystemName((brakeSystem)QuestionStep[brakeSystem_Q]));
            printf("제동장치 ");
            break;
        case CASE_SUV_TOYOTA_ENGINE:
        case CASE_TRUCK_WIA_ENGINE:
            printf("%s 에는 ", getCarTypeName((CarType)QuestionStep[CarType_Q]));
            printf("%s ", getEngineName((Engine)QuestionStep[Engine_Q]));
            printf("엔진 ");
            break;
        case CASE_BOSCH_B_NOT_BOSCH_S:
            printf("%s 제동장치 에는 ", getbrakeSystemName((brakeSystem)QuestionStep[brakeSystem_Q]));
            printf("%s ", getSteerinSystemName((SteeringSystem)QuestionStep[SteeringSystem_Q]));
            printf("조향장치 이외 ");
            break;
            break;
        default:
            break;
        }
        printf("사용불가 \n");
    }
    default:
        break;
    }
    delay(2000);
}

void printCarPicture(void)
{
    printf("        ______________\n");
    printf("       /|            | \n");
    printf("  ____/_|_____________|____\n");
    printf(" |                      O  |\n");
    printf(" '-(@)----------------(@)--'\n");
    printf("===============================\n");
}

void displayInfo(QuestionType_t step)
{
    if (step == CarType_Q)
    {
        printf(CLEAR_SCREEN);
        printCarPicture();
        printf("어떤 차량 타입을 선택할까요?\n");
        printf("1. Sedan\n");
        printf("2. SUV\n");
        printf("3. Truck\n");
    }
    else if (step == Engine_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 엔진을 탑재할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. GM\n");
        printf("2. TOYOTA\n");
        printf("3. WIA\n");
        printf("4. 고장난 엔진\n");
    }
    else if (step == brakeSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 제동장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. MANDO\n");
        printf("2. CONTINENTAL\n");
        printf("3. BOSCH\n");
    }
    else if (step == SteeringSystem_Q)
    {
        printf(CLEAR_SCREEN);
        printf("어떤 조향장치를 선택할까요?\n");
        printf("0. 뒤로가기\n");
        printf("1. BOSCH\n");
        printf("2. MOBIS\n");
    }
    else if (step == Run_Test)
    {
        printf(CLEAR_SCREEN);
        printf("멋진 차량이 완성되었습니다.\n");
        printf("어떤 동작을 할까요?\n");
        printf("0. 처음 화면으로 돌아가기\n");
        printf("1. RUN\n");
        printf("2. Test\n");
    }
    printf("===============================\n");
}

void getUserInput(char buf[])
{
    printf("INPUT > ");
    fgets(buf, sizeof(buf), stdin);

    // 엔터 개행문자 제거
    char* context = nullptr;
    strtok_s(buf, "\r", &context);
    strtok_s(buf, "\n", &context);
}

bool IsInputExit(char buf[])
{
    if (!strcmp(buf, "exit"))
    {
        printf("바이바이\n");
        return true;
    }
    return false;
}

bool IsInputNotNumber(char buf[])
{
    char* checkNumber;
    strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    // 입력받은 문자가 숫자가 아니라면
    if (*checkNumber != '\0')
    {
        printf("ERROR :: 숫자만 입력 가능\n");
        delay(800);
        return true;
    }
    return false;
}

int getAnswerfromUser(char buf[])
{
    char* checkNumber;
    int answer = strtol(buf, &checkNumber, 10); // 문자열을 10진수로 변환

    return answer;
}

bool IsInvalidInput(QuestionType_t step, int answer)
{
    bool retval = false;
    if (step == CarType_Q && !(answer >= 1 && answer <= 3))
    {
        printf("ERROR :: 차량 타입은 1 ~ 3 범위만 선택 가능\n");
        retval = true;
    }

    if (step == Engine_Q && !(answer >= 0 && answer <= 4))
    {
        printf("ERROR :: 엔진은 1 ~ 4 범위만 선택 가능\n");
        retval = true;
    }

    if (step == brakeSystem_Q && !(answer >= 0 && answer <= 3))
    {
        printf("ERROR :: 제동장치는 1 ~ 3 범위만 선택 가능\n");
        retval = true;
    }

    if (step == SteeringSystem_Q && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: 조향장치는 1 ~ 2 범위만 선택 가능\n");
        retval = true;
    }

    if (step == Run_Test && !(answer >= 0 && answer <= 2))
    {
        printf("ERROR :: Run 또는 Test 중 하나를 선택 필요\n");
        retval = true;
    }
    delay(800);
    return retval;
}

bool IsGoBacktoPrevPage(QuestionType_t *step, int answer)
{
    bool retVal = false;
    // 처음으로 돌아가기
    if (answer == 0 && *step == Run_Test)
    {
        *step = CarType_Q;
        retVal = true;
    }

    // 이전으로 돌아가기
    if (answer == 0 && *step >= Engine_Q)
    {
        *step = (QuestionType_t)((int)(*step) - 1);
        retVal = true;
    }
    return retVal;
}

void MakeCar(QuestionType_t* step, int answer)
{
    if (*step == CarType_Q)
    {
        selectCarType((CarType)answer);
        delay(800);
        *step = Engine_Q;
    }
    else if (*step == Engine_Q)
    {
        selectEngine((Engine)answer);
        delay(800);
        *step = brakeSystem_Q;
    }
    else if (*step == brakeSystem_Q)
    {
        selectbrakeSystem((brakeSystem)answer);
        delay(800);
        *step = SteeringSystem_Q;
    }
    else if (*step == SteeringSystem_Q)
    {
        selectSteeringSystem((SteeringSystem)answer);
        delay(800);
        *step = Run_Test;
    }
    else if (*step == Run_Test)
    {
        runProducedCar(answer);
        delay(2000);
    }
}

int main()
{
    char inputbuf[100];
    QuestionType_t step = CarType_Q;

    while (true)
    {
        displayInfo(step);
        getUserInput(inputbuf);

        if (IsInputExit(inputbuf)) break;
        if (IsInputNotNumber(inputbuf)) continue;
        int answer = getAnswerfromUser(inputbuf);

        if (IsInvalidInput(step, answer)) continue;
        if (IsGoBacktoPrevPage(&step, answer)) continue;

        MakeCar(&step, answer);
    }
}