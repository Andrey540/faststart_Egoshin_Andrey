#pragma once

#include <iostream>  

unsigned GCD(unsigned x, unsigned y);

class CRational
{
    friend std::ostream & operator<<(std::ostream & os, const CRational & rhs);
    friend std::istream & operator>>(std::istream & is, CRational & rhs);
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

	const CRational operator+(CRational const & rhs)const;
    const CRational operator-(CRational const & rhs)const;

    CRational& operator+=(CRational const & rhs);
    CRational& operator-=(CRational const & rhs);

    const CRational operator*(CRational const & rhs)const;
    const CRational operator/(CRational const & rhs)const;

    CRational& operator*=(CRational const & rhs);
    CRational& operator/=(CRational const & rhs);  

    bool operator<(CRational const & rhs)const;
    bool operator<=(CRational const & rhs)const;

    bool operator>(CRational const & rhs)const;
    bool operator>=(CRational const & rhs)const;   

private:
	int m_numerator;
	int m_denominator;
};