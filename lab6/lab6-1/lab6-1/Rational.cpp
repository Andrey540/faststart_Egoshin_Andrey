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
	Assign(numerator, denominator);
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


CRational& CRational::operator+=(CRational const& rhs)
{
	Assign(rhs.m_numerator * m_denominator + 
		   rhs.m_denominator * m_numerator, 
		   m_denominator * rhs.m_denominator);

	return *this;
}

CRational& CRational::operator-=(CRational const & rhs)
{
	Assign(m_numerator * rhs.m_denominator - 
		   m_denominator * rhs.m_numerator, 
		   m_denominator * rhs.m_denominator);

	return *this;
}

CRational& CRational::operator*=(CRational const & rhs)
{
	Assign(rhs.m_numerator * m_numerator, rhs.m_denominator * m_denominator);
	return *this;
}

CRational& CRational::operator/=(CRational const & rhs)
{
    Assign(m_numerator * rhs.m_denominator, m_denominator * rhs.m_numerator);
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

double CRational::ToDouble()const
{
    return static_cast<double>(m_numerator) / static_cast<double>(m_denominator);
}

CRational const operator+(CRational lhs, CRational const & rhs)
{
	return lhs += rhs;
}

CRational const operator-(CRational lhs, CRational const & rhs)
{
	return lhs -= rhs;
}

CRational const operator*(CRational lhs, CRational const & rhs)
{
	return lhs *= rhs;
}

CRational const operator/(CRational lhs, CRational const & rhs)
{
	return lhs /= rhs;
}

std::istream & operator>>(std::istream & is, CRational & rhs)
{
    int numerator;
    int denominator;
    char delimiter;
    is >> numerator >> delimiter >> denominator;
    if (delimiter != '/')
    {
        throw std::domain_error("Incorrect delimeter");
    }
    rhs = CRational(numerator, denominator);
    return is;
}

std::ostream & operator<<(std::ostream & os, CRational const & rhs)
{
    os << rhs.GetNumerator() << "/" << rhs.GetDenominator();
    return os;
}

void CRational::Assign(int numerator, int denominator)
{
	if (denominator == 0)
	{
		throw std::invalid_argument("Denominator must not be zero");
	}
	if (denominator < 0)
	{
		numerator = -numerator;
		denominator = -denominator;
	}
	int gcd = GCD(std::abs(numerator), denominator);
	m_numerator = numerator / gcd;
	m_denominator = denominator / gcd;
}