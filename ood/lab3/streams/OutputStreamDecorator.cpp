#include "OutputStreamDecorator.h"

COutputStreamDecorator::COutputStreamDecorator(IOutputStreamPtr && outputStreame)
	: m_outputStream(move(outputStreame))
{}

COutputStreamDecorator::~COutputStreamDecorator()
{}

void COutputStreamDecorator::WriteByte(BYTE byte)
{
	m_outputStream->WriteByte(DecoratorByte(byte));
}

void COutputStreamDecorator::WriteBlock(const std::vector<BYTE>& srcData, size_t dataSize)
{
	std::vector<BYTE> buffer = DecoratorBlock(srcData, dataSize);
	m_outputStream->WriteBlock(buffer, buffer.size());
}
