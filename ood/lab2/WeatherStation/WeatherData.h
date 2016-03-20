#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

using namespace std;

struct SWeatherEconomicalInfo
{
	double temperature = 0;
	double pressure = 0;
};

struct SWeatherInfo : public SWeatherEconomicalInfo
{
	double humidity = 0;
};

struct SWeatherInfoPro : public SWeatherInfo
{
	double windSpeed = 0;
	double windOrientation = 0;
};

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

class CEconomicalDisplay : public IObserver<SWeatherEconomicalInfo>
{
public:
	void SetNeedTemperature(bool needTemperature)
	{
		m_needTemperature = needTemperature;
	}
	void SetNeedPressure(bool needPressure)
	{
		m_needPressure = needPressure;
	}
	void GetInterestData(SWeatherEconomicalInfo & info) const override
	{
		info.temperature = m_needTemperature;
		info.pressure = m_needPressure;
	}
	void Update(SWeatherEconomicalInfo const& data, const std::string & stationName) override
	{
		if (stationName.size() > 0)
		{
			std::cout << "Data from " << stationName.c_str() << " station" << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
private:
	bool m_needTemperature = false;
	bool m_needPressure = false;
};

class CDisplay : public IDuoObserver<SWeatherInfo, SWeatherInfoPro>
{
public:
	void GetInterestData(SWeatherInfo & info) const override {}
	void GetInterestData(SWeatherInfoPro & info) const override {}
	void Update(SWeatherInfo const& data, const std::string & stationName) override
	{
		if (stationName.size() > 0)
		{
			std::cout << "Data from " << stationName.c_str() << " station" << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
	void Update(SWeatherInfoPro const& data, const std::string & stationName) override
	{
		Update(static_cast<SWeatherInfo>(data), stationName);

		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Orientation " << data.windOrientation << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IDuoObserver<SWeatherInfo, SWeatherInfoPro>
{
public:
	CStatsDisplay() : m_temperature(std::string("Temperature")),
					  m_humidity(std::string("Humidity")),
					  m_pressure(std::string("Pressure")),
					  m_windSpeed(std::string("Wind Speed")),
					  m_windOrientation(std::string("Wind Orientation"))
	{}
	void GetInterestData(SWeatherInfo & info) const override {}
	void GetInterestData(SWeatherInfoPro & info) const override {}
	void Update(SWeatherInfo const& data, const std::string & name) override
	{
		m_temperature.UpdateData(data.temperature);
		m_humidity.UpdateData(data.humidity);
		m_pressure.UpdateData(data.pressure);

		m_temperature.PrintData();
		m_humidity.PrintData();
		m_pressure.PrintData();
	}
	void Update(SWeatherInfoPro const& data, const std::string & name) override
	{
		Update(static_cast<SWeatherInfo>(data), name);

		m_windSpeed.UpdateData(data.windSpeed);
		m_windOrientation.UpdateData(data.windSpeed, data.windOrientation);

		m_windSpeed.PrintData();
		m_windOrientation.PrintData();
	}
private:
	CStatsData m_temperature;
	CStatsData m_humidity;
	CStatsData m_pressure;
	CStatsData m_windSpeed;
	CStatsWindOrientation m_windOrientation;
};

class CWeatherEconomicalData : public CObservable<SWeatherEconomicalInfo>
{
public:
	CWeatherEconomicalData(std::string name = "") : CObservable(move(name)) {}
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double pressure)
	{
		m_prevInfo = GetChangedData();
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherEconomicalInfo GetChangedData() const override
	{
		SWeatherEconomicalInfo info;
		info.temperature = GetTemperature();
		info.pressure = GetPressure();
		return info;
	}
	bool IsNeedUpdateObserver(const ObserverType & observer) const override
	{
		bool result = false;
		SWeatherEconomicalInfo needInfo;
		observer.GetInterestData(needInfo);
		if (needInfo.temperature && (GetTemperature() != m_prevInfo.temperature))
		{
			result = true;
		}
		else if (needInfo.pressure && (GetPressure() != m_prevInfo.pressure))
		{
			result = true;
		}
		return result;
	}
private:
	SWeatherEconomicalInfo m_prevInfo;
	double m_temperature = 0.0;
	double m_pressure = 760.0;
};


class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	CWeatherData(std::string name = "") : CObservable(move(name)) {}
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
	bool IsNeedUpdateObserver(const ObserverType & observer) const override
	{
		return true;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class CWeatherDataPro : public CObservable<SWeatherInfoPro>
{
public:
	CWeatherDataPro(std::string name = "") : CObservable(move(name)) {}
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	double GetWindSpeed()const
	{
		return m_windSpeed;
	}

	double GetWindOrientation()const
	{
		return m_windOrientation;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed = 0, double windOrientation = 0)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windOrientation = windOrientation;

		MeasurementsChanged();
	}
protected:
	SWeatherInfoPro GetChangedData()const override
	{
		SWeatherInfoPro info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windSpeed = GetWindSpeed();
		info.windOrientation = GetWindOrientation();
		return info;
	}
	bool IsNeedUpdateObserver(const ObserverType & observer) const override
	{
		return true;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windOrientation = 0;
};
