#include "stdafx.h"
#include "AddressBook.h"
#include <string>
#include <fstream>

using namespace std;

CAddressBook::CAddressBook(void)
{}

CAddressBook::~CAddressBook(void)
{}

CSubscriberCollection CAddressBook::GetCollection() const
{
    return m_Collection;
}

bool CAddressBook::AddSubscriber(const CSubscriber& subscriber)
{
    return m_Collection.Add(subscriber);
}

bool CAddressBook::DeleteSubscriber(unsigned index)
{
    return m_Collection.Delete(index);
}

bool CAddressBook::ChangeSubscriber(unsigned index, const CSubscriber& subscriber)
{
    return m_Collection.Change(index, subscriber);
}

vector<SubscriberPtr> CAddressBook::GetMatches(const string& name, const string& address,
                                               const string& phone, const string& email) const
{
    return m_Collection.GetMatches(name, address, phone, email);
}

int CAddressBook::GetIndex(CSubscriber& subscriber) const
{
    return m_Collection.GetIndex(subscriber);
}

unsigned CAddressBook::GetSize() const
{
    return m_Collection.GetSize();
}

bool CAddressBook::IsChanged() const
{
    return m_Collection.IsChanged();
}

bool CAddressBook::Save(string filePath)
{
    if (filePath != "")
    {
        m_FilePath = filePath;
    }
    ofstream file(m_FilePath);

    if (!file.is_open())
    {
        return false;        
    }
    auto subscriberCollection = m_Collection.GetCollection();
    for(auto subscriberPtr : subscriberCollection)
    {
        CSubscriber subscriber = *subscriberPtr;
        CName name = subscriber.GetName();
        file << name.GetValue() << endl;
        CPostAddress address = subscriber.GetPostAddress();
        file << address.GetValue() << endl;

        auto phones = subscriber.GetPhoneNumbers();

        for(auto phone : phones)
        {
            file << phone->GetValue() << endl;
        }
        file << endl;

        auto emails = subscriber.GetEmails();
        for(auto email : emails)
        {
            file << email->GetValue() << endl;
        }
        file << endl;
    }
    m_Collection.SetChanged(false);
    file.close();
    return true;
}

bool CAddressBook::Read(string filePath)
{
    if (filePath != "")
    {
        m_FilePath = filePath;
    }
    ifstream file(m_FilePath);

    if (!file.is_open())
    {
        return false;        
    }
    m_Collection.Clear();
    while(!file.eof())
    {
        string str;
        getline(file, str);
        if (str != "")
        {
            CSubscriber subscriber;
            subscriber.SetName(str);
            getline(file, str);
            subscriber.SetPostAddress(str);

            getline(file, str);
            while(str != "")
            {
                subscriber.AddPhoneNumber(str);
                getline(file, str);
            }

            getline(file, str);
            while(str != "")
            {
                subscriber.AddEmail(str);
                getline(file, str);
            }
            m_Collection.Add(subscriber);
        }        
    }
    m_Collection.SetChanged(false);
    return true;
}