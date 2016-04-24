#pragma once
#include "IInputStream.h"
class CInputStreamDecorator : public IInputStream
{
public:
	CInputStreamDecorator(IInputStreamPtr && inputStreame);
	~CInputStreamDecorator() = default;

	virtual bool IsEOF() const override;
	virtual uint8_t ReadByte() override;
	virtual std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) override;

protected:
	virtual uint8_t DecorateByte(uint8_t byte) = 0;
	virtual std::streamsize DecorateBlock(void * dstBuffer, std::vector<uint8_t>& readBuffer) = 0;
private:
	IInputStreamPtr m_inputStream;
};

