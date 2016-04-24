#include "DecryptStreamDecorator.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iterator>
#include <random>

CDecryptStreamDecorator::CDecryptStreamDecorator(IOutputStreamPtr && outputStream, unsigned seed)
	: COutputStreamDecorator(move(outputStream))
{
	uint8_t shuffleTable[256];
	std::iota(std::begin(shuffleTable), std::end(shuffleTable), 0);
	std::shuffle(std::begin(shuffleTable), std::end(shuffleTable), std::mt19937{ seed });

	for (int i = 0; i < std::size(shuffleTable); ++i)
	{
		m_unShuffleTable[shuffleTable[i]] = i;
	}
}

CDecryptStreamDecorator::~CDecryptStreamDecorator()
{}

uint8_t CDecryptStreamDecorator::DecorateByte(uint8_t byte)
{
	return m_unShuffleTable[byte];
}

void CDecryptStreamDecorator::DecorateBlock(const void * srcData, std::streamsize size, std::vector<uint8_t>& buffer)
{
	const uint8_t* dataPtr = static_cast<const uint8_t*>(srcData);
	for (int i = 0; i < size; ++i)
	{
		buffer.push_back(DecorateByte(dataPtr[i]));
	}
}
