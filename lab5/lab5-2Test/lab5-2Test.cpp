// lab5-2Test.cpp: определяет точку входа для консольного приложения.
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
        person = CPerson(true, 34, 190.9, 70.9, L"Николай");
    }
};

BOOST_FIXTURE_TEST_SUITE(Person,  PersonFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(person.IsMan(), true);
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"Николай"), true);
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
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"Николай"), true);
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
        BOOST_CHECK_NO_THROW(person.SetName(L"Виктор"));
        BOOST_CHECK_EQUAL(CheckEqualWstrings(person.GetName(), L"Виктор"), true);
	}

    BOOST_AUTO_TEST_CASE(CantConstructPersonWithNotValidParameters)
	{
        BOOST_CHECK_THROW(CPerson(true, 34, 0, 0, L"Николай"), std::domain_error);
	}

    BOOST_AUTO_TEST_CASE(CantSetSezoWeight)
	{
        BOOST_CHECK_THROW(person.SetWeight(0), std::domain_error);
        BOOST_CHECK_EQUAL(person.GetWeight(), 70.9);
	}

BOOST_AUTO_TEST_SUITE_END()

struct UniversityFixture
{
	std::shared_ptr<CUniversity> university;
    UniversityFixture()
    {
        university = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
    }
};

BOOST_FIXTURE_TEST_SUITE(University, UniversityFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university->GetName(), L"МГУ"), true);
	}

    BOOST_AUTO_TEST_CASE(CantSetEmptyName)
	{
        BOOST_CHECK_THROW(university->SetName(L""), std::domain_error);
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university->GetName(), L"МГУ"), true);
	}

    BOOST_AUTO_TEST_CASE(CanSetName)
	{
        BOOST_CHECK_NO_THROW(university->SetName(L"Баумана"));
        BOOST_CHECK_EQUAL(CheckEqualWstrings(university->GetName(), L"Баумана"), true);
	}

    BOOST_AUTO_TEST_CASE(CanAddStudent)
	{
        std::shared_ptr<CStudent> student = std::make_shared<CStudent>(CStudent(true, 20, 190.9, 70.9, L"Николай", 2, university));
        BOOST_CHECK_EQUAL(university->GetStudents().size(), 0);
        BOOST_CHECK_NO_THROW(university->AddStudent(student));
        BOOST_CHECK_EQUAL(university->GetStudents().size(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()


struct UniversityWithStudentsFixture
{
	std::shared_ptr<CUniversity> university;
    UniversityWithStudentsFixture()
    {
        university = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
        std::shared_ptr<CStudent> student1 = std::make_shared<CStudent>(CStudent(true, 20, 190.9, 70.9, L"Николай", 2, university));
        std::shared_ptr<CStudent> student2 = std::make_shared<CStudent>(CStudent(true, 23, 190.9, 71.9, L"Витя", 2, university));
        university->AddStudent(student1);
        university->AddStudent(student2);
        university->ResetModified();
    }
};

BOOST_FIXTURE_TEST_SUITE(UniversityWithStudents, UniversityWithStudentsFixture)

    BOOST_AUTO_TEST_CASE(Has2StudentsAndNotModified)
	{
        BOOST_CHECK_EQUAL(university->GetStudents().size(), 2);
        BOOST_CHECK(!university->IsModified());
	}

    BOOST_AUTO_TEST_CASE(CanDeleteFirstStudentAndBecomeChanged)
	{
        BOOST_CHECK_NO_THROW(university->DeleteStudent(1));
        BOOST_CHECK_EQUAL(university->GetStudents().size(), 1);
        BOOST_CHECK(university->IsModified());
	}

    BOOST_AUTO_TEST_CASE(CanChangeStudentAndBecomeChanged)
	{
        auto newStudent = std::make_shared<CStudent>(CStudent(true, 20, 190.9, 70.9, L"Сергей", 2, university));   
        BOOST_CHECK_NO_THROW(university->ChangeStudent(1, newStudent));
        const std::vector<std::shared_ptr<CStudent>> students = university->GetStudents();
        BOOST_CHECK(newStudent == students[0]);
        BOOST_CHECK(university->IsModified());
	}

BOOST_AUTO_TEST_SUITE_END()

struct StudentFixture
{
	CStudent student;
    std::shared_ptr<CUniversity> university;
    StudentFixture()
    {
        university = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
        student = CStudent(true, 20, 190.9, 70.9, L"Николай", 2, university);
    }
};

BOOST_FIXTURE_TEST_SUITE(Student, StudentFixture)

    BOOST_AUTO_TEST_CASE(HaveParametersTurnedToConstructor)
	{
        BOOST_CHECK_EQUAL(student.GetCourse(), 2);
        BOOST_CHECK(student.GetUniversity() == *university);
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
        auto university1 = std::make_shared<CUniversity>(CUniversity(L"Баумана"));
        BOOST_CHECK_NO_THROW(student.SetUniversity(university1));
        BOOST_CHECK(student.GetUniversity() == *university1);
	}

    BOOST_AUTO_TEST_CASE(NotEqualWithOtherPerson)
	{
        CPerson person(true, 16, 1.7, 70.9, L"Ivanov Ivan");
        CStudent student(true, 16, 1.7, 70.9, L"Ivanov Ivan", 3, university);
        CPerson & studentAsPerson = student;
        BOOST_CHECK(person != studentAsPerson); 
        BOOST_CHECK(studentAsPerson != person);
	}

    BOOST_AUTO_TEST_CASE(NotEqualStudentCastedTpPersonWithOtherPerson)
	{
        CPerson person(true, 16, 1.7, 70.9, L"Ivanov Ivan");
        CStudent student(true, 16, 1.7, 70.9, L"Ivanov Ivan", 3, university);
        BOOST_CHECK(person != student); 
        BOOST_CHECK(student != person);
	}

    BOOST_AUTO_TEST_CASE(NotEqualWithOtherStudent)
	{
        auto otherUniversity = std::make_shared<CUniversity>(CUniversity(L"Баумана"));
        CStudent student1(true, 16, 1.7, 70.9, L"Ivanov Ivan", 4, otherUniversity);
        CStudent student2(true, 16, 1.7, 70.9, L"Ivanov Ivan", 3, university);
        CPerson &  student1AsPerson = student1;
        CPerson &  student2AsPerson = student2;
        BOOST_CHECK(student1AsPerson != student2AsPerson); 
        BOOST_CHECK(student1 != student2);
	}

BOOST_AUTO_TEST_SUITE_END()

struct EmptyUniversityCollectionManagerFixture
{
	CUniversityCollectionManager manager;
};

BOOST_FIXTURE_TEST_SUITE(EmptyUniversityCollectionManager, EmptyUniversityCollectionManagerFixture)

    BOOST_AUTO_TEST_CASE(CanAddUniversity)
	{
        std::shared_ptr<CUniversity> university = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
        BOOST_CHECK_NO_THROW(manager.AddUniversity(university));
        BOOST_CHECK_EQUAL(manager.GetUniversities().size(), 1);
	}

BOOST_AUTO_TEST_SUITE_END()

struct UniversityCollectionManagerFixture
{
	CUniversityCollectionManager manager;

    UniversityCollectionManagerFixture()
    {
        std::shared_ptr<CUniversity> university1 = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
        manager.AddUniversity(university1);       
        std::shared_ptr<CUniversity> university2 = std::make_shared<CUniversity>(CUniversity(L"Баумана"));
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
        std::shared_ptr<CUniversity> university = std::make_shared<CUniversity>(CUniversity(L"МГУ"));
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
        BOOST_CHECK_NO_THROW(manager.SetUniversityName(1, L"МОСИ"));
        const std::vector<std::shared_ptr<CUniversity>> vectorUniversities = manager.GetUniversities();
        BOOST_CHECK_EQUAL(CheckEqualWstrings(vectorUniversities[0]->GetName(), L"МОСИ"), true);
	}

    BOOST_AUTO_TEST_CASE(CanChangeUniversity)
	{
        auto university = std::make_shared<CUniversity>(CUniversity(L"ПГТУ"));
        BOOST_CHECK_NO_THROW(manager.ChangeUniversity(1, university));
        const std::vector<std::shared_ptr<CUniversity>> vectorUniversities = manager.GetUniversities();
        BOOST_CHECK(vectorUniversities[0] == university);
	}

    BOOST_AUTO_TEST_CASE(CantSetAlreadyExistUniversityName)
	{
        BOOST_CHECK_THROW(manager.SetUniversityName(1, L"Баумана"), std::domain_error);
        const std::vector<std::shared_ptr<CUniversity>> universities = manager.GetUniversities();
        BOOST_CHECK_EQUAL(CheckEqualWstrings(universities[0]->GetName(), L"МГУ"), true);
	}

BOOST_AUTO_TEST_SUITE_END()
