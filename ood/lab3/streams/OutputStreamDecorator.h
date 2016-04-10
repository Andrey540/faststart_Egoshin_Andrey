#pragma once
#include "IOutputStream.h"
class COutputStreamDecorator :
	public IOutputStream
{
public:
	COutputStreamDecorator(IOutputStreamPtr && outputStreame);
	~COutputStreamDecorator();

	void WriteByte(uint8_t byte) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

	virtual uint8_t DecorateByte(uint8_t byte) = 0;
	virtual const std::vector<uint8_t>& DecorateBlock(const void * srcData, std::streamsize size) = 0;
private:
	IOutputStreamPtr m_outputStream;
};

