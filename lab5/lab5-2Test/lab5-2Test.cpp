// lab5-2Test.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "..\lab5-2\Person.h"
#include "..\lab5-2\University.h"
#include "..\lab5-2\Student.h"
#include "..\lab5-2\UniversityCollectionManager.h"

bool CheckEqualWstrings(const std::wstring& s1, const std::wstring& s2)
{
    return s1 == s2;
}

struct PersonFixture
{
	CPerson person;
    PersonFixture()
    {
        person = CPerson(true, 34, 190.9, 70.9, L"�������");
    }
};

BOOST_FIXTURE_TEST_SUITE(Person,  PersonFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(person.IsMan(), true);
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"�������"), true);
        BOOST_CHECK_EQUAL(person.GetAge(), 34);
        BOOST_CHECK_EQUAL(person.GetGrowth(), 190.9);
        BOOST_CHECK_EQUAL(person.GetWeight(), 70.9);
	}

	BOOST_AUTO_TEST_CASE(CantSetAgeLessThanExist)
	{
        BOOST_CHECK_THROW(person.SetAge(23), std::domain_error);
        BOOST_CHECK_EQUAL(person.GetAge(), 34);
	}

	BOOST_AUTO_TEST_CASE(CantSetGrowthLessThanExist)
	{
        BOOST_CHECK_THROW(person.SetGrowth(185), std::domain_error);
        BOOST_CHECK_EQUAL(person.GetGrowth(), 190.9);
	}

    BOOST_AUTO_TEST_CASE(CantSetEmptyName)
	{
        BOOST_CHECK_THROW(person.SetName(L""), std::domain_error);
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"�������"), true);
	}

    BOOST_AUTO_TEST_CASE(CanSetGrowth)
	{
        BOOST_CHECK_NO_THROW(person.SetGrowth(200.0));
        BOOST_CHECK_EQUAL(person.GetGrowth(), 200.0);
	}

    BOOST_AUTO_TEST_CASE(CanSetAge)
	{
        BOOST_CHECK_NO_THROW(person.SetAge(36));
        BOOST_CHECK_EQUAL(person.GetAge(), 36);
	}

    BOOST_AUTO_TEST_CASE(CanSetName)
	{
        BOOST_CHECK_NO_THROW(person.SetName(L"������"));
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"������"), true);
	}

    BOOST_AUTO_TEST_CASE(CantConstructPersonWithNotValidParameters)
	{
        BOOST_CHECK_THROW(CPerson(true, 34, 0, 0, L"�������"), std::domain_error);
	}

    BOOST_AUTO_TEST_CASE(CantSetSezoWeight)
	{
        BOOST_CHECK_THROW(person.SetWeight(0), std::domain_error);
        BOOST_CHECK_EQUAL(person.GetWeight(), 70.9);
	}

BOOST_AUTO_TEST_SUITE_END()

struct UniversityFixture
{
	CUniversity university;
    UniversityFixture()
    {
        university = CUniversity(L"���");
    }
};

BOOST_FIXTURE_TEST_SUITE(University, UniversityFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university.GetName(), L"���"), true);
	}

    BOOST_AUTO_TEST_CASE(CantSetEmptyName)
	{
        BOOST_CHECK_THROW(university.SetName(L""), std::domain_error);
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university.GetName(), L"���"), true);
	}

    BOOST_AUTO_TEST_CASE(CanSetName)
	{
        BOOST_CHECK_NO_THROW(university.SetName(L"�������"));
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university.GetName(), L"�������"), true);
	}

    BOOST_AUTO_TEST_CASE(CanAddStudent)
	{
        CStudent student = CStudent(true, 20, 190.9, 70.9, L"�������", 2, university);
        BOOST_CHECK_EQUAL(university.GetStudents().size(), 0);
        BOOST_CHECK_NO_THROW(university.AddStudent(student));
        BOOST_CHECK_EQUAL(university.GetStudents().size(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()


struct UniversityWithStudentsFixture
{
	CUniversity university;
    UniversityWithStudentsFixture()
    {
        university = CUniversity(L"���");
        CStudent student1 = CStudent(true, 20, 190.9, 70.9, L"�������", 2, university);
        CStudent student2 = CStudent(true, 23, 190.9, 71.9, L"����", 2, university);
        university.AddStudent(student1);
        university.AddStudent(student2);
        university.ResetModified();
    }
};

BOOST_FIXTURE_TEST_SUITE(UniversityWithStudents, UniversityWithStudentsFixture)

    BOOST_AUTO_TEST_CASE(Has2StudentsAndNotModified)
	{
        BOOST_CHECK_EQUAL(university.GetStudents().size(), 2);
        BOOST_CHECK(!university.IsModified());
	}

    BOOST_AUTO_TEST_CASE(CanDeleteFirstStudentAndBecomeChanged)
	{
        BOOST_CHECK_NO_THROW(university.DeleteStudent(1));
        BOOST_CHECK_EQUAL(university.GetStudents().size(), 1);
        BOOST_CHECK(university.IsModified());
	}

    BOOST_AUTO_TEST_CASE(CanChangeStudentAndBecomeChanged)
	{
        CStudent newStudent = CStudent(true, 20, 190.9, 70.9, L"������", 2, university);   
        BOOST_CHECK_NO_THROW(university.ChangeStudent(1, newStudent));
        const std::vector<std::shared_ptr<CStudent>> students = university.GetStudents();
        BOOST_CHECK(newStudent == *(students[0]));
        BOOST_CHECK(university.IsModified());
	}

BOOST_AUTO_TEST_SUITE_END()

struct StudentFixture
{
	CStudent student;
    CUniversity university;
    StudentFixture()
    {
        university = CUniversity(L"���");
        student = CStudent(true, 20, 190.9, 70.9, L"�������", 2, university);
    }
};

BOOST_FIXTURE_TEST_SUITE(Student, StudentFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(student.GetCourse(), 2);
        BOOST_CHECK(student.GetUniversity() == university);
	}

    BOOST_AUTO_TEST_CASE(CantSetCourseLessThanExist)
	{
        BOOST_CHECK_THROW(student.SetCourse(1), std::domain_error);
        BOOST_CHECK_EQUAL(student.GetCourse(), 2);
	}

    BOOST_AUTO_TEST_CASE(CanSetGreaterCourse)
	{
        BOOST_CHECK_NO_THROW(student.SetCourse(3));
        BOOST_CHECK_EQUAL(student.GetCourse(), 3);
	}

    BOOST_AUTO_TEST_CASE(CanSetUniversity)
	{
        CUniversity university = CUniversity(L"�������");
        BOOST_CHECK_NO_THROW(student.SetUniversity(university));
        BOOST_CHECK(student.GetUniversity() == university);
	}

BOOST_AUTO_TEST_SUITE_END()

struct EmptyUniversityCollectionManagerFixture
{
	CUniversityCollectionManager manager;
};

BOOST_FIXTURE_TEST_SUITE(EmptyUniversityCollectionManager, EmptyUniversityCollectionManagerFixture)

    BOOST_AUTO_TEST_CASE(CanAddUniversity)
	{
        CUniversity university = CUniversity(L"���");
        BOOST_CHECK_NO_THROW(manager.AddUniversity(university));
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()

struct UniversityCollectionManagerFixture
{
	CUniversityCollectionManager manager;

    UniversityCollectionManagerFixture()
    {
        CUniversity university1 = CUniversity(L"���");
        manager.AddUniversity(university1);       
        CUniversity university2 = CUniversity(L"�������");
        manager.AddUniversity(university2);
    }
};

BOOST_FIXTURE_TEST_SUITE(UniversityCollectionManager, UniversityCollectionManagerFixture)

    BOOST_AUTO_TEST_CASE(HaveTwoUniversities)
	{
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 2);        
	}

    BOOST_AUTO_TEST_CASE(CantAddAlreadyExistUniversity)
	{
        CUniversity university = CUniversity(L"���");
        BOOST_CHECK_THROW(manager.AddUniversity(university), std::domain_error);
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 2);
	}

    BOOST_AUTO_TEST_CASE(CanDeleteExistUniversity)
	{
        BOOST_CHECK_NO_THROW(manager.DeleteUniversity(1));
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 1);
	}

    BOOST_AUTO_TEST_CASE(CantDeleteNotExistUniversity)
	{
        BOOST_CHECK_THROW(manager.DeleteUniversity(3), std::domain_error);
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 2);
	}

    BOOST_AUTO_TEST_CASE(CanSetNotExistUniversityName)
	{
        BOOST_CHECK_NO_THROW(manager.SetUniversityName(1, L"����"));
        const std::vector<std::shared_ptr<CUniversity>> vectorUniversities = manager.GetUniversities();
        BOOST_CHECK_EQUAL(CheckEqualWstrings(vectorUniversities[0]->GetName(), L"����"), true);
	}

    BOOST_AUTO_TEST_CASE(CanChangeUniversity)
	{
        CUniversity university = CUniversity(L"����");
        BOOST_CHECK_NO_THROW(manager.ChangeUniversity(1, university));
        const std::vector<std::shared_ptr<CUniversity>> vectorUniversities = manager.GetUniversities();
        BOOST_CHECK(*(vectorUniversities[0]) == university);
	}

    BOOST_AUTO_TEST_CASE(CantSetAlreadyExistUniversityName)
	{
        BOOST_CHECK_THROW(manager.SetUniversityName(1, L"�������"), std::domain_error);
        const std::vector<std::shared_ptr<CUniversity>> universities = manager.GetUniversities();
        BOOST_CHECK_EQUAL(CheckEqualWstrings(universities[0]->GetName(), L"���"), true);
	}

BOOST_AUTO_TEST_SUITE_END()
