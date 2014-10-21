// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int MATRIX_COLS = 3;
const int MATRIX_ROWS = 3;

bool ReadMatrix(ifstream& file, double* matrix);
void PrintMatrix(double* matrix);
double CalculateDeterminant(double* matrix);
double CalculateMinor(double A11, double A12, double A21, double A22);
void CalculateInvertMatrix(double* matrix, double* invertMatrix);
void TransponseMatrix(double* matrix);

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("Empty parameter!");
        return 1;
    }

    ifstream sourceFile(argv[1]);

    if (sourceFile.is_open())
    {
        double matrix[MATRIX_COLS][MATRIX_ROWS];
        if (!ReadMatrix(sourceFile, (double*)matrix))
        {
           printf("There is not matrix %d x %d", MATRIX_COLS, MATRIX_ROWS);
           return 1;
        }

        if (CalculateDeterminant((double*)matrix) == 0)
        {
           printf("Error - deterbinant of the matrix = 0!");
           return 1;
        }
        double invertMatrix[MATRIX_COLS][MATRIX_ROWS];
        CalculateInvertMatrix((double*)matrix, (double*)invertMatrix);
        PrintMatrix((double*)invertMatrix);
    }
    else
    {
        printf("Can not open file!");
        return 1;
    }

	return 0;
}

bool ReadMatrix(ifstream& file, double* matrix)
{
    int index = 0;
    while (file >> matrix[index])
    {
        index++;
        if (index > MATRIX_COLS * MATRIX_ROWS)
        {
            break;
        }
    }

    return index == MATRIX_COLS * MATRIX_ROWS;
}

void CalculateInvertMatrix(double* matrix, double* invertMatrix)
{
    double determinanrt = CalculateDeterminant(matrix);
    for (int i = 0; i < MATRIX_COLS * MATRIX_ROWS; ++i)
    {
        int currentRow = i / MATRIX_COLS;
        int row1 = (currentRow + 1) % MATRIX_ROWS;
        int row2 = (currentRow + 2) % MATRIX_ROWS;
        int indA11 = row1 * MATRIX_COLS + ((i + 1) % MATRIX_COLS);
        int indA12 = row1 * MATRIX_COLS + ((i + 2) % MATRIX_COLS);
        int indA21 = row2 * MATRIX_COLS + ((i + 1) % MATRIX_COLS);
        int indA22 = row2 * MATRIX_COLS + ((i + 2) % MATRIX_COLS);
        invertMatrix[i] = CalculateMinor(matrix[indA11], matrix[indA12], 
                                                       matrix[indA21], matrix[indA22]);
        invertMatrix[i] /= determinanrt;
    }
    TransponseMatrix((double*)invertMatrix);
    return;
}

void TransponseMatrix(double* matrix)
{
    for (int i = 0; i < MATRIX_ROWS; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            double replacingValue = matrix[i * MATRIX_COLS + j];
            matrix[i * MATRIX_COLS + j] = matrix[j * MATRIX_COLS + i];
            matrix[j * MATRIX_COLS + i] = replacingValue;
        }
    }
}

double CalculateDeterminant(double* matrix)
{
    double determinant = matrix[0] * CalculateMinor(matrix[4], matrix[5],
                                                    matrix[7], matrix[8]);
    determinant -= matrix[1] * CalculateMinor(matrix[3], matrix[5],
                                              matrix[6], matrix[8]);
    determinant += matrix[2] * CalculateMinor(matrix[3], matrix[4],
                                              matrix[6], matrix[7]);
    return determinant;
}

double CalculateMinor(double A11, double A12, double A21, double A22)
{
    return (A11 * A22) - (A12 * A21);
}

void PrintMatrix(double* matrix)
{
    for (int i = 0; i < MATRIX_COLS * MATRIX_ROWS; ++i)
    {
        printf("%.3lf ", matrix[i]);

        if (i % MATRIX_COLS == MATRIX_COLS - 1)
        {
            printf("\n");
        }
    }
    return;
}