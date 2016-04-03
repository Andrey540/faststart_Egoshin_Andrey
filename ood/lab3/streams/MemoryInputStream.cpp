#include "MemoryInputStream.h"

CMemoryInputStream::CMemoryInputStream()
{}

CMemoryInputStream::~CMemoryInputStream()
{}

bool CMemoryInputStream::IsEOF() const
{
	return true;
}

BYTE CMemoryInputStream::ReadByte()
{
	return 2;
}

void CMemoryInputStream::ReadBlock(std::vector<BYTE>& dstData, size_t dataSize)
{
}
