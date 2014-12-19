// lab4-1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Car.h"

using namespace std;

int main(int argc, char* argv[])
{
    string command;
    cout << "For exit enter Exit" << endl;
    CCar car;
    while (cin >> command)
    {
        if (command == "Exit")
        {
            break;
        }
        else if (command == "Info")
        {
            car.GetInfo();
        }
        else if (command == "EngineOn")
        {
            car.TurnOnEngine();
        }
        else if (command == "EngineOff")
        {
            car.TurnOffEngine();
        }
        else if (command == "SetGear")
        {
            int gear;
            cin >> gear;
            car.SetGear(gear);
        }
        else if (command == "SetSpeed")
        {
            int speed;
            cin >> speed;
            car.SetSpeed(speed);
        }
        else
        {
            cout << "Undefined command!" << endl;
        }
    }

	return 0;
}

