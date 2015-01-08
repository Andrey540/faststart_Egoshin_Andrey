// AddressBookTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab4-4\StringField.h"
#include "..\lab4-4\Name.h"
#include "..\lab4-4\PostAddress.h"
#include "..\lab4-4\PhoneNumber.h"
#include "..\lab4-4\Email.h"
#include "..\lab4-4\StringFieldCollection.h"
#include "..\lab4-4\Subscriber.h"
#include "..\lab4-4\SubscriberCollection.h"
#include "..\lab4-4\AddressBook.h"

template <typename T, typename F, typename EqualFn>
bool VerifyObjectImmutability(T const& obj, F const& fn, EqualFn const& equal)
{
    T copy(obj);
    fn(copy);
    return equal(copy, obj);
}

template <typename T, typename F>
bool VerifyObjectImmutability(T const& obj, F const& fn)
{
    return VerifyObjectImmutability(obj, fn, std::equal_to<T>());
}

struct CreatedNameWithSetValueFixture
{    
    CName name;
    CreatedNameWithSetValueFixture()
    {
        name = CName("Иванов Сергей Петрович");
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedNameWithSetValue,  CreatedNameWithSetValueFixture)

	BOOST_AUTO_TEST_CASE(HasMatches)
	{
        BOOST_CHECK(name.IsMatches("Сергей иванов"));
        BOOST_CHECK(name.IsMatches("Иванов"));
        BOOST_CHECK(name.IsMatches("Иванов Сергей"));
        BOOST_CHECK(name.IsMatches("Сергей Петрович"));
        BOOST_CHECK(name.IsMatches("Иванов ПетровиЧ"));
        BOOST_CHECK(name.IsMatches("Петрович"));
        BOOST_CHECK(name.IsMatches("Сергей Петрович Иванов"));
        BOOST_CHECK(name.IsMatches("Иванов Сергей Петрович"));
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        BOOST_CHECK(!name.IsMatches("Сергеев Иван Петрович"));
        BOOST_CHECK(!name.IsMatches("Иванов Иван Петрович"));
        BOOST_CHECK(!name.IsMatches("Иван"));
        BOOST_CHECK(!name.IsMatches("Семён Семёныч Горбунков"));
	}

BOOST_AUTO_TEST_SUITE_END()

struct CreatedAddressWithSetValueFixture
{    
    CPostAddress postAddress;
    CreatedAddressWithSetValueFixture()
    {
        postAddress = CPostAddress("Москва, Шаболовка, 37, 54");
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedAddressWithSetValue,  CreatedAddressWithSetValueFixture)

	BOOST_AUTO_TEST_CASE(HasMatches)
	{
        BOOST_CHECK(postAddress.IsMatches("Шаболовка, 37"));
        BOOST_CHECK(postAddress.IsMatches("шаболовКа, 37"));
        BOOST_CHECK(postAddress.IsMatches("москва, 54"));
        BOOST_CHECK(postAddress.IsMatches("москва, шаболовка, 37, 54"));
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        BOOST_CHECK(!postAddress.IsMatches("Йошкар-Ола, Шаболовка"));
        BOOST_CHECK(!postAddress.IsMatches("Москва, Шаболовка, 24"));
	}

BOOST_AUTO_TEST_SUITE_END()

struct CreatedPhoneNumberWithSetValueFixture
{    
    CPhoneNumber phoneNumber;
    CreatedPhoneNumberWithSetValueFixture()
    {
        phoneNumber = CPhoneNumber("+9(988) 123-45-67");
    }
};


BOOST_FIXTURE_TEST_SUITE(CreatedPhoneNumberWithSetValue,  CreatedPhoneNumberWithSetValueFixture)

	BOOST_AUTO_TEST_CASE(HasMatches)
	{
        BOOST_CHECK(phoneNumber.IsMatches("+9(988) 123-45-67"));
        BOOST_CHECK(phoneNumber.IsMatches("+99881234567"));
        BOOST_CHECK(phoneNumber.IsMatches("+998 81 23 45 67"));
        BOOST_CHECK(phoneNumber.IsMatches("23 45 67"));
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        BOOST_CHECK(!phoneNumber.IsMatches("45 23 67"));
        BOOST_CHECK(!phoneNumber.IsMatches("+9(988) 213-45-67"));
	}

BOOST_AUTO_TEST_SUITE_END()


struct CreatedEmailWithSetValueFixture
{    
    CEmail email;
    CreatedEmailWithSetValueFixture()
    {
        email = CEmail("test@mail.ru");
    }
};


BOOST_FIXTURE_TEST_SUITE(CreatedEmailWithSetValue,  CreatedEmailWithSetValueFixture)

	BOOST_AUTO_TEST_CASE(HasMatches)
	{
        BOOST_CHECK(email.IsMatches("TEST@MAIL.RU"));
        BOOST_CHECK(email.IsMatches("TEST@"));
        BOOST_CHECK(email.IsMatches("MAIL.RU"));
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        BOOST_CHECK(!email.IsMatches("TEST1@MAIL.RU"));
        BOOST_CHECK(!email.IsMatches("MAIL.COM"));
	}

BOOST_AUTO_TEST_SUITE_END()


struct CreatedPhoneCollectionWithFillInElementsFixture
{    
    CStringFieldCollection<CPhoneNumber> phones;
    CreatedPhoneCollectionWithFillInElementsFixture()
    {
        phones.Add("+9(988) 123-45-67");
        phones.Add("+9(917) 725-45-65");
        phones.Add("+9(917) 654-23-13");
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedPhoneCollectionWithFillInElements,  CreatedPhoneCollectionWithFillInElementsFixture)

	BOOST_AUTO_TEST_CASE(HasMatches)
	{
        BOOST_CHECK(phones.IsMatches("+99881234567"));
        auto matches = phones.GetMatches("9917");
        BOOST_CHECK_EQUAL(matches.size(), 2);
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        BOOST_CHECK(!phones.IsMatches("45-67-123"));
        auto matches = phones.GetMatches("991773");
        BOOST_CHECK_EQUAL(matches.size(), 0);
	}

    BOOST_AUTO_TEST_CASE(CantAddEqualElement)
	{
        BOOST_CHECK(!phones.Add("+99881234567"));       
        auto matches = phones.GetMatches("+99881234567");
        BOOST_CHECK_EQUAL(matches.size(), 1);
	}

    BOOST_AUTO_TEST_CASE(CantAddEmptyElement)
	{
        BOOST_CHECK(!phones.Add(""));
        BOOST_CHECK_EQUAL(phones.GetSize(), 3);
	}

    BOOST_AUTO_TEST_CASE(CanDeleteExistElement)
	{
        CPhoneNumber number = CPhoneNumber("+99176542313");
        BOOST_CHECK(phones.Delete(number));
        BOOST_CHECK_EQUAL(phones.GetSize(), 2);
        BOOST_CHECK(phones.Delete(1));
        BOOST_CHECK_EQUAL(phones.GetSize(), 1);
	}

    BOOST_AUTO_TEST_CASE(CantDeleteNotExistElement)
	{
        CPhoneNumber number = CPhoneNumber("+99176542314");
        BOOST_CHECK(!phones.Delete(number));
        BOOST_CHECK_EQUAL(phones.GetSize(), 3);
        BOOST_CHECK(!phones.Delete(3));
        BOOST_CHECK_EQUAL(phones.GetSize(), 3);
	}

    BOOST_AUTO_TEST_CASE(CanChangeExistElement)
	{
        CPhoneNumber number = CPhoneNumber("+99176542313");
        BOOST_CHECK(phones.Change(2, number));
	}

    BOOST_AUTO_TEST_CASE(CantSetAlreadyExistElement)
	{
        CPhoneNumber number = CPhoneNumber("+99176542313");
        BOOST_CHECK(!phones.Change(1, number));
	}

    BOOST_AUTO_TEST_CASE(CantSetNotExistElement)
	{
        CPhoneNumber number = CPhoneNumber("+9917643345");
        BOOST_CHECK(!phones.Change(3, number));
	}

BOOST_AUTO_TEST_SUITE_END()

struct JustCreatedSubscriberFixture
{    
    CSubscriber subscriber;
};

BOOST_FIXTURE_TEST_SUITE(JustCreatedSubscriber,  JustCreatedSubscriberFixture)

	BOOST_AUTO_TEST_CASE(CanSetNotEmptyName)
	{
        BOOST_CHECK(subscriber.SetName("Иван"));
        BOOST_CHECK_EQUAL(subscriber.GetName().GetValue(), "Иван");
	}

    BOOST_AUTO_TEST_CASE(CanеSetEmptyName)
	{
        BOOST_CHECK(subscriber.SetName("Иван"));
        BOOST_CHECK(!subscriber.SetName(""));
        BOOST_CHECK_EQUAL(subscriber.GetName().GetValue(), "Иван");
	}

BOOST_AUTO_TEST_SUITE_END()

struct CreatedNotEmptySubscriberCollectionFixture
{    
    CSubscriberCollection subscribers;
    CreatedNotEmptySubscriberCollectionFixture()
    {
        CSubscriber subscriber1("Иванов Иван Иванович");
        subscriber1.SetPostAddress("Москва, Баумана, 34, 32");
        subscriber1.AddEmail("test@mail.ru");
        subscriber1.AddEmail("test1@mail.ru");
        subscriber1.AddPhoneNumber("89325563211");
        subscribers.Add(subscriber1);

        CSubscriber subscriber2("Иванов Сергей Петрович");
        subscriber2.SetPostAddress("Москва, Баумана, 34, 32");
        subscriber2.AddEmail("test2@mail.ru");
        subscriber2.AddPhoneNumber("89325563211");
        subscribers.Add(subscriber2);

        CSubscriber subscriber3("Сергеев Сергий Иванович");
        subscriber3.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber3.AddEmail("test3@mail.ru");
        subscriber3.AddEmail("test4@mail.ru");
        subscriber3.AddPhoneNumber("89177563212");
        subscribers.Add(subscriber3);

        CSubscriber subscriber4("Петров Пётр Петрович");
        subscriber4.SetPostAddress("Санкт-Петербург, Панфилова, 21, 38");
        subscriber4.AddEmail("test5@mail.ru");
        subscriber4.AddPhoneNumber("894775657904");
        subscribers.Add(subscriber4);

        subscribers.SetChanged(false);
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedNotEmptySubscriberCollection,  CreatedNotEmptySubscriberCollectionFixture)

    BOOST_AUTO_TEST_CASE(Has4Elements)
	{
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 4);
	}

    BOOST_AUTO_TEST_CASE(CantAddSubscriberWithoutName)
	{
        CSubscriber subscriber("");
        BOOST_CHECK(!subscribers.Add(subscriber));
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 4);
	}

    BOOST_AUTO_TEST_CASE(CantAddSubscriberWithExistEmail)
	{
        CSubscriber subscriber("Виктор");
        subscriber.AddEmail("test5@mail.ru");
        BOOST_CHECK(!subscribers.Add(subscriber));
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 4);
	}

    BOOST_AUTO_TEST_CASE(CanDeleteExistSubscriber)
	{
        BOOST_CHECK(subscribers.Delete(3));
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 3);
	}

    BOOST_AUTO_TEST_CASE(CantDeleteNotExistSubscriber)
	{
        BOOST_CHECK(!subscribers.Delete(4));
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 4);
	}

    BOOST_AUTO_TEST_CASE(CantChangeSubscriberWithAlreadyExistEmail)
	{
        CSubscriber subscriber("Сергей Пётр Петрович");
        subscriber.SetPostAddress("Санкт-Петербург, Панфилова, 21, 38");
        subscriber.AddEmail("test5@mail.ru");
        subscriber.AddPhoneNumber("894775657904");
        BOOST_CHECK(!subscribers.Change(2, subscriber));
        BOOST_CHECK_EQUAL(subscribers.GetIndex(subscriber), -1);
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 4);
	}

    BOOST_AUTO_TEST_CASE(CanChangeExistSubscriberWithOwnEmail)
	{
        CSubscriber subscriber("Сергеев Сергий Иванович");
        subscriber.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber.AddEmail("test3@mail.ru");
        subscriber.AddEmail("test4@mail.ru");
        subscriber.AddPhoneNumber("89177563212");
        BOOST_CHECK(subscribers.Change(2, subscriber));
        BOOST_CHECK_EQUAL(subscribers.GetIndex(subscriber), 2);
	}

    BOOST_AUTO_TEST_CASE(CanChangeExistSubscriberEmail)
	{
        CSubscriber subscriber("Николаев Николай Николаевич");
        subscriber.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber.AddEmail("test7@mail.ru");
        subscriber.AddPhoneNumber("89177563212");
        BOOST_CHECK(subscribers.Change(2, subscriber));
        BOOST_CHECK_EQUAL(subscribers.GetIndex(subscriber), 2);
	}

    BOOST_AUTO_TEST_CASE(HasMatches)
	{
        auto matches = subscribers.GetMatches("Иванов");
        BOOST_CHECK_EQUAL(matches.size(), 2);
        matches = subscribers.GetMatches("", "москва, баумана");
        BOOST_CHECK_EQUAL(matches.size(), 2);
        matches = subscribers.GetMatches("", "", "77");
        BOOST_CHECK_EQUAL(matches.size(), 2);
        matches = subscribers.GetMatches("", "", "", "test");
        BOOST_CHECK_EQUAL(matches.size(), 4);
        matches = subscribers.GetMatches("");
        BOOST_CHECK_EQUAL(matches.size(), 4);
        matches = subscribers.GetMatches("Сергей", "москва, баумана");
        BOOST_CHECK_EQUAL(matches.size(), 1);   
        matches = subscribers.GetMatches("Сергей", "москва, баумана", "89325563211", "test2@mail.ru");
        BOOST_CHECK_EQUAL(matches.size(), 1);
	}

    BOOST_AUTO_TEST_CASE(HasntMatches)
	{
        auto matches = subscribers.GetMatches("Сергей", "москва, баумана", "89177563212");
        BOOST_CHECK_EQUAL(matches.size(), 0);
        matches = subscribers.GetMatches("Николай");
        BOOST_CHECK_EQUAL(matches.size(), 0);
	}

    BOOST_AUTO_TEST_CASE(CanCleared)
	{
        subscribers.Clear();
        BOOST_CHECK_EQUAL(subscribers.GetSize(), 0);
	}

    BOOST_AUTO_TEST_CASE(ChangeIfAdd)
	{
        CSubscriber subscriber("Николаев Николай Николаевич");
        subscriber.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber.AddEmail("test7@mail.ru");
        subscriber.AddPhoneNumber("89177563212");
        BOOST_CHECK(subscribers.Add(subscriber));
        BOOST_CHECK(subscribers.IsChanged());
	}
    
BOOST_AUTO_TEST_SUITE_END()

struct CreatedSavedThenReadSubscriberCollectionFixture
{    
    CAddressBook addressBook;   
    CreatedSavedThenReadSubscriberCollectionFixture()
    {
        CSubscriber subscriber1("Иванов Иван Иванович");
        subscriber1.SetPostAddress("Москва, Баумана, 34, 32");
        subscriber1.AddEmail("test@mail.ru");
        subscriber1.AddEmail("test1@mail.ru");
        subscriber1.AddPhoneNumber("89325563211");
        addressBook.AddSubscriber(subscriber1);

        CSubscriber subscriber2("Иванов Сергей Петрович");
        subscriber2.SetPostAddress("Москва, Баумана, 34, 32");
        subscriber2.AddEmail("test2@mail.ru");
        subscriber2.AddPhoneNumber("89325563211");
        addressBook.AddSubscriber(subscriber2);

        addressBook.Save("subscriber.txt");
        addressBook.Read("subscriber.txt");
    }
};

BOOST_FIXTURE_TEST_SUITE(CreatedSavedThenReadSubscriberCollection, CreatedSavedThenReadSubscriberCollectionFixture)

    BOOST_AUTO_TEST_CASE(Has2Elements)
	{
        BOOST_CHECK_EQUAL(addressBook.GetSize(), 2);
	}

    BOOST_AUTO_TEST_CASE(HasMatches)
	{
        auto matches = addressBook.GetMatches("Иванов Иван Иванович", "Москва, Баумана, 34, 32", "89325563211", "test1@mail.ru");
        BOOST_CHECK_EQUAL(matches.size(), 1);
        matches = addressBook.GetMatches("Иванов Сергей Петрович", "Москва, Баумана, 34, 32", "89325563211", "test2@mail.ru");
        BOOST_CHECK_EQUAL(matches.size(), 1);
	}

    BOOST_AUTO_TEST_CASE(CanSave)
	{
        BOOST_CHECK(addressBook.Save("subscriber.txt"));
	}

    BOOST_AUTO_TEST_CASE(CanRead)
	{
        BOOST_CHECK(addressBook.Read("subscriber.txt"));
	}

    BOOST_AUTO_TEST_CASE(NotChangeIfSaved)
	{
        CSubscriber subscriber("Николаев Николай Николаевич");
        subscriber.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber.AddEmail("test7@mail.ru");
        subscriber.AddPhoneNumber("89177563212");
        BOOST_CHECK(addressBook.AddSubscriber(subscriber));
        BOOST_CHECK(addressBook.IsChanged());
        BOOST_CHECK(addressBook.Save("subscriber.txt"));
        BOOST_CHECK(!addressBook.IsChanged());
	}

    BOOST_AUTO_TEST_CASE(NotChangeIfRead)
	{
        CSubscriber subscriber("Николаев Николай Николаевич");
        subscriber.SetPostAddress("Йошкар-Ола, Панфилова, 21, 35");
        subscriber.AddEmail("test7@mail.ru");
        subscriber.AddPhoneNumber("89177563212");
        BOOST_CHECK(addressBook.AddSubscriber(subscriber));
        BOOST_CHECK(addressBook.IsChanged());
        BOOST_CHECK(addressBook.Read("subscriber.txt"));
        BOOST_CHECK(!addressBook.IsChanged());
	}
    
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(RemoveSavedFiles)
{
    BOOST_CHECK(remove("subscriber.txt") == 0);
}