#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include <boost\signals2.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Observer.h"

using namespace std;

class IProvidableName
{
public:
	virtual ~IProvidableName() = default;
	virtual const std::string& GetName() const = 0;
};

typedef boost::signals2::signal<void(double, const IProvidableName&)> UpdateHandlerSingle;
typedef boost::signals2::signal<void(double, double, const IProvidableName&)> UpdateHandlerDouble;

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
		double y = speed * sin(orientation * M_PI / 180);		
		double x = speed * cos(orientation * M_PI / 180);

		m_calcX += x;
		m_calcY += y;
	}
	void PrintData()
	{
		std::cout << "Max " << m_name << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name << " " << std::atan2(m_calcY, m_calcX) * 180 / M_PI  << std::endl;
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
		std::cout << "Max " << m_name << " " << m_maxValue << std::endl;
		std::cout << "Min " << m_name << " " << m_minValue << std::endl;
		std::cout << "Average " << m_name << " " << (m_accValue / m_countAcc) << std::endl;
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
	void OnUpdateTemperature(double data, const IProvidableName & providableName)
	{
		PrintStationName(providableName);
		std::cout << "Current Temp " << data << std::endl;
	}
	void OnUpdateHumidity(double data, const IProvidableName & providableName)
	{
		PrintStationName(providableName);
		std::cout << "Current Hum " << data << std::endl;
	}
	void OnUpdatePressure(double data, const IProvidableName & providableName)
	{
		PrintStationName(providableName);
		std::cout << "Current Pressure " << data << std::endl;
	}
	void OnUpdateWindSpeed(double data, const IProvidableName & providableName)
	{
		PrintStationName(providableName);
		std::cout << "Current Wind Speed " << data << std::endl;
	}
	void OnUpdateWindOrientation(double speed, double orientation, const IProvidableName & providableName)
	{
		PrintStationName(providableName);
		std::cout << "Current Wind Orientation " << orientation << std::endl;
	}
private:
	void PrintStationName(const IProvidableName & providableName)
	{
		std::cout << "Data from " << providableName.GetName() << " station" << std::endl;
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
	void OnUpdateTemperature(double data, const IProvidableName & providableName)
	{
		m_temperature.UpdateData(data);
		m_temperature.PrintData();
	}
	void OnUpdateHumidity(double data, const IProvidableName & providableName)
	{
		m_humidity.UpdateData(data);
		m_humidity.PrintData();
	}
	void OnUpdatePressure(double data, const IProvidableName & providableName)
	{
		m_pressure.UpdateData(data);
		m_pressure.PrintData();
	}
	void OnUpdateWindSpeed(double data, const IProvidableName & providableName)
	{
		m_windSpeed.UpdateData(data);
		m_windSpeed.PrintData();
	}
	void OnUpdateWindOrientation(double speed, double orientation, const IProvidableName & providableName)
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


class CWeatherEconomicalData : public IProvidableName
{
public:

	CWeatherEconomicalData(std::string name = "") : m_name(move(name)) {}
	void SetMeasurements(double temp, double pressure)
	{
		m_temperature = temp;
		m_pressure    = pressure;

		MeasurementsChanged();
	}

	boost::signals2::connection SubscribeToTemperature(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigTemperature.connect(priority, handler);
	}
	boost::signals2::connection SubscribeToPressure(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigPressure.connect(priority, handler);
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void NotifyObservers()
	{
		if (m_temperature != m_prevTemperature)
		{
			m_sigTemperature(m_temperature, *this);
			m_prevTemperature = m_temperature;
		}
		if (m_pressure != m_prevPressure)
		{
			m_sigPressure(m_pressure, *this);
			m_prevPressure = m_pressure;
		}
	}

	const std::string& GetName() const override
	{
		return m_name;
	}

private:	
	double m_temperature = 0.0;
	double m_prevTemperature = 0.0;
	double m_prevPressure = 0.0;
	double m_pressure = 760.0;

	std::string m_name;

	UpdateHandlerSingle m_sigTemperature;
	UpdateHandlerSingle m_sigPressure;
};

class CWeatherData : public IProvidableName
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

	boost::signals2::connection SubscribeToTemperature(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigTemperature.connect(priority, handler);
	}
	boost::signals2::connection SubscribeToHumidity(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigHumidity.connect(priority, handler);
	}
	boost::signals2::connection SubscribeToPressure(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigPressure.connect(priority, handler);
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	virtual void NotifyObservers()
	{
		m_sigTemperature(m_temperature, *this);
		m_sigHumidity(m_humidity, *this);
		m_sigPressure(m_pressure, *this);
	}

	const std::string& GetName() const
	{
		return m_name;
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

	boost::signals2::connection SubscribeToWindSpeed(UpdateHandlerSingle::slot_type handler, int priority = 0)
	{
		return m_sigWindSpeed.connect(priority, handler);
	}
	boost::signals2::connection SubscribeToWindOrientation(UpdateHandlerDouble::slot_type handler, int priority = 0)
	{
		return m_sigWindOrientation.connect(priority, handler);
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

		m_sigWindSpeed(m_windSpeed, *this);
		m_sigWindOrientation(m_windSpeed, m_windOrientation, *this);
	}
private:
	double m_windSpeed = 0;
	double m_windOrientation = 0;

	UpdateHandlerSingle m_sigWindSpeed;
	UpdateHandlerDouble m_sigWindOrientation;
};
