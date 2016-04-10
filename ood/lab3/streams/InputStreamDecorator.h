#pragma once
#include "IInputStream.h"
class CInputStreamDecorator :
	public IInputStream
{
public:
	CInputStreamDecorator(IInputStreamPtr && inputStreame);
	~CInputStreamDecorator();

	bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

	virtual uint8_t DecorateByte(uint8_t byte) = 0;
	virtual void DecorateBlock(void * dstBuffer, std::streamsize size) = 0;
private:
	IInputStreamPtr m_inputStream;
};

