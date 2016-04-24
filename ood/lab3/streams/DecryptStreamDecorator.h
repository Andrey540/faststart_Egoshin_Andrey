#pragma once
#include "OutputStreamDecorator.h"
class CDecryptStreamDecorator :	public COutputStreamDecorator
{
public:
	CDecryptStreamDecorator(IOutputStreamPtr && outputStream, unsigned seed);
	~CDecryptStreamDecorator();

protected:
	uint8_t DecorateByte(uint8_t byte) override;
	void DecorateBlock(const void * srcData, std::streamsize size, std::vector<uint8_t>& buffer) override;
private:
	uint8_t m_unShuffleTable[256];
};

