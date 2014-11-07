// solve.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

const int MAX_COEFFICIENT_COUNT = 3;

typedef struct
{
    double firstRoot;
    double secondRoot;
} QuadraticEquationRoots;


int StringToInt(const char *str, bool &err);
QuadraticEquationRoots CalculateQuadraticEquationRoots(int A, int B, int C, bool& error);
void PrintQuadraticEquationRoots(QuadraticEquationRoots const& roots);
void PrintHelp();

int main(int argc, char* argv[])
{
    if (argc != MAX_COEFFICIENT_COUNT + 1)
    {
        printf("Incorrect format arguments!\n");
        PrintHelp();
        return 1;
    }

    int coefficients[MAX_COEFFICIENT_COUNT];
    bool error = false;
    for (int i = 1; i <= MAX_COEFFICIENT_COUNT; ++i)
    {        
        coefficients[i - 1] = StringToInt(argv[i], error);
        if (error)
        {
            printf("Parameter %d must be a number!", i);
            return 1;
        }
    }

    if (coefficients[0] == 0)
    {
        printf("Parametr A = 0. This is not quadratic equation!");
        return 1;
    }

    QuadraticEquationRoots roots = CalculateQuadraticEquationRoots(coefficients[0], coefficients[1], coefficients[2], error);
    if (error)
    {
        printf("There is no real roots");
    }
    else
    {
        PrintQuadraticEquationRoots(roots);
    }
	return 0;
}

int StringToInt(const char *str, bool &err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}

QuadraticEquationRoots CalculateQuadraticEquationRoots(int A, int B, int C, bool& error)
{
    QuadraticEquationRoots roots;
    roots.firstRoot  = 0;
    roots.secondRoot = 0;
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0)
    {
        error = true;
        return roots;
    }
    
    roots.firstRoot  = (-B + sqrt(discriminant)) / 2 * A;
    roots.secondRoot = (-B - sqrt(discriminant)) / 2 * A;

    return roots;
}

void PrintQuadraticEquationRoots(QuadraticEquationRoots const& roots)
{
    printf("%.4lf", roots.firstRoot);

    if (roots.firstRoot != roots.secondRoot)
    {
        printf(" %.4lf", roots.secondRoot);
    }

    return;
}

void PrintHelp()
{
    printf("Correct format - solve.exe <A> <B> <C>");
    return;
}
