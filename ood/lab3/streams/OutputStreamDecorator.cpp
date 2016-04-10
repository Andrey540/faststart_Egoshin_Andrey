#include "OutputStreamDecorator.h"

COutputStreamDecorator::COutputStreamDecorator(IOutputStreamPtr && outputStreame)
	: m_outputStream(move(outputStreame))
{}

COutputStreamDecorator::~COutputStreamDecorator()
{}

void COutputStreamDecorator::WriteByte(uint8_t byte)
{
	m_outputStream->WriteByte(DecorateByte(byte));
}

void COutputStreamDecorator::WriteBlock(const void * srcData, std::streamsize size)
{
	std::vector<uint8_t> buffer = DecorateBlock(srcData, size);
	m_outputStream->WriteBlock(&buffer, buffer.size());
}
