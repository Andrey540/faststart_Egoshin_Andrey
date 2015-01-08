#include <string>

#pragma once
class CFile
{
typedef enum
{
    FILE_NOT_OPEN = -1,
    CAN_NOT_READ_FILE = -2,
}FILE_ERROR;

public:
    CFile(void);
    ~CFile(void);
    bool Open(std::string filePath, std::string mode);
    bool IsOpened() const;
    void Close();
    bool IsEndOfFile() const;
    bool Seek(unsigned long position);
    long GetPosition() const;
    long GetLength() const;
    bool PutChar(char ch);
    char GetChar();
    size_t Write(void* const buffer, size_t size);
    size_t Read(void* const buffer, size_t size);

private:
    FILE* m_File;
};

