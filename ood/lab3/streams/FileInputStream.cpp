#include "FileInputStream.h"
#include<iostream>
#include<fstream>

CFileInputStream::CFileInputStream(const std::string& fileName)
{
	m_file.open(fileName, std::ifstream::binary);
	if (!m_file.is_open())
	{
		throw std::ios_base::failure("Can not open file");
	}
}

CFileInputStream::~CFileInputStream()
{}

bool CFileInputStream::IsEOF() const
{	
	return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	uint8_t result = m_file.get();
	if (!m_file)
	{
		throw std::ios_base::failure("Can not read file");
	}
	if (m_file.peek() == EOF)
	{
		m_file.setstate(std::ios::eofbit);
	}
	return result;
}

std::streamsize CFileInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	if (IsEOF())
	{
		return 0;
	}
	char* dataPtr = static_cast<char*>(dstBuffer);
	m_file.read(dataPtr, size * sizeof(char));
	return m_file.gcount();
}
