// lab3.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <stdexcept>
#include <boost\optional.hpp>
#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <numeric>

using namespace boost;
using namespace std;

void PrepareArray(vector<double>& array);
void TestPrepareEmptyArray();
void TestPrepareArray();

int main(int argc, char* argv[])
{
    TestPrepareEmptyArray();
    TestPrepareArray();

    vector<double> array;
    cout << "Enter float array" << endl;
    array.insert(array.end(), istream_iterator<double>(cin), istream_iterator<double>());
    PrepareArray(array);
    cout << "Result:" << endl;
    sort(array.begin(), array.end());
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

    double resultArray[] = {2.4, -33.9167, 22.4554, -12.4277};
    vector<double> resultVector;
    resultVector.insert(resultVector.end(), begin(resultArray), end(resultArray));

    PrepareArray(testVector);

    assert(testVector == resultVector && "Algorithm error!");
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
       array[i] = isEvenItem ? (currentItem * 2) : (currentItem - sumOfNonNegativeElements);
    }    

    return;
}