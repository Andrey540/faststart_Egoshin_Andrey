#include "EncryptStreamDecorator.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iterator>
#include <random>

CEncryptStreamDecorator::CEncryptStreamDecorator(IInputStreamPtr && inputStream, unsigned seed)
	: CInputStreamDecorator(move(inputStream))
{
	std::iota(std::begin(m_shuffleTable), std::end(m_shuffleTable), 0);
	std::shuffle(std::begin(m_shuffleTable), std::end(m_shuffleTable), std::mt19937{seed});
}

CEncryptStreamDecorator::~CEncryptStreamDecorator()
{}

uint8_t CEncryptStreamDecorator::DecorateByte(uint8_t byte)
{
	return m_shuffleTable[byte];
}

std::streamsize CEncryptStreamDecorator::DecorateBlock(void * dstBuffer, std::vector<uint8_t>& readBuffer)
{
	uint8_t* dataPtr = static_cast<uint8_t*>(dstBuffer);
	for (unsigned i = 0; i < readBuffer.size(); ++i)
	{
		dataPtr[i] = DecorateByte(readBuffer[i]);
	}
	return readBuffer.size();
}
