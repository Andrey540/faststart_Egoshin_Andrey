// fibonacii.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

const int COLUMNS = 5;

void PrintFibonacciNumbers(int upperNumber);
long int CalculateSum(long int firstNumber, long int secondNumber, bool& error); 
long int StringToInt(const char *str, bool &err);

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        bool error = false; 
        long int upperNumber = StringToInt(argv[1], error);

        if (error || (upperNumber <= 0))
        {
            printf("Incorrect fibonacci parameter\n");
            return 1;
        }

        PrintFibonacciNumbers(upperNumber);
    }

    return 0;
}

void PrintFibonacciNumbers(int upperNumber)
{
    long int intermediateNumber = 0;
    long int previousNumber = 0;
    long int currentNumber  = 1;
    bool firstNumber = true;
    int index = 0;

    while (currentNumber <= upperNumber)
    {
        if (!firstNumber)
        {
            printf(", ");
            if (index % COLUMNS == 0)
            {
                printf("\n");
            }
        }
        
        printf("%d", currentNumber);

        intermediateNumber = currentNumber;
        bool error = false;
        currentNumber  = CalculateSum(previousNumber, currentNumber, error);

        if (error)
        {
            break;
        }

        previousNumber = intermediateNumber;
        firstNumber = false;
        index++;
    }
}

long int CalculateSum(long int firstNumber, long int secondNumber, bool& error)
{
    error = LONG_MAX - firstNumber < secondNumber;
    return firstNumber + secondNumber;
}

long int StringToInt(const char *str, bool &err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}