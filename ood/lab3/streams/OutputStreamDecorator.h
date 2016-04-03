#pragma once
#include "IOutputStream.h"
class COutputStreamDecorator :
	public IOutputStream
{
public:
	COutputStreamDecorator(IOutputStreamPtr && outputStreame);
	~COutputStreamDecorator();

	void WriteByte(BYTE byte) override;
	void WriteBlock(const std::vector<BYTE>& srcData, size_t dataSize) override;

	virtual BYTE DecoratorByte(BYTE byte) = 0;
	virtual const std::vector<BYTE>& DecoratorBlock(const std::vector<BYTE>& srcData, size_t dataSize) = 0;
private:
	IOutputStreamPtr m_outputStream;
};

