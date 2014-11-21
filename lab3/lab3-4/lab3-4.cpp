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
#include <vector>

using namespace boost;
using namespace std;

optional<long> GetUpperBoundSet(const string& str);
set<long> GeneratePrimeNumbersSet(const long& upperBound);
optional<long> ReadIntValue(const string& str, function<void(long value)> validate);
void PrintHelp();
void TestGeneratePrimeNumbersEmptySet();
void TestGeneratePrimeNumbersSet();

const long MAX_UPPER_BOUND = 100000000;

int main(int argc, char* argv[])
{
    TestGeneratePrimeNumbersEmptySet();
    TestGeneratePrimeNumbersSet();

    if (argc != 2)
    {
        cout << "Incorrect format!" << endl;
        PrintHelp();
        return 1;
    }

    try
    {
        optional<long> upperBoundSet = GetUpperBoundSet(argv[1]);
        set<long> primeNumbersSet = GeneratePrimeNumbersSet(upperBoundSet.get());
        copy(primeNumbersSet.begin(), primeNumbersSet.end(), ostream_iterator<long>(cout, " " ));
    }
    catch (std::exception const& e)
    {
        cout << e.what();
        return 1;
    }
	return 0;
}

optional<long> GetUpperBoundSet(const string& str)
{
    optional<long> setUpperBound;
    setUpperBound = ReadIntValue(str, [](long value){
        if ((value <= 0) || (value > MAX_UPPER_BOUND))
        {
            throw domain_error("Upper bound must be greater than 0 and less than 100000000");
        }
    });
    return setUpperBound;
}

set<long> GeneratePrimeNumbersSet(const long& upperBound)
{    
    vector<bool> prime(upperBound + 1, true);
    long arithmeticBound = sqrt(upperBound);
    for (long i = 2; i <= arithmeticBound; ++i)
    {
        if (prime[i])
        {
            for (long j = i * i; j <= upperBound; j += i)
            {
                prime[j] = false;
            }
        }
    }

    set<long> primeNumbersSet;
    for (long i = 1; i <= upperBound; ++i)
    {
        if (prime[i])
        {
            primeNumbersSet.insert(primeNumbersSet.end(), i);
        }
    }
    return primeNumbersSet;         
}

optional<long> ReadIntValue(const string& str, function<void(long value)> validate)
{
    try
    {
        long value = stoi(str);
        validate(value);
        return value;
    }
    catch (invalid_argument const&)
    {
        throw domain_error("Upper bounce must be a number");
    }
}

void PrintHelp()
{
    cout << "lab3-4.exe <upper_bound> - correct format" << endl;
    return;
}

void TestGeneratePrimeNumbersEmptySet()
{
    set<long> testSet;
    assert(GeneratePrimeNumbersSet(0) == testSet && "Algorithm error!");
}

void TestGeneratePrimeNumbersSet()
{
    set<long> testSet;
    testSet.insert(testSet.begin(), 1);
    testSet.insert(testSet.begin(), 2);
    testSet.insert(testSet.begin(), 3);
    testSet.insert(testSet.begin(), 5);
    testSet.insert(testSet.begin(), 7);
    testSet.insert(testSet.begin(), 11);
    testSet.insert(testSet.begin(), 13);
    testSet.insert(testSet.begin(), 17);
    testSet.insert(testSet.begin(), 19);

    assert(GeneratePrimeNumbersSet(22) == testSet && "Algorithm error!");
}