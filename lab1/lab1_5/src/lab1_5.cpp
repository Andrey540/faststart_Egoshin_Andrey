// lab1_5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vld.h>

using namespace std;

#define SPEED_PROMPT "Enter v0"
#define ANGEL_PROMPT "Enter a0"
#define RESULT_MESSAGE   "Distance is:"

const int MAX_INT_SIZE = 10;
const int MAX_ANGEL = 90;
const double ACCELERATION_DUE_TO_OVERFLOW = 9.8;

double CalculateDistance(int speed, int angel);
int GetIntParameter(const char *invitationMessage, bool &exitFlag, int minValue, int maxValue);
string GetStringFromIOStream(void);
int StringToInt(const char *str, bool &err);

int main(int argc, char* argv[])
{    
    bool exitFlag = false;

    while(!exitFlag)
    {
        int speed = GetIntParameter(SPEED_PROMPT, exitFlag, 0, INT_MAX);

        if (exitFlag)
        {
            continue;
        }

        int angle = GetIntParameter(ANGEL_PROMPT, exitFlag, 0, MAX_ANGEL);

        if (exitFlag)
        {
            continue;
        }

        double distance = CalculateDistance(speed, angle);
        printf("%s %f\n", RESULT_MESSAGE, distance);
    }

    return 0;
}

double CalculateDistance(int speed, int angel)
{
    double time = 2 * (speed * sin(angel * M_PI / 180)) / ACCELERATION_DUE_TO_OVERFLOW;
    return (speed * cos(angel * M_PI / 180)) * time;
}

int GetIntParameter(const char *invitationMessage, bool &exitFlag, int minValue, int maxValue)
{
    const char* additionalMessage = " (or type 'exit') ";
    const char* exitCondition     = "exit";    
    bool incorrectParameter = true;
    int result = 0;
    string parameter = "";

    while(incorrectParameter)
    {
        std::cout << invitationMessage << additionalMessage;
        parameter = GetStringFromIOStream();

        if (strcmp(parameter.c_str(), exitCondition) == 0)
        {
            exitFlag = true;
            return 0;
        }

        result = StringToInt(parameter.c_str(), incorrectParameter);

        if (incorrectParameter)
        {
            printf("Parameter must be a number\n");            
        }
        else if ((result <= minValue) || (result >= maxValue))
        {
            printf("Parameter must be greater then %d and less then %d\n", minValue, maxValue);
            incorrectParameter = true;
        }
    }

    return result;
}

string GetStringFromIOStream(void)
{
    string str;
    getline(cin, str);
    return str;
}

int StringToInt(const char *str, bool &err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}