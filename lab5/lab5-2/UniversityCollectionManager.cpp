#include "stdafx.h"
#include "UniversityCollectionManager.h"
#include "Student.h"
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

CUniversityCollectionManager::CUniversityCollectionManager(void)
    : m_isModified(false),
      m_locale("ru")
{}


CUniversityCollectionManager::~CUniversityCollectionManager(void)
{}

void CUniversityCollectionManager::AddUniversity(const CUniversity& university)
{    
    if (!IsNameUnique(university.GetName()))
    {
        wstring name = university.GetName();
        throw domain_error("University with name " + string(name.begin(), name.end()) + " already exist");
    }
    wstring name = university.GetName();
    m_universities.push_back(make_shared<CUniversity>(university));
    m_relationships[make_shared<CUniversity>(university)] = string(name.begin(), name.end()) + ".txt";
    m_isModified = true;
}

void CUniversityCollectionManager::DeleteUniversity(unsigned index)
{
    if (index > m_universities.size() || index == 0)
    {
        throw domain_error("Incorrect university index");
    }
    m_relationships.erase(m_universities[index - 1]);
    m_universities.erase(m_universities.begin() + index - 1);    
    m_isModified = true;
}

void CUniversityCollectionManager::ChangeUniversity(unsigned index, const CUniversity& newUniversity)
{
    if (index > m_universities.size() || index == 0)
    {
        throw domain_error("Incorrect university index");
    }

    if (m_universities[index - 1]->GetName() == newUniversity.GetName() ||
        IsNameUnique(newUniversity.GetName()))
    {
        m_universities[index - 1] = make_shared<CUniversity>(newUniversity);
    }
    m_isModified = true;
}

void CUniversityCollectionManager::SetUniversityName(unsigned index, const wstring& name)
{    
    if (index > m_universities.size() || index == 0)
    {
        throw domain_error("Incorrect university index");
    }
    if (!IsNameUnique(name))
    {
        throw domain_error("University with name " + string(name.begin(), name.end()) + " already exist");
    }
    m_universities[index - 1]->SetName(name);
    m_isModified = true;
}

const std::vector<std::shared_ptr<CUniversity>> CUniversityCollectionManager::GetUniversities() const
{
    return m_universities;
}

void CUniversityCollectionManager::InitializeFromFiles(const std::vector<std::string>& filePaths)
{
    m_universities.clear();
    m_relationships.clear();
    for (auto filePath : filePaths)
    {
        shared_ptr<CUniversity> university = ReadUniversityFromFile(filePath);
        m_universities.push_back(university);
        m_relationships[university] = filePath;
    }
}

void CUniversityCollectionManager::SaveChanges() const
{
   if (!IsChanged())
   {
       return;
   }

   for (auto relationship : m_relationships)
   {
       SaveUniversityToFile(relationship.second, relationship.first);
   }
}

shared_ptr<CUniversity> CUniversityCollectionManager::ReadUniversityFromFile(const std::string& filePath) const
{
    wifstream file(filePath);
    if (!file.is_open())
    {
        throw runtime_error("Can not open file " + filePath);        
    }

    file.imbue(m_locale);
    wstring str;
    getline(file, str);
    CUniversity university(str);

    getline(file, str);
    while(!file.eof() && !str.empty())
    {                
        bool isMan;
        unsigned age;
        double weight;
        double growth;
        unsigned course;        
        file >> isMan >> age >> growth >> weight >> course;
        CStudent student(isMan, age, growth, weight, str, course, university);
        university.AddStudent(student);
        getline(file, str);
    }
    university.ResetModified();

    return make_shared<CUniversity>(university);
}

void CUniversityCollectionManager::SaveUniversityToFile(const std::string& filePath, const shared_ptr<CUniversity>& university) const
{
    wofstream file("university.txt");
    if (!file.is_open())
    {
        throw runtime_error("Can not open file " + filePath);        
    }
    file.imbue(m_locale);
    file << university->GetName() << endl;
    for (auto student : university->GetStudents())
    {
        file << student->GetName() << endl;
        file << student->IsMan() << " " << student->GetAge() << " " << student->GetGrowth() <<
             " " << student->GetWeight() << " " << student->GetCourse() << endl;
    }

    file.close();
}

bool CUniversityCollectionManager::IsNameUnique(const wstring& name) const
{
    auto i = find_if(m_universities.begin(), m_universities.end(),
        [name](shared_ptr<CUniversity> university)
        {
            return university->GetName() == name;            
        });
    return i == m_universities.end();
}

bool CUniversityCollectionManager::IsChanged() const
{
    if (m_isModified)
    {
        return true;
    }
    auto i = find_if(m_universities.begin(), m_universities.end(),
    [](shared_ptr<CUniversity> university)
    {
        return university->IsModified();            
    });
    return i != m_universities.end();
}
