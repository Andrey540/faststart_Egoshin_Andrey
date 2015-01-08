#include "stdafx.h"
#include "SubscriberCollection.h"
#include <memory>

using namespace std;

CSubscriberCollection::CSubscriberCollection(void) : m_Changed(false)
{}

CSubscriberCollection::~CSubscriberCollection(void)
{}

bool CSubscriberCollection::Add(const CSubscriber& subscriber)
{
    string name = subscriber.GetName().GetValue();
    if (!CheckSubscriberContainExistingEmails(subscriber) || name.length() == 0)
    {
        return false;
    }
    m_Subscribers.push_back(make_shared<CSubscriber>(subscriber));
    m_Changed = true;
    return true;
}

bool CSubscriberCollection::Change(unsigned index, const CSubscriber& subscriber)
{
    string name = subscriber.GetName().GetValue();
    if (!CheckSubscriberContainExistingEmails(subscriber, index) || name.length() == 0 ||
        index >= m_Subscribers.size())
    {
        return false;
    }
    m_Subscribers[index] = make_shared<CSubscriber>(subscriber);
    m_Changed = true;
    return true;
}

bool CSubscriberCollection::Delete(unsigned index)
{
    if (index >= m_Subscribers.size())
    {
        return false;
    }
    m_Subscribers.erase(m_Subscribers.begin() + index);
    m_Changed = true;
    return true;
}

bool CSubscriberCollection::IsAlreadyExistEmail(const std::string& email, int withoutSubscriberIndex) const
{
    int count = 0;
    for(SubscriberPtr subscriberPtr : m_Subscribers)
    {
        CSubscriber subscriber = *subscriberPtr;
        if (subscriber.IsContainEmail(email) && count != withoutSubscriberIndex)
        {
            return true;
        }
        ++count;
    }
    return false;
}

vector<SubscriberPtr> CSubscriberCollection::GetMatches(const string& name, const string& address,
                                                        const string& phone, const string& email) const
{
    vector<SubscriberPtr> result = GetCollection();

    if (name != "")
    {
        result = GetNameMatches(name, result);
    }
    if (address != "")
    {
        result = GetPostAddressMatches(address, result);
    }
    if (phone != "")
    {
        result = GetPhoneNumberMatches(phone, result);
    }
    if (email != "")
    {
        result = GetEmailMatches(email, result);
    }
    return result;
}

vector<SubscriberPtr> CSubscriberCollection::GetCollection() const
{
    vector<SubscriberPtr> result;
    for(auto itemPtr : m_Subscribers)
    {
        CSubscriber item = *itemPtr;
        result.push_back(make_shared<CSubscriber>(item));
    }
    return result;
}

bool CSubscriberCollection::IsChanged() const
{
    return m_Changed;
}

void CSubscriberCollection::SetChanged(bool changed)
{
    m_Changed = changed;
}

void CSubscriberCollection::Clear()
{
    m_Subscribers.clear();
}

int CSubscriberCollection::GetIndex(CSubscriber& subscriber) const
{
    int count = 0;
    for(auto itemPtr : m_Subscribers)
    {
        CSubscriber item = *itemPtr;
        if (subscriber == item)
        {
            return count;
        }
        ++count;
    }

    return -1;
}

unsigned CSubscriberCollection::GetSize() const
{
    return m_Subscribers.size();
}

bool CSubscriberCollection::CheckSubscriberContainExistingEmails(const CSubscriber& subscriber, int withoutSubscriberIndex) const
{
    auto emails = subscriber.GetEmails();

    for(auto emailPtr : emails)
    {
        CEmail email = *emailPtr;
        if (IsAlreadyExistEmail(email.GetValue(), withoutSubscriberIndex))
        {
            return false;
        }
    }
    return true;
}

vector<SubscriberPtr> CSubscriberCollection::GetNameMatches(const string& name, const vector<SubscriberPtr>& collection) const
{
    vector<SubscriberPtr> result;
    for(SubscriberPtr elementPtr : collection)
    {
        CSubscriber element = *elementPtr;
        CName currentName = element.GetName();
        if (currentName.IsMatches(name))
        {
            result.push_back(make_shared<CSubscriber>(element));
        }
    }
    return result;
}

vector<SubscriberPtr> CSubscriberCollection::GetPostAddressMatches(const string& address, const vector<SubscriberPtr>& collection) const
{
    vector<SubscriberPtr> result;
    for(SubscriberPtr elementPtr : collection)
    {
        CSubscriber element = *elementPtr;
        CPostAddress currentAddress = element.GetPostAddress();
        if (currentAddress.IsMatches(address))
        {
            result.push_back(make_shared<CSubscriber>(element));
        }
    }
    return result;
}

vector<SubscriberPtr> CSubscriberCollection::GetPhoneNumberMatches(const string& phone, const vector<SubscriberPtr>& collection) const
{
    vector<SubscriberPtr> result;
    for(SubscriberPtr elementPtr : collection)
    {
        CSubscriber element = *elementPtr;
        CStringFieldCollection<CPhoneNumber> phones = element.GetPhoneNumberCollection();
        if (phones.IsMatches(phone))
        {
            result.push_back(make_shared<CSubscriber>(element));
        }
    }
    return result;
}

vector<SubscriberPtr> CSubscriberCollection::GetEmailMatches(const string& email, const vector<SubscriberPtr>& collection) const
{
    vector<SubscriberPtr> result;
    for(SubscriberPtr elementPtr : collection)
    {
        CSubscriber element = *elementPtr;
        CStringFieldCollection<CEmail> emails = element.GetEmailCollection();
        if (emails.IsMatches(email))
        {
            result.push_back(make_shared<CSubscriber>(element));
        }
    }
    return result;
}