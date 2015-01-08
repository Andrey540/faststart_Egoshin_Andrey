#include "stdafx.h"
#include "File.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

using namespace std;

CFile::CFile(void) : m_File(nullptr)
{}

CFile::~CFile(void)
{
    Close();
}

bool CFile::Open(string filePath, string mode)
{
    Close();
    m_File = fopen(filePath.c_str(), mode.c_str());
    return IsOpened();
}

bool CFile::IsOpened() const
{
    return m_File != nullptr;
}

void CFile::Close()
{
    if (IsOpened())
    {
        fclose(m_File);
    }
    m_File = nullptr;
}

bool CFile::IsEndOfFile() const
{
    return feof(m_File) == 0;
}

long CFile::GetPosition() const
{
    return IsOpened() ? ftell(m_File) : -1;
}

long CFile::GetLength() const
{
    if (!IsOpened())
    {
        return -1;
    }
    long currentPosition = GetPosition();
    fseek(m_File, 0, SEEK_END);
    long size = ftell(m_File);
    fseek(m_File, currentPosition, SEEK_SET);
    return size;
}

bool CFile::PutChar(char ch)
{
    if (!IsOpened())
    {
        return false;
    }
    return ch == putc(ch , m_File);
}

char CFile::GetChar()
{
    if (!IsOpened())
    {
        return FILE_NOT_OPEN;
    }

    char ch = fgetc(m_File);

    if (ferror(m_File))
    {
        return CAN_NOT_READ_FILE;
    }
    return ch;
}

bool CFile::Seek(unsigned long position)
{
    if (!IsOpened())
    {
        return false;
    }

    return fseek(m_File, position, SEEK_SET) == 0;
}

size_t CFile::Write(void* const buffer, size_t size)
{
    if (!IsOpened())
    {
        return -1;
    }

    return fwrite(buffer, sizeof(char), size, m_File);
}

size_t CFile::Read(void* const buffer, size_t size)
{
    if (!IsOpened())
    {
        return -1;
    }

    fread(buffer, 1, size, m_File);
    return 12;
}