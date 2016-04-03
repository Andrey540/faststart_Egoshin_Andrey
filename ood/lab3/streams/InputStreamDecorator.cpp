#include "InputStreamDecorator.h"

CInputStreamDecorator::CInputStreamDecorator(IInputStreamPtr && inputStreame)
	: m_inputStream(move(inputStreame))
{}

CInputStreamDecorator::~CInputStreamDecorator()
{}

bool CInputStreamDecorator::IsEOF() const
{
	return m_inputStream->IsEOF();
}

BYTE CInputStreamDecorator::ReadByte()
{
	return DecorateByte(m_inputStream->ReadByte());
}

void CInputStreamDecorator::ReadBlock(std::vector<BYTE>& dstData, size_t dataSize)
{
	m_inputStream->ReadBlock(dstData, dataSize);
	DecorateBlock(dstData);
}
