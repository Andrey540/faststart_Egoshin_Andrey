// invert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MATRIX_SIZE = 3;

typedef double Matrix3x3[MATRIX_SIZE][MATRIX_SIZE];
typedef const double ConstMatrix3x3[MATRIX_SIZE][MATRIX_SIZE];

bool ReadMatrix(ifstream& file, Matrix3x3 matrix);
void PrintMatrix(ConstMatrix3x3 matrix);
double CalculateDeterminant(ConstMatrix3x3 matrix);
double CalculateMinor(double A11, double A12, double A21, double A22);
void CalculateInvertMatrix(ConstMatrix3x3 matrix, Matrix3x3 invertMatrix);
void TransponseMatrix(Matrix3x3 matrix);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Incorrect format!" << endl;
        cout << "Correct format - invert.exe <input_file>" << endl;
        return 1;
    }

    ifstream sourceFile(argv[1]);

    if (sourceFile.is_open())
    {
        Matrix3x3 matrix;
        if (!ReadMatrix(sourceFile, matrix))
        {
           cout << "There is not matrix " << MATRIX_SIZE << " x " << MATRIX_SIZE << endl;
           return 1; 
        }

        if (CalculateDeterminant(matrix) == 0)
        {
           cout << "Error - deterbinant of the matrix = 0!" << endl;
           return 1;
        }
        Matrix3x3 invertMatrix;
        CalculateInvertMatrix(matrix, invertMatrix);
        PrintMatrix(invertMatrix);
    }
    else
    {
        cout << "Can not open file!" << endl;
        return 1;
    }

	return 0;
}

bool ReadMatrix(ifstream& file, Matrix3x3 matrix)
{
    int index = 0;
    int row = 0;
    while (file >> matrix[row][index % MATRIX_SIZE])
    {
        index++;
        if (index > MATRIX_SIZE * MATRIX_SIZE)
        {
            break;
        }
        row = index / MATRIX_SIZE;
    }

    return index == MATRIX_SIZE * MATRIX_SIZE;
}

void CalculateInvertMatrix(ConstMatrix3x3 matrix, Matrix3x3 invertMatrix)
{
    double determinanrt = CalculateDeterminant(matrix);
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            int row1 = (i + 1) % MATRIX_SIZE;
            int row2 = (i + 2) % MATRIX_SIZE;
            int col1 = (j + 1) % MATRIX_SIZE;
            int col2 = (j + 2) % MATRIX_SIZE;
            invertMatrix[i][j] = CalculateMinor(matrix[row1][col1], matrix[row1][col2], 
                                             matrix[row2][col1], matrix[row2][col2]);
            invertMatrix[i][j] /= determinanrt;
        }
    }
    TransponseMatrix(invertMatrix);
    return;
}

void TransponseMatrix(Matrix3x3 matrix)
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            double replacingValue = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = replacingValue;
        }
    }
}

double CalculateDeterminant(ConstMatrix3x3 matrix)
{
    double determinant = matrix[0][0] * CalculateMinor(matrix[1][1], matrix[1][2],
                                                       matrix[2][1], matrix[2][2]);
    determinant -= matrix[0][1] * CalculateMinor(matrix[1][0], matrix[1][2],
                                                 matrix[2][0], matrix[2][2]);
    determinant += matrix[0][2] * CalculateMinor(matrix[1][0], matrix[1][1],
                                                 matrix[2][0], matrix[2][1]);
    return determinant;
}

double CalculateMinor(double A11, double A12, double A21, double A22)
{
    return (A11 * A22) - (A12 * A21);
}

void PrintMatrix(ConstMatrix3x3 matrix)
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            cout << setprecision(3) << fixed << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return;
}