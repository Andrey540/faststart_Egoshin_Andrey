// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <assert.h>

using namespace std;

void ReadArray(vector<double>& array);
void PrepareArray(vector<double>& array);
void PrintArray(vector<double>& const array);

int main(int argc, char* argv[])
{
    vector<double> testArray;
    testArray.push_back(1.2);
    testArray.push_back(-21.279);
    testArray.push_back(11.2277);
    testArray.push_back(0.21);

    vector<double> resultArray;
    resultArray.push_back(-42.558);
    resultArray.push_back(-5.11885);
    resultArray.push_back(0.42);
    resultArray.push_back(4.90885);

    PrepareArray(testArray);

    assert(testArray == resultArray, "Algorithm error!");

    vector<double> array;
    cout << "Enter float array" << endl;
    ReadArray(array);
    PrepareArray(array);
    cout << "Result:" << endl;
    PrintArray(array);
    
    return 0;
}

void ReadArray(vector<double>& array)
{
    double element;
    while (cin >> element)
    {
        double newElement = element;
        array.push_back(element);
    }

    return;
}

void PrepareArray(vector<double>& array)
{
    double positiveSum = 0;
    for(auto i = array.begin(); i != array.end(); ++i)
    {
        if (*i > DBL_EPSILON)
        {
            positiveSum += (*i * 1000 * 0.5) / 1000;
        }
    }

    int count = 1;
    for(auto i = array.begin(); i != array.end(); ++i)
    {
        if (count % 2 == 0)
        {
            *i *= 2;
        }
        else
        {
            *i -= positiveSum;
        }
        ++count;
    }

    sort(array.begin(), array.end());

    return;
}

void PrintArray(vector<double>& const array)
{
    for_each(array.begin(), array.end(), [](double element){
        cout << element << " ";
    });

    return;
}