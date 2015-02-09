#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "University.h"

class CUniversityCollectionManager
{
public:
    CUniversityCollectionManager(void);
    ~CUniversityCollectionManager(void);
    void AddUniversity(const std::shared_ptr<CUniversity>& university);
    void DeleteUniversity(unsigned index);
    void SetUniversityName(unsigned index, const std::wstring& name);
    void ChangeUniversity(unsigned index, const std::shared_ptr<CUniversity>& newUniversity);
    const std::vector<std::shared_ptr<CUniversity>> GetUniversities() const;    
    void InitializeFromFiles(const std::vector<std::string>& filePaths);
    void SaveChanges() const;

private:
    std::vector<std::shared_ptr<CUniversity>> m_universities;
    bool m_isModified;
    std::map<std::shared_ptr<CUniversity>, std::string> m_relationships;
    std::locale m_locale;

    bool IsNameUnique(const std::wstring& name) const;
    bool IsChanged() const;
    std::shared_ptr<CUniversity> ReadUniversityFromFile(const std::string& filePath) const;
    void SaveUniversityToFile(const std::string& filePath, const std::shared_ptr<CUniversity>& university) const;
};

