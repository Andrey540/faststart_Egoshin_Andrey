// TesrtFile.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "..\lab4-3\File.h"


struct JustCreatedFileFixture
{    
    CFile file;
};

BOOST_FIXTURE_TEST_SUITE(JustCreatedFile, JustCreatedFileFixture)

	BOOST_AUTO_TEST_CASE(IsClosed)
	{
        BOOST_CHECK(!file.IsOpened());
	}

    BOOST_AUTO_TEST_CASE(BeingCreatedForWriteIndicateEndOfFileAndEmptySizeAndPosition0)
	{
        BOOST_CHECK(file.Open("Test.txt", "w"));
        BOOST_CHECK(file.IsOpened());
        BOOST_CHECK(file.IsEndOfFile());
        BOOST_CHECK_EQUAL(file.GetPosition(), 0);
        BOOST_CHECK_EQUAL(file.GetLength(), 0);
	}

    BOOST_AUTO_TEST_CASE(CantOpenFileIfNotExist)
	{
        BOOST_CHECK(!file.Open("Test1.txt", "r"));
        BOOST_CHECK(!file.IsOpened());
	}    

BOOST_AUTO_TEST_SUITE_END()


struct JustOpenedFileFixture
{    
    CFile file;
    JustOpenedFileFixture()
    {
        file.Open("Test.txt", "r+");
    }
};

BOOST_FIXTURE_TEST_SUITE(JustOpenedFile, JustOpenedFileFixture)

    BOOST_AUTO_TEST_CASE(CanReopenOtherFileForWrite)
	{
        BOOST_CHECK(file.Open("TestForReopen.txt", "w"));
        BOOST_CHECK(file.IsOpened());
	}

    BOOST_AUTO_TEST_CASE(CanSetPosition10)
	{
        BOOST_CHECK(file.Seek(10));
        BOOST_CHECK_EQUAL(file.GetPosition(), 10);
	}

    BOOST_AUTO_TEST_CASE(CanCloseFile)
	{
        file.Close();
        BOOST_CHECK(!file.IsOpened());
	}

    BOOST_AUTO_TEST_CASE(CanPutCharAndCurrentPosition1AndFileLengthIs1)
	{
        BOOST_CHECK(file.PutChar('A'));
        BOOST_CHECK_EQUAL(file.GetPosition(), 1);
        BOOST_CHECK_EQUAL(file.GetLength(), 1);
	}

    BOOST_AUTO_TEST_CASE(BeingReopenedAbleToReadJustWritenChar)
	{
        BOOST_CHECK(file.Open("Test.txt", "r"));
        BOOST_CHECK_EQUAL(file.GetChar(), 'A');
	}

    BOOST_AUTO_TEST_CASE(BeingReopenedForWriteAbleToWriteBuffer)
	{
        BOOST_CHECK(file.Open("Test.txt", "w"));
        BOOST_CHECK_EQUAL(file.Write("Hello world!", 12), 12);
        BOOST_CHECK_EQUAL(file.GetPosition(), 12);
        BOOST_CHECK_EQUAL(file.GetLength(), 12);
	}

    BOOST_AUTO_TEST_CASE(BeingReopenedForReadAbleToReadJustWritenBuffer)
	{
        BOOST_CHECK(file.Open("Test.txt", "r"));
        char buffer[13] = "";
        BOOST_CHECK_EQUAL(file.Read(buffer, 12), 12);
        BOOST_CHECK_EQUAL(buffer, "Hello world!");
	}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_CASE(RemoveExistingFiles)
{
    BOOST_CHECK(remove("Test.txt") == 0);
    BOOST_CHECK(remove("TestForReopen.txt") == 0);
}




