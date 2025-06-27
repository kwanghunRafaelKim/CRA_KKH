#ifdef _DEBUG

#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#else

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Common.h"
#include "car.h"
#include "carfactory.h"
#include "carSimulator.h"
using namespace std;

int QuestionStep[MaxNum_Question];

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

bool IsGoBacktoPrevPage(QuestionType_t* step, int answer)
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


int main()
{
    char inputbuf[100];
    QuestionType_t step = CarType_Q;
    CarFactory factory;
    CarSimulator simulator;

    while (true)
    {
        displayInfo(step);
        getUserInput(inputbuf);

        if (IsInputExit(inputbuf)) break;
        if (IsInputNotNumber(inputbuf)) continue;
        int answer = getAnswerfromUser(inputbuf);

        if (IsInvalidInput(step, answer)) continue;
        if (IsGoBacktoPrevPage(&step, answer)) continue;

        QuestionStep[step] = answer;
        factory.makeCar(step, answer);

        if (step == Run_Test) {
            Car car = factory.getCar();
            if (answer == RUN) simulator.run(car);
            else if (answer == TEST) simulator.test(car);
            delay(2000);
        }
        else {
            step = (QuestionType_t)((int)step + 1);
            delay(800);
        }
    }
}


#endif