#include "MemoryOutputStream.h"

CMemoryOutputStream::CMemoryOutputStream()
{}

CMemoryOutputStream::~CMemoryOutputStream()
{}

void CMemoryOutputStream::WriteByte(uint8_t byte)
{
	m_buffer.push_back(byte);
}

void CMemoryOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	const uint8_t* dataPtr = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(*dataPtr);
		++dataPtr;
	}
}