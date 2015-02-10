// lab6-1Test.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "..\lab6-1\Rational.h"


BOOST_AUTO_TEST_SUITE(Rational)

// ������������ ����� �� ��������� ����� 0/1
BOOST_AUTO_TEST_CASE(RationalIs0_1ByDefault)
{
	CRational const r;
	BOOST_CHECK_EQUAL(r.GetNumerator(), 0);
	BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
}

// ����� ����� N �������� ������������ ���� N/1
BOOST_AUTO_TEST_CASE(IntegerIsRational_N_1)
{
	{
		CRational const r(42);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 42);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
	}

	{
		CRational const r(0);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 0);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
	}

	{
		CRational const r(-42);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -42);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 1);
	}
}

// ������� ����� N / M �������� ������������ ���� N/M
BOOST_AUTO_TEST_CASE(FractionIsRational_N_M)
{
	{
		CRational const r(-42, 5);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -42);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 5);
	}
}

// ������������ ����� ����� ���� ����� �� ��������� � �����������
BOOST_AUTO_TEST_CASE(RationalsEquality)
{
	BOOST_CHECK(CRational(2, 3) == CRational(2, 3));
	BOOST_CHECK(!(CRational(2, 3) == CRational(5, 8)));
	BOOST_CHECK(!(CRational(2, 5) == CRational(2, 3)));
	BOOST_CHECK(!(CRational(2, 3) == CRational(1, 3)));
}

// ������������ ����� �� ����� ���� �� ����� �� ���������
// ���� �� ����� �� �����������
BOOST_AUTO_TEST_CASE(RationalsInequality)
{
	BOOST_CHECK(!(CRational(2, 3) != CRational(2, 3)));
	BOOST_CHECK(CRational(2, 3) != CRational(5, 8));
	BOOST_CHECK(CRational(2, 5) != CRational(2, 3));
	BOOST_CHECK(CRational(2, 3) != CRational(1, 3));
}

// ������� �����
BOOST_AUTO_TEST_CASE(UnaryMinus)
{
	BOOST_CHECK(-CRational(1, 2) == CRational(-1, 2));
    BOOST_CHECK(-CRational(-1, 2) == CRational(1, 2));
}

// ������� ����
BOOST_AUTO_TEST_CASE(UnaryPlus)
{
	BOOST_CHECK(+CRational(1, 2) == CRational(1, 2));
    BOOST_CHECK(+CRational(-1, 2) == CRational(-1, 2));
}

// �������� ������ � ������������� �������������
BOOST_AUTO_TEST_CASE(Sum)
{
	BOOST_CHECK(CRational(1, 2) + CRational(1, 3) == CRational(5, 6));

    {
        CRational r(1, 2);
        r += CRational(1, 3);
	    BOOST_CHECK(r == CRational(5, 6));
    }
}

// ��������� ������ � ������������� �������������
BOOST_AUTO_TEST_CASE(Difference)
{
	BOOST_CHECK(CRational(1, 2) - CRational(1, 3) == CRational(1, 6));
	BOOST_CHECK(CRational(1, 2) - CRational(2, 3) == CRational(-1, 6));
	BOOST_CHECK(CRational(1, 1) - CRational(1, 1) == CRational(0, 1));
	BOOST_CHECK(CRational(1, 2) - CRational(1, 6) == CRational(1, 3));
}

// ��������� ������ � ������������� �������������
BOOST_AUTO_TEST_CASE(Multiple)
{
	BOOST_CHECK(CRational(1, 2) * CRational(1, 3) == CRational(1, 6));
    BOOST_CHECK(CRational(1, 2) * CRational(-1, 3) == CRational(-1, 6));
    BOOST_CHECK(CRational(-1, 2) * CRational(-1, 3) == CRational(1, 6));
    BOOST_CHECK(CRational(3, 2) * CRational(2, 3) == CRational(1, 1));

    {
        CRational r(1, 2);
        r *= CRational(1, 3);
	    BOOST_CHECK(r == CRational(1, 6));
    }
}

// ������� ������ � ������������� �������������
BOOST_AUTO_TEST_CASE(Division)
{
	BOOST_CHECK(CRational(1, 2) / CRational(1, 3) == CRational(3, 2));
    BOOST_CHECK(CRational(1, 2) / CRational(-1, 3) == CRational(-3, 2));
    BOOST_CHECK(CRational(-1, 2) / CRational(-1, 3) == CRational(3, 2));
    BOOST_CHECK(CRational(3, 2) / CRational(2, 3) == CRational(9, 4));

    {
        CRational r(3, 2);
        r /= CRational(2, 3);
	    BOOST_CHECK(r == CRational(9, 4));
    }
}

// ������ ����� ������ ������
BOOST_AUTO_TEST_CASE(FirstLessThanSecond)
{
	BOOST_CHECK(CRational(1, 2) < CRational(3, 2));
    BOOST_CHECK(CRational(-1, 2) < CRational(-1, 3));
    BOOST_CHECK(CRational(-1, 2) < CRational(1, 3));
    BOOST_CHECK(!(CRational(1, 2) < CRational(1, 2)));
}

// ������ ����� ������ ��� ����� ������
BOOST_AUTO_TEST_CASE(FirstLessOrEqualSecond)
{
	BOOST_CHECK(CRational(1, 2) <= CRational(3, 2));
    BOOST_CHECK(CRational(-1, 2) <= CRational(-1, 3));
    BOOST_CHECK(CRational(-1, 2) <= CRational(1, 3));
    BOOST_CHECK(CRational(1, 2) <= CRational(1, 2));
}

// ������ ����� ������ ������
BOOST_AUTO_TEST_CASE(FirstGreaterThanSecond)
{
	BOOST_CHECK(CRational(3, 2) > CRational(1, 2));
    BOOST_CHECK(CRational(-1, 3) > CRational(-1, 2));
    BOOST_CHECK(CRational(1, 3) > CRational(-1, 2));
    BOOST_CHECK(!(CRational(1, 2) > CRational(1, 2)));
}

// ������ ����� ������ ��� ����� ������
BOOST_AUTO_TEST_CASE(FirstGreaterOrEqualSecond)
{
	BOOST_CHECK(CRational(3, 2) >= CRational(1, 2));
    BOOST_CHECK(CRational(-1, 3) >= CRational(-1, 2));
    BOOST_CHECK(CRational(1, 3) >= CRational(-1, 2));
    BOOST_CHECK(CRational(1, 2) >= CRational(1, 2));
    CRational r = CRational(-1, 2);
    std::cout << r;
}

BOOST_AUTO_TEST_CASE(ComputeGcd)
{
	BOOST_CHECK_EQUAL(GCD(6, 8), 2);
	BOOST_CHECK_EQUAL(GCD(0, 8), 8);
	BOOST_CHECK_EQUAL(GCD(0, 0), 0);
	BOOST_CHECK_EQUAL(GCD(3, 5), 1);
	BOOST_CHECK_EQUAL(GCD(1, 1), 1);
	BOOST_CHECK_EQUAL(GCD(3, 3), 3);
	BOOST_CHECK_EQUAL(GCD(1, 5), 1);
	BOOST_CHECK_EQUAL(GCD(3, 1), 1);
}

//������������ ����� �������� � ���� ������������ ������ ����������� ������������
BOOST_AUTO_TEST_CASE(RationalsAreNormalizedAfterCreation)
{
	{
		CRational r(6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(-6, 8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

	{
		CRational r(-6, -8);
		BOOST_CHECK_EQUAL(r.GetNumerator(), 3);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 4);
	}

    {
		CRational r(-1, 3);
		BOOST_CHECK_EQUAL(r.GetNumerator(), -1);
		BOOST_CHECK_EQUAL(r.GetDenominator(), 3);
	}
}

BOOST_AUTO_TEST_CASE(DenominatorMustNotBeZero)
{
	BOOST_CHECK_THROW((CRational(0, 0)), std::invalid_argument);
	BOOST_CHECK_THROW((CRational(1, 0)), std::invalid_argument);
}


BOOST_AUTO_TEST_SUITE_END()
