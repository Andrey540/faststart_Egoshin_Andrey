#include "WeatherData.h"

#pragma warning(disable:4996)

int main()
{
	CWeatherData wdIn("In");

	CDisplay display;
	CStatsDisplay statsDisplay;

	wdIn.SubscribeToTemperature(boost::bind(&CDisplay::OnUpdateTemperature, &display, _1, _2));
	wdIn.SubscribeToHumidity(boost::bind(&CDisplay::OnUpdateHumidity, &display, _1, _2));
	wdIn.SubscribeToPressure(boost::bind(&CDisplay::OnUpdatePressure, &display, _1, _2));

	wdIn.SubscribeToTemperature(boost::bind(&CStatsDisplay::OnUpdateTemperature, &statsDisplay, _1, _2));
	wdIn.SubscribeToHumidity(boost::bind(&CStatsDisplay::OnUpdateHumidity, &statsDisplay, _1, _2));
	auto pressureConnection = wdIn.SubscribeToPressure(boost::bind(&CStatsDisplay::OnUpdatePressure, &statsDisplay, _1, _2));

	wdIn.SetMeasurements(3, 0.7, 760);
	wdIn.SetMeasurements(4, 0.8, 761);

	pressureConnection.disconnect();
	
	wdIn.SetMeasurements(10, 0.8, 761);
	wdIn.SetMeasurements(-10, 0.8, 761);
	

	CWeatherDataPro wdOut("Out");

	wdOut.SubscribeToTemperature(boost::bind(&CDisplay::OnUpdateTemperature, &display, _1, _2));
	wdOut.SubscribeToHumidity(boost::bind(&CDisplay::OnUpdateHumidity, &display, _1, _2));
	wdOut.SubscribeToPressure(boost::bind(&CDisplay::OnUpdatePressure, &display, _1, _2));
	wdOut.SubscribeToWindSpeed(boost::bind(&CDisplay::OnUpdateWindSpeed, &display, _1, _2));
	wdOut.SubscribeToWindOrientation(boost::bind(&CDisplay::OnUpdateWindOrientation, &display, _1, _2, _3));

	wdOut.SubscribeToTemperature(boost::bind(&CStatsDisplay::OnUpdateTemperature, &statsDisplay, _1, _2));
	wdOut.SubscribeToHumidity(boost::bind(&CStatsDisplay::OnUpdateHumidity, &statsDisplay, _1, _2));
	wdOut.SubscribeToPressure(boost::bind(&CStatsDisplay::OnUpdatePressure, &statsDisplay, _1, _2));
	wdOut.SubscribeToWindSpeed(boost::bind(&CStatsDisplay::OnUpdateWindSpeed, &statsDisplay, _1, _2));
	wdOut.SubscribeToWindOrientation(boost::bind(&CStatsDisplay::OnUpdateWindOrientation, &statsDisplay, _1, _2, _3));

	wdOut.SetMeasurements(3, 0.7, 760, 10, 45);
	wdOut.SetMeasurements(4, 0.8, 761, 5, 60);

	wdOut.SetMeasurements(10, 0.8, 761, 4, 70);
	wdOut.SetMeasurements(-10, 0.8, 761, 3, 90);
	
	return 0;
}