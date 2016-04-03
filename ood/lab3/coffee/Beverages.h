#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override
	{
		return m_description;
	}
private:
	std::string m_description;
};

enum class CoffePortionType
{
	Normal,	// Обычный
	Double,	// Двойной
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino() 
		:CCoffee("Capuccino") 
	{}

	CCapuccino(CoffePortionType portionType)
		:CCoffee("Capuccin"),
		m_portionType(portionType)
	{}

	std::string GetDescription() const override
	{
		return (isDoublePortion() ? "Double " : "") + CCoffee::GetDescription();
	}

	double GetCost() const override 
	{
		return isDoublePortion() ? 120 : 80;
	}
private:
	CoffePortionType m_portionType;

	bool isDoublePortion() const
	{
		return m_portionType == CoffePortionType::Double;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte() 
		:CCoffee("Latte") 
	{}

	CLatte(CoffePortionType portionType)
		:CCoffee("Latte"),
		m_portionType(portionType)
	{}

	std::string GetDescription() const override
	{
		return (isDoublePortion() ? "Double " : "") + CCoffee::GetDescription();
	}

	double GetCost() const override 
	{
		return isDoublePortion() ? 130 : 90;
	}

private:
	CoffePortionType m_portionType;

	bool isDoublePortion() const
	{
		return m_portionType == CoffePortionType::Double;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea() 
		:CBeverage("Tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};


class CGreenTea : public CBeverage
{
public:
	CGreenTea()
		:CBeverage("Green tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class CYellowTea : public CBeverage
{
public:
	CYellowTea()
		:CBeverage("Yellow tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class COolongTea : public CBeverage
{
public:
	COolongTea()
		:CBeverage("Oolong tea") 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

enum class MilkshakePortionType
{
	Little,
	Middle,
	Big
};

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake() 
		:CBeverage("Milkshake") 
	{}
	
	CMilkshake(MilkshakePortionType portionType)
		:CBeverage("Milkshake"),
		m_portionType(portionType)
	{}
	
	std::string GetDescription() const override
	{
		std::string descriptionPrefix;
		if (m_portionType == MilkshakePortionType::Little)
		{
			descriptionPrefix = "Little ";
		}
		else if (m_portionType == MilkshakePortionType::Big)
		{
			descriptionPrefix = "Big ";
		}
		return descriptionPrefix + CBeverage::GetDescription();
	}

	double GetCost() const override 
	{ 
		if (m_portionType == MilkshakePortionType::Little)
		{
			return 50;
		}
		else if (m_portionType == MilkshakePortionType::Big)
		{
			return 80;
		}
		return 60; 
	}
	
private:	
	MilkshakePortionType m_portionType;
};
