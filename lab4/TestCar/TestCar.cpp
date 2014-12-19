// TestCar.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab4-1\Car.h"


struct JustCreatedCarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(JustCreatedCar, JustCreatedCarFixture)

	BOOST_AUTO_TEST_CASE(IsTurnedOff)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

    BOOST_AUTO_TEST_CASE(IsAtNeutralAndSpeed0)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanBeTurnedOn)
	{
		BOOST_CHECK(car.TurnOnEngine());
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithJustTurnedOnEngineFixture
{
	CCar car;
    CarWithJustTurnedOnEngineFixture()
	{
		car.TurnOnEngine();
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithJustTurnedOnEngine, CarWithJustTurnedOnEngineFixture)

	BOOST_AUTO_TEST_CASE(IsTurnedON)
	{
		BOOST_CHECK(car.IsTurnedOn());
	}

    BOOST_AUTO_TEST_CASE(IsAtNeutralAndSpeed0)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanBeTurnedOff)
	{
		BOOST_CHECK(car.TurnOffEngine());
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineFixture
{
	CCar car;
    CarWithTurnedOnEngineFixture()
	{
		car.TurnOnEngine();
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngine, CarWithTurnedOnEngineFixture)

	BOOST_AUTO_TEST_CASE(IsTurnedON)
	{
		BOOST_CHECK(car.IsTurnedOn());
	}

    BOOST_AUTO_TEST_CASE(CanBeTurnedOnJustTurnedOnCar)
	{
		BOOST_CHECK(!car.TurnOnEngine());
	}

    BOOST_AUTO_TEST_CASE(IsAtNeutralAndSpeed0)
	{
		BOOST_CHECK_EQUAL(car.GetGear(), 0);
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanBeTurnedOff)
	{
		BOOST_CHECK(car.TurnOffEngine());
        BOOST_CHECK(!car.IsTurnedOn());
	}

    BOOST_AUTO_TEST_CASE(CanBeTurnedOffJustTurnedOffCar)
	{
		BOOST_CHECK(car.TurnOffEngine());
        BOOST_CHECK(!car.TurnOffEngine());
	}

    BOOST_AUTO_TEST_CASE(CanSetSpeedAtGear0)
	{
        BOOST_CHECK(!car.SetSpeed(10));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetGearBack)
	{
        BOOST_CHECK(car.SetGear(-1));
        BOOST_CHECK_EQUAL(car.GetGear(), -1);
	}

    BOOST_AUTO_TEST_CASE(CanSetGearFront)
	{
        BOOST_CHECK(car.SetGear(1));
        BOOST_CHECK_EQUAL(car.GetGear(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGearBackFixture
{
	CCar car;
    CarWithTurnedOnEngineAtGearBackFixture()
	{
		car.TurnOnEngine();
        car.SetGear(-1);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGearBack, CarWithTurnedOnEngineAtGearBackFixture)

	BOOST_AUTO_TEST_CASE(CanSetSpeed20)
	{
		BOOST_CHECK(car.SetSpeed(20));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 20);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed21)
	{
		BOOST_CHECK(!car.SetSpeed(21));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear0)
	{
		BOOST_CHECK(car.SetGear(0));
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear1)
	{
		BOOST_CHECK(!car.SetGear(1));
        BOOST_CHECK_EQUAL(car.GetGear(), -1);
	}

    BOOST_AUTO_TEST_CASE(CantEngineOffAtSpeed20)
	{
		BOOST_CHECK(car.SetSpeed(20));
        BOOST_CHECK(!car.TurnOffEngine());
        BOOST_CHECK(car.IsTurnedOn());
	}

    BOOST_AUTO_TEST_CASE(CantSetGear2)
	{
		BOOST_CHECK(!car.SetGear(2));
        BOOST_CHECK_EQUAL(car.GetGear(), -1);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGear1Fixture
{
	CCar car;
    CarWithTurnedOnEngineAtGear1Fixture()
	{
		car.TurnOnEngine();
        car.SetGear(1);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGear1, CarWithTurnedOnEngineAtGear1Fixture)

	BOOST_AUTO_TEST_CASE(CanSetSpeed30)
	{
		BOOST_CHECK(car.SetSpeed(30));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed31)
	{
		BOOST_CHECK(!car.SetSpeed(31));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear0)
	{
		BOOST_CHECK(car.SetGear(0));
        BOOST_CHECK_EQUAL(car.GetGear(), 0);
	}

    BOOST_AUTO_TEST_CASE(CantSetGearBack)
	{
		BOOST_CHECK(!car.SetGear(-1));
        BOOST_CHECK_EQUAL(car.GetGear(), 1);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear2)
	{
		BOOST_CHECK(!car.SetGear(2));
        BOOST_CHECK_EQUAL(car.GetGear(), 1);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear2AtSpeed20)
	{
        BOOST_CHECK(car.SetSpeed(20));
		BOOST_CHECK(car.SetGear(2));
        BOOST_CHECK_EQUAL(car.GetGear(), 2);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear3AtSpeed30)
	{
        BOOST_CHECK(car.SetSpeed(30));
		BOOST_CHECK(car.SetGear(3));
        BOOST_CHECK_EQUAL(car.GetGear(), 3);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear4AtSpeed30)
	{
        BOOST_CHECK(car.SetSpeed(30));
		BOOST_CHECK(!car.SetGear(4));
        BOOST_CHECK_EQUAL(car.GetGear(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGear2AtSpeed30Fixture
{
	CCar car;
    CarWithTurnedOnEngineAtGear2AtSpeed30Fixture()
	{
		car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(2);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGear2AtSpeed30, CarWithTurnedOnEngineAtGear2AtSpeed30Fixture)

	BOOST_AUTO_TEST_CASE(CanSetGear1)
	{
		BOOST_CHECK(car.SetGear(1));
        BOOST_CHECK_EQUAL(car.GetGear(), 1);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear0)
	{
		BOOST_CHECK(!car.SetGear(0));
        BOOST_CHECK_EQUAL(car.GetGear(), 2);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed19)
	{
		BOOST_CHECK(!car.SetSpeed(19));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
	}

    BOOST_AUTO_TEST_CASE(CanSetSpeed50)
	{
		BOOST_CHECK(car.SetSpeed(50));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 50);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed51)
	{
		BOOST_CHECK(!car.SetSpeed(51));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear3AtSpeed50)
	{
		BOOST_CHECK(car.SetSpeed(50));
        BOOST_CHECK(car.SetGear(3));
        BOOST_CHECK_EQUAL(car.GetGear(), 3);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear4AtSpeed50)
	{
		BOOST_CHECK(car.SetSpeed(50));
        BOOST_CHECK(car.SetGear(4));
        BOOST_CHECK_EQUAL(car.GetGear(), 4);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear5AtSpeed50)
	{
		BOOST_CHECK(car.SetSpeed(50));
        BOOST_CHECK(car.SetGear(5));
        BOOST_CHECK_EQUAL(car.GetGear(), 5);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear4AtSpeed30)
	{
        BOOST_CHECK(!car.SetGear(4));
        BOOST_CHECK_EQUAL(car.GetGear(), 2);
	}

    BOOST_AUTO_TEST_CASE(CantSetGear5AtSpeed40)
	{
        BOOST_CHECK(!car.SetGear(5));
        BOOST_CHECK_EQUAL(car.GetGear(), 2);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGear3AtSpeed60Fixture
{
	CCar car;
    CarWithTurnedOnEngineAtGear3AtSpeed60Fixture()
	{
		car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGear3AtSpeed60, CarWithTurnedOnEngineAtGear3AtSpeed60Fixture)

	BOOST_AUTO_TEST_CASE(CanSetGear2AtSpeed60)
	{
		BOOST_CHECK(!car.SetGear(2));
        BOOST_CHECK_EQUAL(car.GetGear(), 3);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed29)
	{
		BOOST_CHECK(!car.SetSpeed(29));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed61)
	{
		BOOST_CHECK(!car.SetSpeed(61));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 60);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear2AtSpeed30)
	{
		BOOST_CHECK(car.SetSpeed(30));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 30);
        BOOST_CHECK(car.SetGear(2));
        BOOST_CHECK_EQUAL(car.GetGear(), 2);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGear4AtSpeed90Fixture
{
	CCar car;
    CarWithTurnedOnEngineAtGear4AtSpeed90Fixture()
	{
		car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);
        car.SetGear(4);
        car.SetSpeed(90);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGear4AtSpeed90, CarWithTurnedOnEngineAtGear4AtSpeed90Fixture)

	BOOST_AUTO_TEST_CASE(CanSetGear3AtSpeed90)
	{
		BOOST_CHECK(!car.SetGear(3));
        BOOST_CHECK_EQUAL(car.GetGear(), 4);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed39)
	{
		BOOST_CHECK(!car.SetSpeed(39));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed91)
	{
		BOOST_CHECK(!car.SetSpeed(91));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 90);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear3AtSpeed40)
	{
		BOOST_CHECK(car.SetSpeed(40));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 40);
        BOOST_CHECK(car.SetGear(3));
        BOOST_CHECK_EQUAL(car.GetGear(), 3);
	}

BOOST_AUTO_TEST_SUITE_END()

struct CarWithTurnedOnEngineAtGear5AtSpeed150Fixture
{
	CCar car;
    CarWithTurnedOnEngineAtGear5AtSpeed150Fixture()
	{
		car.TurnOnEngine();
        car.SetGear(1);
        car.SetSpeed(30);
        car.SetGear(3);
        car.SetSpeed(60);
        car.SetGear(5);
        car.SetSpeed(150);
	}    
};

BOOST_FIXTURE_TEST_SUITE(CarWithTurnedOnEngineAtGear5AtSpeed150, CarWithTurnedOnEngineAtGear5AtSpeed150Fixture)

	BOOST_AUTO_TEST_CASE(CanSetGear4AtSpeed150)
	{
		BOOST_CHECK(!car.SetGear(4));
        BOOST_CHECK_EQUAL(car.GetGear(), 5);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed49)
	{
		BOOST_CHECK(!car.SetSpeed(49));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
	}

    BOOST_AUTO_TEST_CASE(CantSetSpeed151)
	{
		BOOST_CHECK(!car.SetSpeed(151));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 150);
	}

    BOOST_AUTO_TEST_CASE(CanSetGear4AtSpeed80)
	{
		BOOST_CHECK(car.SetSpeed(80));
        BOOST_CHECK_EQUAL(car.GetSpeed(), 80);
        BOOST_CHECK(car.SetGear(4));
        BOOST_CHECK_EQUAL(car.GetGear(), 4);
	}

BOOST_AUTO_TEST_SUITE_END()