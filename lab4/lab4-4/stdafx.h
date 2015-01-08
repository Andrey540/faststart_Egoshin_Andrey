// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"
#include "AddressBook.h"
#include <functional>

typedef std::shared_ptr<CStringField> StringFieldPtr;

void ExecuteMainMenu(CAddressBook& addressBook);
void PrintMainMenu();
bool ProcessMainMenuChoose(int choose, CAddressBook& addressBook);
std::vector<SubscriberPtr> GetSubscriberMatches(CAddressBook& addressBook);
void PrintSubscribers(std::vector<SubscriberPtr> subscribers);
void ProcessSearchSubscribers(CAddressBook& addressBook);
void FillInSubscriberParameters(std::string& name, std::string& address, std::string& phone, std::string& email);
void ProcessAddSubscriber(CAddressBook& addressBook);
void ProcessDeleteSubscriber(CAddressBook& addressBook);
int GetChooseSunscriber(CAddressBook& addressBook, std::vector<SubscriberPtr>& subscribers);
void ProcessEditSubscriber(CAddressBook& addressBook);
void PrintEditSubscriberMenu();
bool ProcessEditSubscriberChoose(int choose, int index, CAddressBook& addressBook, CSubscriber& subscriber);
void ExecuteEditSubscriberMenu(CAddressBook& addressBook, CSubscriber& subscriber, int index);

void ExecuteEditEmails(CSubscriber& subscriber);
void ExecuteEditPhoneNumbers(CSubscriber& subscriber);
void PrintEditFieldMenu(std::string fieldName);
bool ProcessEditFieldChoose(int choose, std::string name, CSubscriber& subscriber, std::function<std::vector<StringFieldPtr>(CSubscriber& subscriber, std::string value)> getMatches,
                            std::function<bool(CSubscriber& subscriber, int index)> deleteField, std::function<bool(CSubscriber& subscriber, int index, std::string value)> changeField,
                            std::function<bool(CSubscriber& subscriber, std::string value)> addField, std::function<int(CSubscriber& subscriber, CStringField field)> getIndex);
void ProcessSearchFields(CSubscriber& subscriber, std::string name, std::function<std::vector<StringFieldPtr>(CSubscriber& subscriber, std::string value)> getMatches);
void PrintFields(std::vector<StringFieldPtr>& fields);
void ProcessChangeField(CSubscriber& subscriber, std::string name, std::function<std::vector<StringFieldPtr>(CSubscriber& subscriber, std::string value)> getMatches,
                        std::function<bool(CSubscriber& subscriber, int index, std::string value)> changeField, std::function<int(CSubscriber& subscriber, CStringField field)> getIndex);
int GetChooseField(std::string name, CSubscriber& subscriber, std::vector<StringFieldPtr>& fields, std::function<int(CSubscriber& subscriber, CStringField field)> getIndex);
void ProcessDeleteField(CSubscriber& subscriber, std::string name, std::function<std::vector<StringFieldPtr>(CSubscriber& subscriber, std::string value)> getMatches,
                        std::function<bool(CSubscriber& subscriber, int index)> deleteField, std::function<int(CSubscriber& subscriber, CStringField field)> getIndex);
