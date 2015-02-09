// lab5-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab5-1\Body.h"
#include "..\lab5-1\Sphere.h"
#include "..\lab5-1\Cone.h"
#include "..\lab5-1\Parallelepiped.h"
#include "..\lab5-1\Cylinder.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct SphereFixture
{
	CSphere sphere;
    SphereFixture()
    {
        sphere = CSphere(1000, 5);
    }
};

BOOST_FIXTURE_TEST_SUITE(Sphere,  SphereFixture)

	BOOST_AUTO_TEST_CASE(HasDensityPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(sphere.GetDensity(), 1000);
	}

    BOOST_AUTO_TEST_CASE(HasRadiusPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(sphere.GetRadius(), 5);
	}

    BOOST_AUTO_TEST_CASE(HasVolume)
	{
        BOOST_CHECK_CLOSE(sphere.GetVolume(), 4 * M_PI * pow(5, 3) / 3, 0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasWeight)
	{
        BOOST_CHECK_CLOSE(sphere.GetWeight(), 4 * M_PI * pow(5, 3) * 1000/ 3, 0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasStringRepresentation)
    {
	    BOOST_CHECK_EQUAL(sphere.ToString(), "Sphere: density 1000 radius 5 volume 523.599 weight 523599");
    }

BOOST_AUTO_TEST_SUITE_END()

struct ConeFixture
{
	CCone cone;
    ConeFixture()
    {
        cone = CCone(1000, 5, 2);
    }
};

BOOST_FIXTURE_TEST_SUITE(Cone, ConeFixture)

	BOOST_AUTO_TEST_CASE(HasDensityPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cone.GetDensity(), 1000);
	}

    BOOST_AUTO_TEST_CASE(HasRadiusPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cone.GetRadius(), 5);
	}

    BOOST_AUTO_TEST_CASE(HasHeightPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cone.GetHeight(), 2);
	}

    BOOST_AUTO_TEST_CASE(HasVolume)
	{
        BOOST_CHECK_CLOSE(cone.GetVolume(), pow(5,2) * M_PI * 2,  0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasWeight)
	{
        BOOST_CHECK_CLOSE(cone.GetWeight(), pow(5,2) * M_PI * 2 * 1000,  0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasStringRepresentation)
    {
	    BOOST_CHECK_EQUAL(cone.ToString(), "Cone: density 1000 radius 5 height 2 volume 157.08 weight 157080");
    }

BOOST_AUTO_TEST_SUITE_END()


struct CylinderFixture
{
	CCylinder cylinder;
    CylinderFixture()
    {
        cylinder = CCylinder(1000, 5, 2);
    }
};

BOOST_FIXTURE_TEST_SUITE(Cylinder, CylinderFixture)

	BOOST_AUTO_TEST_CASE(HasDensityPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cylinder.GetDensity(), 1000);
	}

    BOOST_AUTO_TEST_CASE(HasRadiusPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cylinder.GetRadius(), 5);
	}

    BOOST_AUTO_TEST_CASE(HasHeightPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(cylinder.GetHeight(), 2);
	}

    BOOST_AUTO_TEST_CASE(HasVolume)
	{
        BOOST_CHECK_CLOSE(cylinder.GetVolume(), pow(5,2) * M_PI * 2,  0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasWeight)
	{
        BOOST_CHECK_CLOSE(cylinder.GetWeight(), pow(5,2) * M_PI * 2 * 1000,  0.0001);
	}

    BOOST_AUTO_TEST_CASE(HasStringRepresentation)
    {
	    BOOST_CHECK_EQUAL(cylinder.ToString(), "Cylinder: density 1000 radius 5 height 2 volume 157.08 weight 157080");
    }

BOOST_AUTO_TEST_SUITE_END()


struct ParellelepipedFixture
{
	CParallelepiped parellelepiped;
    ParellelepipedFixture()
    {
        parellelepiped = CParallelepiped(1000, 5, 4, 3);
    }
};

BOOST_FIXTURE_TEST_SUITE(Parellelepiped, ParellelepipedFixture)

	BOOST_AUTO_TEST_CASE(HasDensityPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetDensity(), 1000);
	}

    BOOST_AUTO_TEST_CASE(HasWidthPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetWidth(), 5);
	}

    BOOST_AUTO_TEST_CASE(HasHeightPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetHeight(), 4);
	}

    BOOST_AUTO_TEST_CASE(HasDepthPassedToConstructor)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetDepth(), 3);
	}

    BOOST_AUTO_TEST_CASE(HasVolume)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetVolume(), 60);
	}

    BOOST_AUTO_TEST_CASE(HasWeight)
	{
        BOOST_CHECK_EQUAL(parellelepiped.GetWeight(), 60000);
	}

    BOOST_AUTO_TEST_CASE(HasStringRepresentation)
    {
	    BOOST_CHECK_EQUAL(parellelepiped.ToString(), "Parallelepiped: density 1000 width 5 height 4 depth 3 volume 60 weight 60000");
    }

BOOST_AUTO_TEST_SUITE_END()