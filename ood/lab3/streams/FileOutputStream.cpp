#include "FileOutputStream.h"

CFileOutputStream::CFileOutputStream(const std::string& fileName)
{
	m_file.open(fileName, std::ofstream::binary);
	if (!m_file.is_open())
	{
		throw std::ios_base::failure("Can not open file");
	}
}

CFileOutputStream::~CFileOutputStream()
{}

void CFileOutputStream::WriteByte(uint8_t byte)
{
	if (!m_file.put(byte))
	{
		throw std::ios_base::failure("Can not write data to file");
	}
}

void CFileOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	const char* dataPtr = static_cast<const char*>(srcData);
	if (!m_file.write(dataPtr, size * sizeof(char)))
	{
		throw std::ios_base::failure("Can not write data to file");
	}
}
