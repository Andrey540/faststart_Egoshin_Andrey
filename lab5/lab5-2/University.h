#pragma once

#include <string>
#include <vector>
#include <memory>

class CStudent;

class CUniversity
{
public:
    CUniversity(const std::wstring& name);
    ~CUniversity(void);
    void SetName(const std::wstring& name);
    std::wstring GetName() const;
    void AddStudent(const std::shared_ptr<CStudent>& student);
    void DeleteStudent(unsigned index);
    void ChangeStudent(unsigned index, const std::shared_ptr<CStudent>& student);
    void ResetModified();
    bool IsModified();
    const std::vector<std::shared_ptr<CStudent>>& GetStudents() const;

private:
    std::wstring m_name;
    bool m_isModified;
    std::vector<std::shared_ptr<CStudent>> m_students;    
    
    void CheckValidName(const std::wstring& value) const;
};
