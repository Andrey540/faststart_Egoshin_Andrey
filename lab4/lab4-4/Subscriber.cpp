#include "stdafx.h"
#include "Subscriber.h"
#include <string>
#include <memory>
#include <iostream>

using namespace std;

CSubscriber::CSubscriber(void)
{}

CSubscriber::CSubscriber(const string& name) : m_Name(name)
{}

CSubscriber::~CSubscriber(void)
{}

bool CSubscriber::SetName(const string& name)
{
    if (name.length() > 0)
    {
        m_Name.SetValue(name);
    }
    else
    {
        return false;
    }
    return true;
}

CName CSubscriber::GetName() const
{
    return m_Name;
}

void CSubscriber::SetPostAddress(const string& address)
{
    m_PostAddress.SetValue(address);
}

CPostAddress CSubscriber::GetPostAddress() const
{
    return m_PostAddress;
}

bool CSubscriber::AddPhoneNumber(const CPhoneNumber& phoneNumber)
{    
    return m_PhoneNumbers.Add(phoneNumber);
}

bool CSubscriber::AddPhoneNumber(const string& phoneNumber)
{    
    return m_PhoneNumbers.Add(phoneNumber);
}

bool CSubscriber::DeletePhoneNumber(CPhoneNumber& phoneNumber)
{    
    return m_PhoneNumbers.Delete(phoneNumber);
}

bool CSubscriber::DeletePhoneNumber(int index)
{    
    return m_PhoneNumbers.Delete(index);
}

bool CSubscriber::ChangePhoneNumber(int index, const CPhoneNumber& phoneNumber)
{
    return m_PhoneNumbers.Change(index, phoneNumber);
}

int CSubscriber::GetPhoneNumberIndex(CPhoneNumber& phoneNumber) const
{
    return m_PhoneNumbers.GetIndex(phoneNumber);
}

int CSubscriber::GetEmailIndex(CEmail& email) const
{
    return m_Emails.GetIndex(email);
}

vector<PhoneNumberPtr> CSubscriber::GetPhoneNumberMaches(const string& phoneNumber) const
{
    return m_PhoneNumbers.GetMatches(phoneNumber);
}

vector<PhoneNumberPtr> CSubscriber::GetPhoneNumbers() const
{
    return m_PhoneNumbers.GetCollection();
}

bool CSubscriber::IsPhoneNumberMaches(const string& phoneNumber) const
{
    return m_PhoneNumbers.IsMatches(phoneNumber);
}

CStringFieldCollection<CPhoneNumber>& CSubscriber::GetPhoneNumberCollection()
{
    return m_PhoneNumbers;
}

bool CSubscriber::AddEmail(const CEmail& email)
{    
    return m_Emails.Add(email);
}

bool CSubscriber::AddEmail(const string& email)
{    
    return m_Emails.Add(email);
}

bool CSubscriber::DeleteEmail(CEmail& email)
{    
    return m_Emails.Delete(email);
}

bool CSubscriber::DeleteEmail(int index)
{    
    return m_Emails.Delete(index);
}

bool CSubscriber::ChangeEmail(int index, const CEmail& email)
{
    return m_Emails.Change(index, email);
}

vector<EmailPtr> CSubscriber::GetEmailMaches(const string& email) const
{
    return m_Emails.GetMatches(email);
}

vector<EmailPtr> CSubscriber::GetEmails() const
{
    return m_Emails.GetCollection();
}

bool CSubscriber::IsEmailMaches(const std::string& email) const
{
    return m_Emails.IsMatches(email);
}

bool CSubscriber::IsContainEmail(const std::string& email)
{
    return m_Emails.IsContain(email);
}

CStringFieldCollection<CEmail>& CSubscriber::GetEmailCollection()
{
    return m_Emails;
}

void CSubscriber::Print(string ident) const
{
    cout << "Subscriber " << ident << endl;
    cout << "Name: ";
    m_Name.Print();
    if (m_PostAddress.GetValue() != "")
    {
        cout << "Post address: ";
        m_PostAddress.Print();
    }
    if (m_PhoneNumbers.GetSize() > 0)
    {
        cout << "Phone numbers: " << endl;
        m_PhoneNumbers.Print("   ");
    }
    if (m_Emails.GetSize() > 0)
    {
        cout << "Emails: " << endl;
        m_Emails.Print("   ");
    }
}