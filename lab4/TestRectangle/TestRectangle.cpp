// TestRectangle.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab4-2\Rectangle.h"

struct JustCreatedRectangleWithZeroFieldsFixture
{    
    CRectangle rectangle;
    JustCreatedRectangleWithZeroFieldsFixture()
    {
        rectangle = CRectangle(0, 0, 0, 0);
    }
};

BOOST_FIXTURE_TEST_SUITE(JustCreatedRectangleWithZeroFields,  JustCreatedRectangleWithZeroFieldsFixture)

	BOOST_AUTO_TEST_CASE(HasZeroFields)
	{
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetArea(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetPerimeter(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetLeft)
	{
        rectangle.SetLeft(10);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
    }

    BOOST_AUTO_TEST_CASE(CanSetNegativeLeft)
    {
        rectangle.SetLeft(-10);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), -10);
	}

    BOOST_AUTO_TEST_CASE(CanSetTop)
	{
        rectangle.SetTop(20);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 20);
    }

    BOOST_AUTO_TEST_CASE(CanSetNegativeTop)
    {
        rectangle.SetTop(-20);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), -20);
	}

    BOOST_AUTO_TEST_CASE(CanSetRight)
	{
        rectangle.SetRight(30);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 30);
    }

    BOOST_AUTO_TEST_CASE(CantSetRightIfLeftGreaterThanRight)
    {
        rectangle.SetRight(-30);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetRightIfLeftLessThanRight)
    {
        rectangle.SetLeft(-40);
        rectangle.SetRight(-30);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), -30);
	}

    BOOST_AUTO_TEST_CASE(CanSetBottom)
	{
        rectangle.SetBottom(40);
        BOOST_CHECK_EQUAL(rectangle.GetBottom(), 40);
    }

    BOOST_AUTO_TEST_CASE(CantSetBottomIfLeftGreaterThanTop)
    {
        rectangle.SetBottom(-40);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanSetBottomIfLeftLessThanTop)
    {
        rectangle.SetTop(-50);
        rectangle.SetBottom(-40);
        BOOST_CHECK_EQUAL(rectangle.GetBottom(), -40);
	}

    BOOST_AUTO_TEST_CASE(CanSetWidth)
	{
        rectangle.SetWidth(200);
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 200);
    }

    BOOST_AUTO_TEST_CASE(CantSetNegativeWidth)
	{
        rectangle.SetWidth(-200);
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 0);
    }

    BOOST_AUTO_TEST_CASE(CanSetHeight)
	{
        rectangle.SetHeight(200);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 200);
    }

    BOOST_AUTO_TEST_CASE(CantSetNegativeHeight)
	{
        rectangle.SetHeight(-200);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 0);
    }

    BOOST_AUTO_TEST_CASE(ChangeRightIfSetWidth)
	{
        rectangle.SetWidth(100);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 100);
    }

    BOOST_AUTO_TEST_CASE(ChangeBottomIfSetHeight)
	{
        rectangle.SetHeight(100);
        BOOST_CHECK_EQUAL(rectangle.GetBottom(), 100);
    }

    BOOST_AUTO_TEST_CASE(ChangeWidthIfSetRight)
	{
        rectangle.SetRight(100);
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 100);
    }

    BOOST_AUTO_TEST_CASE(ChangeHeightIfSetBottom)
	{
        rectangle.SetBottom(100);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 100);
    }

BOOST_AUTO_TEST_SUITE_END()

struct CreatedRectangleWithNotZeroFieldsFixture
{    
    CRectangle rectangle;
    CreatedRectangleWithNotZeroFieldsFixture()
    {
        rectangle = CRectangle(10, 50, 100, 200);
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedRectangleWithNotZeroFields,  CreatedRectangleWithNotZeroFieldsFixture)

	BOOST_AUTO_TEST_CASE(HasPerimeter)
	{
        BOOST_CHECK_EQUAL(rectangle.GetPerimeter(), 600);
	}

    BOOST_AUTO_TEST_CASE(HasArea)
	{
        BOOST_CHECK_EQUAL(rectangle.GetArea(), 20000);
	}

    BOOST_AUTO_TEST_CASE(ChangeCoordinatsAndNotChangeSizeIfMove)
	{
        rectangle.Move(20, 30);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 30);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 80);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 130);
        BOOST_CHECK_EQUAL(rectangle.GetBottom(), 280);
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 100);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 200);
	}

    BOOST_AUTO_TEST_CASE(ChangeSizeAndNotChangeLeftAndTopIfScale)
	{
        rectangle.Scale(2, 3);       
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 200);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 600);
        BOOST_CHECK_EQUAL(rectangle.GetRight(), 210);
        BOOST_CHECK_EQUAL(rectangle.GetBottom(), 650);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);
	}

    BOOST_AUTO_TEST_CASE(DontScaleIfNegative)
	{
        rectangle.Scale(-2, 3);       
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 100);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 200);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);

        rectangle.Scale(2, -3);       
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 100);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 200);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);

        rectangle.Scale(-2, -3);       
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 100);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 200);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);
	}

    BOOST_AUTO_TEST_CASE(ChangeRectangleIfIntresectWithOtherRactangle)
	{
        CRectangle other1(15, 60, 100, 100);
               
        BOOST_CHECK(rectangle.Intersect(other1));
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 95);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 100);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 15);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 60);


        rectangle.SetLeft(10);
        rectangle.SetTop(50);
        rectangle.SetWidth(100);
        rectangle.SetHeight(200);

        CRectangle other2(0, 0, 100, 100);
               
        BOOST_CHECK(rectangle.Intersect(other2));
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 90);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 50);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);

        rectangle.SetLeft(15);
        rectangle.SetTop(60);
        rectangle.SetWidth(100);
        rectangle.SetHeight(100);

        CRectangle other3(10, 50, 100, 200);
               
        BOOST_CHECK(rectangle.Intersect(other3));
	}

    BOOST_AUTO_TEST_CASE(SetHeightAndWidthZeroIfNotIntresectWithOtherRactangle)
	{
        CRectangle other1(0, 00, 10, 40);
               
        BOOST_CHECK(!rectangle.Intersect(other1));
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);

        rectangle.SetWidth(100);
        rectangle.SetHeight(200);

        CRectangle other2(120, 360, 100, 100);
               
        BOOST_CHECK(!rectangle.Intersect(other2));
        BOOST_CHECK_EQUAL(rectangle.GetWidth(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetHeight(), 0);
        BOOST_CHECK_EQUAL(rectangle.GetLeft(), 10);
        BOOST_CHECK_EQUAL(rectangle.GetTop(), 50);
	}

BOOST_AUTO_TEST_SUITE_END()
