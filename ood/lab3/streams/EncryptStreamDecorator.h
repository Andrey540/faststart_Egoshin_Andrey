#pragma once
#include "InputStreamDecorator.h"
class CEncryptStreamDecorator : public CInputStreamDecorator
{
public:
	CEncryptStreamDecorator(IInputStreamPtr && inputStream, unsigned seed);
	~CEncryptStreamDecorator();

protected:
	uint8_t DecorateByte(uint8_t byte) override;
	std::streamsize DecorateBlock(void * dstBuffer, std::vector<uint8_t>& readBuffer) override;
private:
	uint8_t m_shuffleTable[256];
};

