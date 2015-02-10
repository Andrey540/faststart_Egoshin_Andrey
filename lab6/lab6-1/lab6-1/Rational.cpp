#include "stdafx.h"
#include "Rational.h"
#include <exception>
#include <iostream>     
#include <algorithm>   

using namespace std;

unsigned GCD(unsigned x, unsigned y)
{
	while (x != 0)
	{
		swap(x, y);
		x %= y;
	}
	return y;
}

CRational::CRational(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw invalid_argument("Denominator must not be zero");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	int gcd = GCD(abs(numerator), abs(denominator));
	m_numerator = numerator / gcd;
	m_denominator = denominator / gcd;
}

// Возвращаем числитель
int CRational::GetNumerator()const
{
	return m_numerator;
}

// Возвращаем знаменатель
int CRational::GetDenominator()const
{
	return m_denominator;
}

bool CRational::operator==(CRational const & rhs)const
{
	return (rhs.m_numerator == m_numerator && 
			rhs.m_denominator == m_denominator);
}

bool CRational::operator!=(CRational const & rhs)const
{
	return !(*this == rhs);
}

CRational& CRational::operator-()
{
    m_numerator = -m_numerator;
    return *this;
}

CRational& CRational::operator+()
{
    return *this;
}

const CRational CRational::operator + (CRational const & rhs)const
{
	return CRational(
		m_numerator * rhs.m_denominator + rhs.m_numerator * m_denominator, 
		m_denominator * rhs.m_denominator		
	);
}

const CRational CRational::operator - (CRational const & rhs)const
{
	return CRational(
		m_numerator * rhs.m_denominator - rhs.m_numerator * m_denominator, 
		m_denominator * rhs.m_denominator		
	);
}

CRational& CRational::operator+=(CRational const & rhs)
{
    *this = *this + rhs;
    return *this;
}

CRational& CRational::operator-=(CRational const & rhs)
{
    *this = *this - rhs;
    return *this;
}

const CRational CRational::operator*(CRational const & rhs)const
{
	return CRational(
		m_numerator * rhs.m_numerator, 
		m_denominator * rhs.m_denominator		
	);
}

const CRational CRational::operator/(CRational const & rhs)const
{
    return CRational(
		m_numerator * rhs.m_denominator, 
		m_denominator * rhs.m_numerator		
	);
}

CRational& CRational::operator*=(CRational const & rhs)
{
    *this = *this * rhs;
    return *this;
}

CRational& CRational::operator/=(CRational const & rhs)
{
    *this = *this / rhs;
    return *this;
}

bool CRational::operator<(CRational const & rhs)const
{
    return (m_numerator * rhs.m_denominator) < (rhs.m_numerator * m_denominator);
}

bool CRational::operator<=(CRational const & rhs)const
{
    return (*this < rhs) || (*this == rhs);
}

bool CRational::operator>(CRational const & rhs)const
{
    return !(*this <= rhs);
}

bool CRational::operator>=(CRational const & rhs)const
{
    return !(*this < rhs);
}

std::istream & operator>>(std::istream & is, CRational & rhs)
{
    int numerator;
    int denominator;
    char delimiter;
    is >> numerator >> delimiter >> denominator;
    rhs = CRational(numerator, denominator);
    return is;
}

std::ostream & operator<<(std::ostream & os, CRational const & rhs)
{
    os << rhs.GetNumerator() << "/" << rhs.GetDenominator();
    return os;
}