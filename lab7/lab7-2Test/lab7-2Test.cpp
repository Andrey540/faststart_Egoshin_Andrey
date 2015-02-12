// lab7-2Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab7-2\Student.h"

bool CheckStudent(const CStudent& student, const std::string& name, const std::string& surname, const std::string& patronymic, unsigned age)
{
    return student.GetName() == name &&
           student.GetSurname() == surname &&
           student.GetPatronymic() == patronymic &&
           student.GetAge() == age;
}

struct EmptyStudentFixture
{
	CStudent student;
};

BOOST_FIXTURE_TEST_SUITE(EmptyStudent,  EmptyStudentFixture)

    BOOST_AUTO_TEST_CASE(HaveEmptyParameters)
	{
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CanSetNotEmptyName)
	{
        BOOST_CHECK_NO_THROW(student.Rename("Jack", "Nikolson", "David"));
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "David", 0));
	}

    BOOST_AUTO_TEST_CASE(CanSetNotEmptyNameWithEmptyPatronymic)
	{
        BOOST_CHECK_NO_THROW(student.Rename("Jack", "Nikolson", ""));
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CantSetNotEmptyNameWithPatronymicConsistOfWhiteSpaces)
	{
        BOOST_CHECK_THROW(student.Rename("Jack", "Nikolson", "   "), std::invalid_argument);
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CantSetNotEmptyNameAndEmptySurname)
	{
        BOOST_CHECK_THROW(student.Rename("Jack", "", ""), std::invalid_argument);
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CantSetNotEmptyNameAndSurnameConsistOfWhiteSpaces)
	{
        BOOST_CHECK_THROW(student.Rename("Jack", "  ", ""), std::invalid_argument);
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CantSetEmptyNameAndNotEmptySurname)
	{
        BOOST_CHECK_THROW(student.Rename("", "Nikolson", ""), std::invalid_argument);
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

    BOOST_AUTO_TEST_CASE(CantSetNameConsistOfWhiteSpacesAndNotEmptySurname)
	{
        BOOST_CHECK_THROW(student.Rename("   ", "Nikolson", ""), std::invalid_argument);
        BOOST_CHECK(CheckStudent(student, "", "", "", 0));
	}

BOOST_AUTO_TEST_SUITE_END()

struct StudentFixture
{
	CStudent student;
    StudentFixture()
    {
        student = CStudent("Jack", "Nikolson", "David", 19);
    }
};

BOOST_FIXTURE_TEST_SUITE(Student, StudentFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "David", 19));
	}

    BOOST_AUTO_TEST_CASE(CanSetAgeGreaterThenExist)
	{
        BOOST_CHECK_NO_THROW(student.SetAge(60));
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "David", 60));
	}

    BOOST_AUTO_TEST_CASE(CanSetAgeGreaterThenUpperBounce)
	{
        BOOST_CHECK_THROW(student.SetAge(61), std::out_of_range);
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "David", 19));
	}

    BOOST_AUTO_TEST_CASE(CantSetAgeLessThenExist)
	{
        BOOST_CHECK_THROW(student.SetAge(18), std::domain_error);
        BOOST_CHECK(CheckStudent(student, "Jack", "Nikolson", "David", 19));
	}

    BOOST_AUTO_TEST_CASE(CantConstructStudentWithAgeLessThanLowerBounce)
	{
        BOOST_CHECK_THROW(CStudent("Jack", "Nikolson", "David", 13), std::out_of_range);
	}

    BOOST_AUTO_TEST_CASE(CanConstructStudentWithMinimumAge)
	{
        BOOST_CHECK_NO_THROW(CStudent("Jack", "Nikolson", "David", 14));
	}

BOOST_AUTO_TEST_SUITE_END()