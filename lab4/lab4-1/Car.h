#pragma once

#include <string>

using namespace std;

class CCar
{
public:
    CCar(void);
    ~CCar(void);

    bool IsTurnedOn();
    bool TurnOnEngine();
    bool TurnOffEngine();
    bool SetSpeed(short speed);
    bool SetGear(short gear);
    short GetGear();
    short GetSpeed();
    void GetInfo();

private:
    bool _turnedOn;
    bool _directionFront;
    int _gear;
    int _speed;

    bool CheckCanSetSpeed(short speed);
    bool CheckCanSetGear(short gear);
    const string GetEngineState();
    const string GetDirrectionState();
    void DefineDirrection();
};

