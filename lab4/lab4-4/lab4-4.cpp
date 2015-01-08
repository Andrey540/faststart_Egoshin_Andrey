#include "stdafx.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <functional>

using namespace std;

const string FILE_PATH = "subscribers_base.txt";

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);    
    CAddressBook addressBook;
    addressBook.Read(FILE_PATH);
    ExecuteMainMenu(addressBook);
    
    if (addressBook.IsChanged())
    {         
        cout << "Do you want save changes? (y/n)" << endl;
        char choose;
        cin >> choose;
        if (choose == 'y')
        {
            addressBook.Save();
        }
    }
	return 0;
}

vector<StringFieldPtr> InterpretStringFieldVector(vector<EmailPtr>& other)
{
    std::vector<StringFieldPtr> collection;
    for (auto item : other)
    {
        collection.push_back(item);
    }
    return collection;
}

vector<StringFieldPtr> InterpretStringFieldVector(vector<PhoneNumberPtr>& other)
{
    std::vector<StringFieldPtr> collection;
    for (auto item : other)
    {
        collection.push_back(item);
    }
    return collection;
}

int GetEmailIndex(CSubscriber& subscriber, CStringField field)
{
    return subscriber.GetEmailIndex(CEmail(field));
}

int GetPhoneNumberIndex(CSubscriber& subscriber, CStringField field)
{
    return subscriber.GetPhoneNumberIndex(CPhoneNumber(field));
}

bool DeleteEmail(CSubscriber& subscriber, int index)
{
    return subscriber.DeleteEmail(index);
}

bool DeletePhoneNumber(CSubscriber& subscriber, int index)
{
    return subscriber.DeletePhoneNumber(index);
}

bool ChangeEmail(CSubscriber& subscriber, int index, string value)
{
    return subscriber.ChangeEmail(index, value);
}

bool ChangePhoneNumber(CSubscriber& subscriber, int index, string value)
{
    return subscriber.ChangePhoneNumber(index, value);
}

bool AddEmail(CSubscriber& subscriber, string value)
{
    return subscriber.AddEmail(value);
}

bool AddPhoneNumber(CSubscriber& subscriber, string value)
{
    return subscriber.AddPhoneNumber(value);
}

vector<StringFieldPtr> GetEmailMaches(CSubscriber& subscriber, string email)
{
    auto emails = subscriber.GetEmailMaches(email);
    return InterpretStringFieldVector(emails);
}

vector<StringFieldPtr> GetPhoneNumberMaches(CSubscriber& subscriber, string phone)
{
    auto phones = subscriber.GetPhoneNumberMaches(phone);
    return InterpretStringFieldVector(phones);
}

void PrintMainMenu()
{
    system("cls");
    cout << "Your choose:" << endl;
    cout << "1. Search subscriber" << endl;
    cout << "2. Add subscriber" << endl;
    cout << "3. Edit subscriber" << endl;
    cout << "4. Delete subscriber" << endl;
    cout << "5. Exit" << endl;
}

void ExecuteMainMenu(CAddressBook& addressBook)
{
    PrintMainMenu();
    int choose;
    cin >> choose;
    while(!ProcessMainMenuChoose(choose, addressBook))
    {
        PrintMainMenu();
        cin >> choose;
    }
}

bool ProcessMainMenuChoose(int choose, CAddressBook& addressBook)
{
    switch(choose)
    {
        case 1 :
            ProcessSearchSubscribers(addressBook);
            break;
        case 2 :
            ProcessAddSubscriber(addressBook);
            break;
        case 3 :
            ProcessEditSubscriber(addressBook);
            break;
        case 4 :
            ProcessDeleteSubscriber(addressBook);
            break;
        case 5 :
            return true;
    }
    return false;
}

void ProcessSearchSubscribers(CAddressBook& addressBook)
{
    vector<SubscriberPtr> subscribers = GetSubscriberMatches(addressBook);
    PrintSubscribers(subscribers);
    cout << endl << "Press any key for continue" << endl;
    _getch();
}

void ProcessAddSubscriber(CAddressBook& addressBook)
{
    CSubscriber subscriber;
    string value;
    cout << "Enter name ";
    while(value == "")
    {
        getline(cin, value);
    }

    subscriber.SetName(value);
    cout << "Enter post address ";    
    getline(cin, value);
    subscriber.SetPostAddress(value);

    while(value != "s")
    {
        cout << "Enter phone number (s - for skip) ";    
        getline(cin, value);;
        if (value != "s")
        {
            subscriber.AddPhoneNumber(value);
        }
    }
    value = "";
    while(value != "s")
    {
        cout << "Enter email (s - for skip) ";    
        getline(cin, value);
        if (value != "s")
        {
            subscriber.AddEmail(value);
        }
    }

    if (!addressBook.AddSubscriber(subscriber))
    {
        cout << endl << "Cant add subscriber press any key for continue" << endl;
        _getch();
    }
}

void FillInSubscriberParameters(string& name, string& address, string& phone, string& email)
{
    cout << "Enter name ";
    getchar();
    getline(cin, name);
    cout << "Enter post address ";
    getline(cin, address);
    cout << "Enter phone number ";
    getline(cin, phone);
    cout << "Enter email ";
    getline(cin, email);
}

vector<SubscriberPtr> GetSubscriberMatches(CAddressBook& addressBook)
{
    string name, address, phone, email;
    FillInSubscriberParameters(name, address, phone, email);
    return addressBook.GetMatches(name, address, phone, email);
}

void PrintSubscribers(vector<SubscriberPtr> subscribers)
{
    if (subscribers.size() == 0)
    {
        cout << "Empty list" << endl;
    }
    for (unsigned i = 0; i < subscribers.size(); ++i)
    {
        subscribers[i]->Print(to_string(i));
    }
}

void ProcessDeleteSubscriber(CAddressBook& addressBook)
{
    vector<SubscriberPtr> subscribers = GetSubscriberMatches(addressBook);
    int index = GetChooseSunscriber(addressBook, subscribers);
    if (index >= 0)
    {
        addressBook.DeleteSubscriber(index);
    }
}

int GetChooseSunscriber(CAddressBook& addressBook, vector<SubscriberPtr>& subscribers)
{
    PrintSubscribers(subscribers);
    if (subscribers.size() == 0)
    {
        _getch();
        return -1;
    }
    cout << endl << "Choose subscriber or enter R for return" << endl;
    string chooseStr;
    while(true)
    {
        cin >> chooseStr;
        if (chooseStr == "R")
        {
            return -1;
        }
        else
        {
            unsigned choose = stoi(chooseStr);
            if (choose >= 0 && choose < subscribers.size())
            {
                return addressBook.GetIndex(*subscribers[choose]);
            }
        }
    }
    return -1;
}

void ProcessEditSubscriber(CAddressBook& addressBook)
{
    vector<SubscriberPtr> subscribers = GetSubscriberMatches(addressBook);
    int index = GetChooseSunscriber(addressBook, subscribers);
    if (index >= 0)
    {
        CSubscriber subscriber = *subscribers[index];
        ExecuteEditSubscriberMenu(addressBook, subscriber, index);
    }
}

void PrintEditSubscriberMenu()
{
    system("cls");
    cout << "Your choose:" << endl;
    cout << "1. Change name" << endl;
    cout << "2. Change post address" << endl;
    cout << "3. Edit phone numbers" << endl;
    cout << "4. Edit emails" << endl;
    cout << "5. Save changes" << endl;
    cout << "6. Return" << endl;
}

bool ProcessEditSubscriberChoose(int choose, int index, CAddressBook& addressBook, CSubscriber& subscriber)
{
    string value;
    switch(choose)
    {
        case 1 :
            cout << "Enter new name ";
            while(value == "")
            {
                getline(cin, value);
            }
            subscriber.SetName(value);
            break;
        case 2 :
            cout << "Enter new post address ";
            getchar();
            getline(cin, value);
            subscriber.SetPostAddress(value);
            break;
        case 3 :
            ExecuteEditPhoneNumbers(subscriber);
            break;
        case 4 :
            ExecuteEditEmails(subscriber);
            break;
        case 5 :
            if (!addressBook.ChangeSubscriber(index, subscriber))
            {
                cout << "Cant save changes press any key for continue" << endl; 
                _getch();
            }
            break;
        case 6 :
            return true;
    }
    return false;
}

void ExecuteEditSubscriberMenu(CAddressBook& addressBook, CSubscriber& subscriber, int index)
{
    PrintEditSubscriberMenu();
    int choose;
    cin >> choose;
    while(!ProcessEditSubscriberChoose(choose, index, addressBook, subscriber))
    {
        PrintEditSubscriberMenu();
        cin >> choose;
    }
}

void PrintEditFieldMenu(string fieldName)
{
    system("cls");
    cout << "Your choose:" << endl;
    cout << "1. Search " << fieldName << endl;
    cout << "2. Add " << fieldName << endl;
    cout << "3. Change " << fieldName << endl;
    cout << "4. Delete " << fieldName << endl;
    cout << "5. Return" << endl;
}

void ExecuteEditPhoneNumbers(CSubscriber& subscriber)
{
    string name = "phone number";
    PrintEditFieldMenu(name);
    int choose;
    cin >> choose;
    while(!ProcessEditFieldChoose(choose, name, subscriber, GetPhoneNumberMaches, DeletePhoneNumber, ChangePhoneNumber, AddPhoneNumber, GetPhoneNumberIndex))
    {
        PrintEditFieldMenu(name);
        cin >> choose;
    }
}

void ExecuteEditEmails(CSubscriber& subscriber)
{
    string name = "email";
    PrintEditFieldMenu(name);
    int choose;
    cin >> choose;
    while(!ProcessEditFieldChoose(choose, name, subscriber, GetEmailMaches, DeleteEmail, ChangeEmail, AddEmail, GetEmailIndex))
    {
        PrintEditFieldMenu(name);
        cin >> choose;
    }
}

bool ProcessEditFieldChoose(int choose, string name, CSubscriber& subscriber, function<vector<StringFieldPtr>(CSubscriber& subscriber, string value)> getMatches,
                            function<bool(CSubscriber& subscriber, int index)> deleteField, function<bool(CSubscriber& subscriber, int index, string value)> changeField,
                            function<bool(CSubscriber& subscriber, string value)> addField, function<int(CSubscriber& subscriber, CStringField field)> getIndex)
{
    string value;
    switch(choose)
    {
        case 1 :
            ProcessSearchFields(subscriber, name, getMatches);
            break;
        case 2 :
            cout << "Enter new " << name << " ";
            cin >> value;
            if (!addField(subscriber, value))
            {
                cout << "Cant add " << name << " press any key for continue" << endl;
                _getch();
            }
            break;
        case 3 :
            ProcessChangeField(subscriber, name, getMatches, changeField, getIndex);
            break;
        case 4 :
            ProcessDeleteField(subscriber, name, getMatches, deleteField, getIndex);
            break;
        case 5 :
            return true;
    }

    return false;
}

void ProcessSearchFields(CSubscriber& subscriber, string name, function<vector<StringFieldPtr>(CSubscriber& subscriber, string value)> getMatches)
{
    cout << "Enter " << name << " ";
    string value;
    cin >> value;
    auto fields = getMatches(subscriber, value);
    PrintFields(fields);
    cout << endl << "Press any key for continue" << endl;
    _getch();
}

void PrintFields(vector<StringFieldPtr>& fields)
{
    if (fields.size() == 0)
    {
        cout << "Empty list" << endl;
    }
    for (unsigned i = 0; i < fields.size(); ++i)
    {
        fields[i]->Print(to_string(i) + " ");
    }
}

void ProcessDeleteField(CSubscriber& subscriber, string name, function<vector<StringFieldPtr>(CSubscriber& subscriber, string value)> getMatches,
                        function<bool(CSubscriber& subscriber, int index)> deleteField, function<int(CSubscriber& subscriber, CStringField field)> getIndex)
{
    cout << "Enter " << name << " ";
    string value;
    cin >> value;
    auto fields = getMatches(subscriber, value);
    int index = GetChooseField(name, subscriber, fields, getIndex);
    if (index >= 0)
    {
        deleteField(subscriber, index);
    }
}

void ProcessChangeField(CSubscriber& subscriber, string name, function<vector<StringFieldPtr>(CSubscriber& subscriber, string value)> getMatches,
                        function<bool(CSubscriber& subscriber, int index, string value)> changeField, function<int(CSubscriber& subscriber, CStringField field)> getIndex)
{
    cout << "Enter " << name << " ";
    string value;
    cin >> value;
    auto fields = getMatches(subscriber, value);    
    int index = GetChooseField(name, subscriber, fields, getIndex);
    if (index >= 0)
    {
        cout << "Entre new " << name << " ";
        cin >> value;
        if (!changeField(subscriber, index, value))
        {
            cout << "Cant change " << name << " press any key for continue" << endl;
            _getch();
        }
    }
}

int GetChooseField(string name, CSubscriber& subscriber, vector<StringFieldPtr>& fields, function<int(CSubscriber& subscriber, CStringField field)> getIndex)
{
    PrintFields(fields);
    if (fields.size() == 0)
    {
        _getch();
        return -1;
    }
    cout << endl << "Choose " << name << " or enter R for return" << endl;
    string chooseStr;
    while(true)
    {
        cin >> chooseStr;
        if (chooseStr == "R")
        {
            return -1;
        }
        else
        {
            unsigned choose = stoi(chooseStr);
            if (choose >= 0 && choose < fields.size())
            {
                return getIndex(subscriber, *fields[choose]);
            }
        }
    }
    return -1;
}