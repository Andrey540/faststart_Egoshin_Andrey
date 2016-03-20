#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <boost\signals2.hpp>
#include "Observer.h"

using namespace std;

typedef boost::signals2::signal<void(double, const std::string&)> UpdateHandlerSingle;
typedef boost::signals2::signal<void(double, double, const std::string&)> UpdateHandlerDouble;

class CStatsWindOrientation
{
public:
	CStatsWindOrientation(std::string && name) : m_name(move(name)) {}
	void UpdateData(double speed, double orientation)
	{
		if (m_minValue > orientation)
		{
			m_minValue = orientation;
		}
		if (m_maxValue < orientation)
		{
			m_maxValue = orientation;
		}
		double y = speed * sin(orientation / 100);
		double x = speed * cos(orientation / 100);
		m_calcX += x;
		m_calcY += y;
	}
	void PrintData()
	{
		std::cout << "Max " << m_name.c_str() << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name.c_str() << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name.c_str() << " " << atan(m_calcY / m_calcX) * 100 << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	std::string m_name;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_calcX = 0;
	double m_calcY = 0;
};

class CStatsData
{
public:
	CStatsData(std::string && name) : m_name(move(name)) {}
	void UpdateData(double value)
	{
		if (m_minValue > value)
		{
			m_minValue = value;
		}
		if (m_maxValue < value)
		{
			m_maxValue = value;
		}
		m_accValue += value;
		++m_countAcc;
	}
	void PrintData()
	{
		std::cout << "Max " << m_name.c_str() << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name.c_str() << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name.c_str() << " " << (m_accValue / m_countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	std::string m_name;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CDisplay
{
public:
	void OnUpdateTemperature(double data, const std::string & stationName)
	{
		PrintStationName(stationName);
		std::cout << "Current Temp " << data << std::endl;
	}
	void OnUpdateHumidity(double data, const std::string & stationName)
	{
		PrintStationName(stationName);
		std::cout << "Current Hum " << data << std::endl;
	}
	void OnUpdatePressure(double data, const std::string & stationName)
	{
		PrintStationName(stationName);
		std::cout << "Current Pressure " << data << std::endl;
	}
	void OnUpdateWindSpeed(double data, const std::string & stationName)
	{
		PrintStationName(stationName);
		std::cout << "Current Wind Speed " << data << std::endl;
	}
	void OnUpdateWindOrientation(double speed, double orientation, const std::string & stationName)
	{
		PrintStationName(stationName);
		std::cout << "Current Wind Orientation " << orientation << std::endl;
	}
private:
	void PrintStationName(const std::string & stationName)
	{
		if (stationName.size() > 0)
		{
			std::cout << "Data from " << stationName.c_str() << " station" << std::endl;
		}
	}
};

class CStatsDisplay
{
public:
	CStatsDisplay() : m_temperature(std::string("Temperature")),
					  m_humidity(std::string("Humidity")),
					  m_pressure(std::string("Pressure")),
					  m_windSpeed(std::string("Wind Speed")),
					  m_windOrientation(std::string("Wind Orientation"))
	{}
	void OnUpdateTemperature(double data, const std::string & name)
	{
		m_temperature.UpdateData(data);
		m_temperature.PrintData();
	}
	void OnUpdateHumidity(double data, const std::string & name)
	{
		m_humidity.UpdateData(data);
		m_humidity.PrintData();
	}
	void OnUpdatePressure(double data, const std::string & name)
	{
		m_pressure.UpdateData(data);
		m_pressure.PrintData();
	}
	void OnUpdateWindSpeed(double data, const std::string & name)
	{
		m_windSpeed.UpdateData(data);
		m_windSpeed.PrintData();
	}
	void OnUpdateWindOrientation(double speed, double orientation, const std::string & name)
	{
		m_windOrientation.UpdateData(speed, orientation);
		m_windOrientation.PrintData();
	}
private:
	CStatsData m_temperature;
	CStatsData m_humidity;
	CStatsData m_pressure;
	CStatsData m_windSpeed;
	CStatsWindOrientation m_windOrientation;
};

class CWeatherData
{
public:

	CWeatherData(std::string name = "") : m_name(move(name)) {}
	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}

	void SubscribeToTemperature(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		m_sigTemperature.connect(priority, handler);
	}
	void SubscribeToHumidity(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		m_sigHumidity.connect(priority, handler);
	}
	void SubscribeToPressure(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		m_sigPressure.connect(priority, handler);
	}
	void UnsubscribeFromTEmperature(const UpdateHandlerSingle::slot_function_type & handler)
	{
		//m_sigTemperature.disconnect(handler);
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	virtual void NotifyObservers()
	{
		m_sigTemperature(m_temperature, m_name);
		m_sigHumidity(m_humidity, m_name);
		m_sigPressure(m_pressure, m_name);
	}

protected:
	std::string m_name;

private:	
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;

	UpdateHandlerSingle m_sigTemperature;
	UpdateHandlerSingle m_sigHumidity;
	UpdateHandlerSingle m_sigPressure;
};

class CWeatherDataPro : public CWeatherData
{
public:
	CWeatherDataPro(std::string name = "") : CWeatherData(move(name)) {}

	void SubscribeToWindSpeed(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		m_sigWindSpeed.connect(priority, handler);
	}
	void SubscribeToWindOrientation(UpdateHandlerDouble::slot_type handler, int priority = 0)
	{
		m_sigWindOrientation.connect(priority, handler);
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed = 0, double windOrientation = 0)
	{		
		m_windSpeed = windSpeed;
		m_windOrientation = windOrientation;

		CWeatherData::SetMeasurements(temp, humidity, pressure);
	}

	virtual void NotifyObservers() override
	{
		CWeatherData::NotifyObservers();

		m_sigWindSpeed(m_windSpeed, m_name);
		m_sigWindOrientation(m_windSpeed, m_windOrientation, m_name);
	}
private:
	double m_windSpeed = 0;
	double m_windOrientation = 0;

	UpdateHandlerSingle m_sigWindSpeed;
	UpdateHandlerDouble m_sigWindOrientation;
};
