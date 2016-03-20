#include "WeatherData.h"

int main()
{
	CWeatherDataPro wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 10, 50);
	wd.SetMeasurements(4, 0.8, 761, 8, 45);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 9, 35);
	wd.SetMeasurements(-10, 0.8, 761, 4, 75);
	return 0;
}