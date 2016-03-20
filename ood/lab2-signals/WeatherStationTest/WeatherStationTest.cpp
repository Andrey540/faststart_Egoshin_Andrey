// WeatherStationTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"
/*
class CTestDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestDisplay(CWeatherData & wd) : m_weatherData(wd){}
	void GetInterestData(SWeatherInfo & info) const override
	{
	}
	void Update(SWeatherInfo const& data, const std::string & stationName) override
	{
		std::cout << "Current Temp of test display " << data.temperature << std::endl;
		std::cout << "Current Hum of test display " << data.humidity << std::endl;
		std::cout << "Current Pressure of test display " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
		m_weatherData.RemoveObserver(*this);
	}
private:
	CWeatherData &m_weatherData;
};

BOOST_AUTO_TEST_CASE(IsRomoveIntoUppdateProcessCorrect)
{
	CWeatherData wd;

	CDisplay display1;
	wd.RegisterObserver(display1);

	CTestDisplay testDisplay(wd);
	wd.RegisterObserver(testDisplay);

	CDisplay display2;
	wd.RegisterObserver(display2);

	wd.SetMeasurements(3, 0.7, 760);
	std::cout << "+++++++++++++++++++++" << std::endl;
	wd.SetMeasurements(4, 0.8, 761);
	std::cout << "=====================" << std::endl;
}

BOOST_AUTO_TEST_CASE(IsPriorityWorksCorrect)
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 10);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, 20);

	CTestDisplay testDisplay(wd);
	wd.RegisterObserver(testDisplay, 30);

	wd.SetMeasurements(3, 0.7, 760);
	std::cout << "=====================" << std::endl;
}


BOOST_AUTO_TEST_CASE(IsDuoWorksCorrect)
{
	CWeatherData wdIn(std::string("in"));
	CWeatherData wdOut(std::string("out"));

	CDisplay display;
	wdIn.RegisterObserver(display, 10);
	wdOut.RegisterObserver(display, 10);

	wdIn.SetMeasurements(23, 0.6, 762);
	wdOut.SetMeasurements(3, 0.7, 760);
	std::cout << "=====================" << std::endl;
}

BOOST_AUTO_TEST_CASE(IsWindOrientationCalcCorrect)
{
	CWeatherDataPro wd;

	CStatsDisplay display;
	wd.RegisterObserver(display, 10);

	wd.SetMeasurements(23, 0.6, 762, 10, 45);
	wd.SetMeasurements(3, 0.7, 760, 10, 135);
	std::cout << "=====================" << std::endl;
}

BOOST_AUTO_TEST_CASE(IsProVersionWorksCorrect)
{
	CWeatherDataPro wdPro;
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display, 10);
	wdPro.RegisterObserver(display, 10);

	wd.SetMeasurements(23, 0.6, 762);
	wdPro.SetMeasurements(3, 0.7, 760, 10, 135);
	std::cout << "=====================" << std::endl;
}

BOOST_AUTO_TEST_CASE(IsEconomocalDisplayWorksCorrect)
{
	CWeatherEconomicalData wdEconomical;
	CWeatherData wd;

	CEconomicalDisplay display;
	wdEconomical.RegisterObserver(display, 10);

	wdEconomical.SetMeasurements(3, 0.7);
	std::cout << "=====================" << std::endl;

	display.SetNeedPressure(true);
	wdEconomical.SetMeasurements(13, 0.7);
	std::cout << "=====================" << std::endl;

	display.SetNeedTemperature(true);
	wdEconomical.SetMeasurements(23, 0.6);
	std::cout << "=====================" << std::endl;
}*/