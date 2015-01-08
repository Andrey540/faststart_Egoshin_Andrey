#include "StringField.h"
#include "Name.h"
#include "PostAddress.h"
#include "PhoneNumber.h"
#include "Email.h"
#include "StringFieldCollection.h"

#pragma once

typedef std::shared_ptr<CEmail> EmailPtr;
typedef std::shared_ptr<CPhoneNumber> PhoneNumberPtr;

class CSubscriber
{
public:
    CSubscriber(void);
    CSubscriber(const std::string& name);
    bool SetName(const std::string& name);
    CName GetName() const;
    void SetPostAddress(const std::string& address);
    CPostAddress GetPostAddress() const;
    bool AddPhoneNumber(const std::string& phoneNumber);
    bool AddPhoneNumber(const CPhoneNumber& phoneNumber);
    bool DeletePhoneNumber(CPhoneNumber& phoneNumber);
    bool DeletePhoneNumber(int index);
    bool ChangePhoneNumber(int index, const CPhoneNumber& phoneNumber);
    int GetPhoneNumberIndex(CPhoneNumber& phoneNumber) const;
    std::vector<PhoneNumberPtr> GetPhoneNumberMaches(const std::string& phoneNumber) const;    
    std::vector<PhoneNumberPtr> GetPhoneNumbers() const;
    bool IsPhoneNumberMaches(const std::string& phoneNumber) const;
    CStringFieldCollection<CPhoneNumber>& GetPhoneNumberCollection();
    bool AddEmail(const std::string& email);
    bool AddEmail(const CEmail& email);
    bool ChangeEmail(int index, const CEmail& email);
    int GetEmailIndex(CEmail& email) const;
    bool DeleteEmail(CEmail& email);
    bool DeleteEmail(int index);
    bool IsContainEmail(const std::string& email);
    std::vector<EmailPtr> GetEmailMaches(const std::string& email) const;
    std::vector<EmailPtr> GetEmails() const;
    bool IsEmailMaches(const std::string& email) const;
    CStringFieldCollection<CEmail>& GetEmailCollection();
    void Print(std::string ident = "") const;
    ~CSubscriber(void);

    bool const operator == (CSubscriber other)
    {
        CName otherName = other.GetName();
        CPostAddress otherPostAddress = other.GetPostAddress(); 
        CStringFieldCollection<CPhoneNumber> otherPhones = other.GetPhoneNumberCollection();
        CStringFieldCollection<CEmail> otherEmails = other.GetEmailCollection();               
        return (otherName == m_Name) && (otherPostAddress == m_PostAddress) &&
               (otherPhones == m_PhoneNumbers) && (otherEmails == m_Emails);
    }

private:
    CName        m_Name;
    CPostAddress m_PostAddress;
    CStringFieldCollection<CPhoneNumber> m_PhoneNumbers;
    CStringFieldCollection<CEmail>       m_Emails;
};

