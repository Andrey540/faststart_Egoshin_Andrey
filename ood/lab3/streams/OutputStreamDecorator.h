#pragma once
#include "IOutputStream.h"
class COutputStreamDecorator : public IOutputStream
{
public:
	COutputStreamDecorator(IOutputStreamPtr && outputStreame);
	~COutputStreamDecorator() = default;

	virtual void WriteByte(uint8_t byte) override;
	virtual void WriteBlock(const void * srcData, std::streamsize size) override;

protected:
	virtual uint8_t DecorateByte(uint8_t byte) = 0;
	virtual void DecorateBlock(const void * srcData, std::streamsize size, std::vector<uint8_t>& buffer) = 0;
private:
	IOutputStreamPtr m_outputStream;
};

