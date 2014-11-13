// lab3-4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdexcept>
#include <boost\optional.hpp>
#include <string>
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <set>

using namespace boost;
using namespace std;

bool CheckIsNumberPrime(long number, set<int>& const primeNumbersSet);
set<int> GeneratePrimeNumbersSet(int upperBound);
optional<int> GetUpperBoundSet(string const& str);
set<int> GeneratePrimeNumbersSet(int upperBound);
optional<int> ReadIntValue(string const& str, function<void(int value)> validate);
void PrintSet(set<int>& const primeNumbersSet);
void PrintHelp();

const int MAX_UPPER_BOUND = 100000000;

int main(int argc, char* argv[])
{
    set<int> testSet;
    testSet.insert(testSet.begin(), 1);
    testSet.insert(testSet.begin(), 2);
    testSet.insert(testSet.begin(), 3);
    testSet.insert(testSet.begin(), 5);
    testSet.insert(testSet.begin(), 7);
    testSet.insert(testSet.begin(), 11);
    testSet.insert(testSet.begin(), 13);
    testSet.insert(testSet.begin(), 17);
    testSet.insert(testSet.begin(), 19);

    assert(GeneratePrimeNumbersSet(22) == testSet, "Algorithm error!");

    if (argc != 2)
    {
        cout << "Incorrect format!" << endl;
        PrintHelp();
        return 1;
    }

    try
    {
        optional<int> upperBoundSet = GetUpperBoundSet(argv[1]);
        set<int> primeNumbersSet = GeneratePrimeNumbersSet(upperBoundSet.get());
        PrintSet(primeNumbersSet);
    }
    catch (std::exception const& e)
    {
        cout << e.what();
        return 1;
    }
	return 0;
}

bool CheckIsNumberPrime(long number, set<int>& const primeNumbersSet)
{
    for (auto i = primeNumbersSet.begin(); i != primeNumbersSet.end(); ++i)
    {
        if (*i > number / 2)
        {
            break;
        }
        if ((*i != 1) && (number % *i) == 0)
        {
            return false;
        }
    }
    return true;
}

optional<int> GetUpperBoundSet(string const& str)
{
    optional<int> setUpperBound;
    setUpperBound = ReadIntValue(str, [](int value){
        if ((value <= 0) || (value > MAX_UPPER_BOUND))
        {
            throw domain_error("Upper bound must be greater than 0 and less than 100000000");
        }
    });
    return setUpperBound;
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
    set<int> primeNumbersSet;
    primeNumbersSet.insert(primeNumbersSet.end(), 1);
    for (int i = 2; i <= upperBound; ++i)
    {
        if (CheckIsNumberPrime(i, primeNumbersSet))
        {
            primeNumbersSet.insert(primeNumbersSet.end(), i);
        }
    }
    return primeNumbersSet;         
}

optional<int> ReadIntValue(string const& str, function<void(int value)> validate)
{
    try
    {
        int value = stoi(str);
        validate(value);
        return value;
    }
    catch (invalid_argument const&)
    {
    throw domain_error("Upper bounce must be a number");
    }
}

void PrintSet(set<int>& const primeNumbersSet)
{
    for_each(primeNumbersSet.begin(), primeNumbersSet.end(), [](int element){
        cout << element << " ";
    });

    return;
}

void PrintHelp()
{
    cout << "lab3-4.exe <upper_bound> - correct format" << endl;
    return;
}

