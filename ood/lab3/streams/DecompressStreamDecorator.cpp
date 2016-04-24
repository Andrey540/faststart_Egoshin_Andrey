#include "DecompressStreamDecorator.h"
#include <iostream>

CDecompressStreamDecorator::CDecompressStreamDecorator(IOutputStreamPtr && outputStream)
	: COutputStreamDecorator(move(outputStream))
{
}

CDecompressStreamDecorator::~CDecompressStreamDecorator()
{}

uint8_t CDecompressStreamDecorator::DecorateByte(uint8_t byte)
{
	return byte;
}

void CDecompressStreamDecorator::DecorateBlock(const void * srcData, std::streamsize size, std::vector<uint8_t>& buffer)
{
	if (size % 2 != 0)
	{
		throw std::runtime_error("incorrect data length");
	}
	const uint8_t* dataPtr = static_cast<const uint8_t*>(srcData);	
	for (unsigned i = 0; i < size; i += 2)
	{
		uint8_t byte = dataPtr[i];
		uint8_t count = dataPtr[i + 1];
		FilleBuffer(buffer, byte, count);
	}
}

void CDecompressStreamDecorator::FilleBuffer(std::vector<uint8_t>& buffer, uint8_t byte, std::streamsize size)
{	
	for (unsigned j = 0; j < size; ++j)
	{
		buffer.push_back(byte);
	}
}