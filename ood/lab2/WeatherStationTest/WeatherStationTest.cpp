// WeatherStationTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\WeatherStation\WeatherData.h"

class CTestDisplay : public IObserver<SWeatherInfo>
{
public:
	CTestDisplay(CWeatherData & wd) : m_weatherData(wd){}
	void Update(SWeatherInfo const& data) override
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
	CTestDisplay testDisplay(wd);
	wd.RegisterObserver(testDisplay);

	CDisplay display;
	wd.RegisterObserver(display);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);
}


