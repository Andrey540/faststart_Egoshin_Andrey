#include "MemoryInputStream.h"
#include <istream>

CMemoryInputStream::CMemoryInputStream(std::vector<uint8_t>& buffer) : m_buffer(buffer)
{}

CMemoryInputStream::~CMemoryInputStream()
{}

bool CMemoryInputStream::IsEOF() const
{
	return m_position == m_buffer.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
	if (IsEOF())
	{		
		throw std::ios_base::failure("memory is empty");
	}
	++m_position;
	return m_buffer[m_position - 1];
}

std::streamsize CMemoryInputStream::ReadBlock(void * dstBuffer, std::streamsize size)
{
	std::streamsize allowSize = m_buffer.size() - m_position;
	std::streamsize readSize = (allowSize < size) ? allowSize : size;

	uint8_t* dataPtr = static_cast<uint8_t*>(dstBuffer);
	for (std::streamsize i = 0; i < readSize; ++i)
	{
		*dataPtr = ReadByte();
		++dataPtr;
	}
	return readSize;
}
