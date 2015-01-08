#include "Subscriber.h"

#pragma once

typedef std::shared_ptr<CSubscriber> SubscriberPtr;

class CSubscriberCollection
{
public:
    CSubscriberCollection(void);
    ~CSubscriberCollection(void);

    bool Add(const CSubscriber& subscriber);
    bool Delete(unsigned index);
    bool Change(unsigned index, const CSubscriber& subscriber);
    std::vector<SubscriberPtr> GetMatches(const std::string& name, const std::string& address = "",
                                          const std::string& phone = "", const std::string& email = "") const;
    std::vector<SubscriberPtr> GetCollection() const;
    int GetIndex(CSubscriber& subscriber) const;
    unsigned GetSize() const;    
    bool IsChanged() const;
    void SetChanged(bool changed);
    void Clear();

private:    
    std::vector<SubscriberPtr> m_Subscribers;
    bool m_Changed;

    std::vector<SubscriberPtr> GetNameMatches(const std::string& name, const std::vector<SubscriberPtr>& collection) const;
    std::vector<SubscriberPtr> GetPostAddressMatches(const std::string& address, const std::vector<SubscriberPtr>& collection) const;
    std::vector<SubscriberPtr> GetPhoneNumberMatches(const std::string& phone, const std::vector<SubscriberPtr>& collection) const;
    std::vector<SubscriberPtr> GetEmailMatches(const std::string& email, const std::vector<SubscriberPtr>& collection) const;
    bool IsAlreadyExistEmail(const std::string& email, int withoutSubscriberIndex = -1) const;
    bool CheckSubscriberContainExistingEmails(const CSubscriber& subscriber, int withoutSubscriberIndex = -1) const;
};

