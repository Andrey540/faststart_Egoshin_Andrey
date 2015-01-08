#include "SubscriberCollection.h"

#pragma once
class CAddressBook
{
public:
    CAddressBook(void);
    ~CAddressBook(void);
    CSubscriberCollection GetCollection() const;
    bool Save(std::string filePath = "");
    bool Read(std::string filePath = "");
    bool AddSubscriber(const CSubscriber& subscriber);
    bool DeleteSubscriber(unsigned index);
    bool ChangeSubscriber(unsigned index, const CSubscriber& subscriber);
    std::vector<SubscriberPtr> GetMatches(const std::string& name, const std::string& address = "",
                                          const std::string& phone = "", const std::string& email = "") const;
    int GetIndex(CSubscriber& subscriber) const;
    unsigned GetSize() const;    
    bool IsChanged() const;

private:
    CSubscriberCollection m_Collection;
    std::string m_FilePath;
};

