// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <boost\optional.hpp>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <assert.h>

using namespace std;

void ReadArray(vector<double>& array);
void PrepareArray(vector<double>& array);
void TestPrepareEmptyArray();
void TestPrepareArray();

int main(int argc, char* argv[])
{
    void TestPrepareEmptyArray();
    void TestPrepareArray();

    vector<double> array;
    cout << "Enter float array" << endl;
    ReadArray(array);
    PrepareArray(array);
    cout << "Result:" << endl;
    copy(array.begin(), array.end(), ostream_iterator<double>(cout, " " ));
    
    return 0;
}

void TestPrepareEmptyArray()
{
    vector<double> testVector;
    vector<double> resultVector;

    PrepareArray(testVector);

    assert(testVector == resultVector && "Algorithm error!");
    return;
}

void TestPrepareArray()
{
    double testArray[] = {1.2, -21.279, 11.2277, 0.21};
    vector<double> testVector;
    testVector.insert(testVector.end(), begin(testArray), end(testArray));

    double resultArray[] = {-42.558, -5.11885, 0.42, 4.90885};
    vector<double> resultVector;
    resultVector.insert(resultVector.end(), begin(resultArray), end(resultArray));

    PrepareArray(testVector);

    assert(testVector == resultVector && "Algorithm error!");
    return;
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

double AddIfPositive(double sum, double item)
{
    return sum + (item > 0.0 ? item : 0.0);
};

void PrepareArray(vector<double>& array)
{
    double sumOfNonNegativeElements = accumulate(begin(array), end(array), 0.0, AddIfPositive);

    const size_t n = array.size();
    bool isEvenItem = true;
    for (size_t i = 0; i < n; ++i, isEvenItem = !isEvenItem)
    {
       double & currentItem = array[i];
       currentItem = isEvenItem ? (currentItem * 2) : (currentItem - sumOfNonNegativeElements);
    }

    sort(array.begin(), array.end());

    return;
}