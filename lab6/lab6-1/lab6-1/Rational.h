#pragma once

#include <iostream>  

unsigned GCD(unsigned x, unsigned y);

class CRational
{
public:

	CRational(int numerator = 0, int denominator = 1);

	// Возвращаем числитель
	int GetNumerator()const;

	// Возвращаем знаменатель
	int GetDenominator()const;
	
	bool operator==(CRational const & rhs)const;
	bool operator!=(CRational const & rhs)const;

    CRational& operator-();
    CRational& operator+();

    CRational& operator+=(CRational const & rhs);
    CRational& operator-=(CRational const & rhs);
    CRational& operator*=(CRational const & rhs);
    CRational& operator/=(CRational const & rhs);  

    bool operator<(CRational const & rhs)const;
    bool operator<=(CRational const & rhs)const;

    bool operator>(CRational const & rhs)const;
    bool operator>=(CRational const & rhs)const;   

    double ToDouble()const;

private:
    void Assign(int numerator, int denominator);

	int m_numerator;
	int m_denominator;
};

CRational const operator+(CRational lhs, CRational const & rhs);
CRational const operator-(CRational lhs, CRational const & rhs);
CRational const operator*(CRational lhs, CRational const & rhs);
CRational const operator/(CRational lhs, CRational const & rhs);

std::ostream & operator<<(std::ostream & os, const CRational & rhs);
std::istream & operator>>(std::istream & is, CRational & rhs);