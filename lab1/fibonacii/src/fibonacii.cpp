// fibonacii.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

const int COLUMNS = 5;

void PrintFibonacciNumbers(int upperNumber);
long int CalculateSum(long int firstNumber, long int secondNumber); 
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
    int index = 1;

    while (currentNumber <= upperNumber)
    {
        if (!firstNumber)
        {
            printf(", ");
        }
        if (index % COLUMNS == 0)
        {
            printf("\n");
        }
        printf("%d", currentNumber);

        intermediateNumber = currentNumber;
        currentNumber  = CalculateSum(previousNumber, currentNumber);
        previousNumber = intermediateNumber;

        if (currentNumber < 0)
        {
            printf("\nLimit varible was exceeded, program stopped\n");
            break;
        }

        firstNumber = false;
        index++;
    }
}

long int CalculateSum(long int firstNumber, long int secondNumber)
{
    return (LONG_MAX - firstNumber < secondNumber) ? -1 : (firstNumber + secondNumber);
}

long int StringToInt(const char *str, bool &err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}