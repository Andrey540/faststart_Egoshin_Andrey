// lab1_5.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <stdexcept>
#include <optional.hpp>
#include <functional>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <iostream>

#define exception std::exception
     
using namespace std;
using namespace boost;

const double MAX_ANGLE_VALUE = 90;
     
optional<double> ReadDoubleUntilExit(string const& prompt, function<void(double value)> validate)
{
    while (true)
    {
        cout << prompt;
        string str;
        getline(cin, str);
        if (str == "exit")
        {
            return none;
        }
        try
        {
            double value = stod(str);
            validate(value);
            return value;
        }
        catch (invalid_argument const&)
        {
            cout << "Please enter a number" << endl;
        }
        catch (exception const& e)
        {
            cout << e.what() << endl;
        }
    }   
}
     
optional<double> ReadSpeed()
{
    optional<double> speed;
    do
    {
        speed = ReadDoubleUntilExit("Enter speed or exit: ", [](double value){
            if (value <= 0)
            {
                throw domain_error("Speed must be greater than 0");
            }
        });
    } while (speed && (speed.get() <= 0));
    return speed;
}
     
optional<double> ReadAngle()
{    
    optional<double> angle;
    do
    {
        angle = ReadDoubleUntilExit("Enter angle or exit: ", [](double value){
            if ((value <= 0) || (value >= MAX_ANGLE_VALUE))
            {
                throw domain_error("Angle must be greater than 0 and less than 90");
            }
        });
    } while (angle && ((angle.get() <= 0) || (angle >= MAX_ANGLE_VALUE)));
    return angle;
}
     
double CalculateDistance(double speed, double angle)
{
    const double ACCELERATION_DUE_TO_OVERFLOW = 9.8;
    double time = 2 * (speed * sin(angle * M_PI / 180)) / ACCELERATION_DUE_TO_OVERFLOW;
    return (speed * cos(angle * M_PI / 180)) * time;
}
     
void main()
{
    optional<double> speed;
    optional<double> angle;
    while ((speed = ReadSpeed()) && (angle = ReadAngle()))
    {
        cout << "Distance is " << CalculateDistance(*speed, *angle) << endl;
    }
}