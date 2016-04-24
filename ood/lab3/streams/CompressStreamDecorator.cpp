#include "CompressStreamDecorator.h"
#include <iostream>

CCompressStreamDecorator::CCompressStreamDecorator(IInputStreamPtr && inputStream)
	: CInputStreamDecorator(move(inputStream))
{
}

CCompressStreamDecorator::~CCompressStreamDecorator()
{}

uint8_t CCompressStreamDecorator::DecorateByte(uint8_t byte)
{
	return byte;
}

std::streamsize CCompressStreamDecorator::DecorateBlock(void * dstBuffer, std::vector<uint8_t>& readBuffer)
{
	uint8_t* dataPtr = static_cast<uint8_t*>(dstBuffer);
	uint8_t prevByte = readBuffer.size() > 0 ? readBuffer[0] : 0;
	uint8_t count = 0;
	std::streamsize dstBufferLength = 0;
	for (unsigned i = 0; i < readBuffer.size(); ++i)
	{
		if (readBuffer[i] == prevByte)
		{
			++count;
		}
		else
		{
			dataPtr[dstBufferLength] = prevByte;
			dataPtr[dstBufferLength + 1] = count;
			dstBufferLength += 2;
			prevByte = readBuffer[i];
			count = 1;
		}
	}
	if (dstBufferLength > 0)
	{
		dataPtr[dstBufferLength] = prevByte;
		dataPtr[dstBufferLength + 1] = count;
		dstBufferLength += 2;
	}
	return dstBufferLength;
}