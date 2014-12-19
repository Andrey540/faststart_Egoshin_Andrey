#include "stdafx.h"
#include "Car.h"
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

CCar::CCar(void)
    : _turnedOn(false),
    _directionFront(true),
    _gear(0),
    _speed(0)
{
}

bool CCar::IsTurnedOn()
{
    return _turnedOn;
}

bool CCar::TurnOnEngine()
{
    bool result = !_turnedOn;
    _turnedOn = true;
    return result;
}

bool CCar::TurnOffEngine()
{
    bool result = _turnedOn && (_speed == 0) && (_gear == 0);
    if (result)
    {
        _turnedOn = false;
    }
    return result;
}

bool CCar::SetSpeed(short speed)
{
    bool result = false;
    if (CheckCanSetSpeed(speed))
    {
        result = true;
        _speed = speed;
    }
    else
    {
        string direction = GetDirrectionState();
        cout << "Can't set speed, because current gear " << _gear << " speed " <<
             _speed << " and direction " << direction.c_str() << endl;
    }

    return result;
}

bool CCar::SetGear(short gear)
{
    bool result = false;
    if (!_turnedOn && gear != 0)
    {
        return result;
    }
    if (CheckCanSetGear(gear))
    {        
        result = true;
        _gear = gear;
        DefineDirrection();
    }
    else
    {
        string direction = GetDirrectionState();
        cout << "Can't set gear, because current gear " << _gear << " speed " <<
             _speed << " and direction " << direction.c_str() << endl;
    }

    return result;
}

short CCar::GetGear()
{
    return _gear;
}

short CCar::GetSpeed()
{
    return _speed;
}

void CCar::GetInfo()
{
    string infoLine = "Engine is turned ";
    infoLine += GetEngineState();
    cout << infoLine.c_str() << endl;

    infoLine = "Direction ";
    infoLine += GetDirrectionState();
    cout << infoLine.c_str() << endl;

    cout << "Speed " << _speed << endl;
    cout << "Gear " << _gear << endl;
    return;
}

CCar::~CCar(void)
{
}

bool CCar::CheckCanSetSpeed(short speed)
{
    bool result;
    switch(_gear)
    {
        case -1:
            result = (speed >= 0 && speed <= 20);
            break;
        case 0:
            result = (speed == 0);
            break;
        case 1:
            result = (speed >= 0 && speed <= 30);
            break;
        case 2:
            result = (speed >= 20 && speed <= 50);
            break;
        case 3:
            result = (speed >= 30 && speed <= 60);
            break;
        case 4:
            result = (speed >= 40 && speed <= 90);
            break;
        case 5:
            result = (speed >= 50 && speed <= 150);
            break;
        default:
            result = false;
    }
    return result;
}

bool CCar::CheckCanSetGear(short gear)
{
    bool result;
    switch(gear)
    {
        case -1:
            result = ((_speed == 0) && (_gear == 0)) ||
                     ((_speed >= 0 && _speed <= 20) && !_directionFront);
            break;
        case 0:
            result = (_speed == 0);
            break;
        case 1:
            result = (_speed >= 0 && _speed <= 30) && _directionFront;
            break;
        case 2:
            result = (_speed >= 20 && _speed <= 50) && _directionFront;
            break;
        case 3:
            result = (_speed >= 30 && _speed <= 60);
            break;
        case 4:
            result = (_speed >= 40 && _speed <= 90);
            break;
        case 5:
            result = (_speed >= 50 && _speed <= 150);
            break;
        default:
            result = false;
    }
    return result;
}

const string CCar::GetEngineState()
{
    string result = _turnedOn ? "turned on" : "turned off";
    return result;
}

const string CCar::GetDirrectionState()
{
    string result = _directionFront ? "front" : "back";
    return result;
}

void CCar::DefineDirrection()
{
    if (_gear == 0)
    {
        _directionFront = true;
    }
    else if(_gear == -1)
    {
        _directionFront = false;
    }
    else
    {
        _directionFront = true;
    }
}
