#include "FileInputStream.h"

CFileInputStream::CFileInputStream()
{}

CFileInputStream::~CFileInputStream()
{}

bool CFileInputStream::IsEOF() const
{
	return true;
}

BYTE CFileInputStream::ReadByte()
{
	return 2;
}

void CFileInputStream::ReadBlock(std::vector<BYTE>& dstData, size_t dataSize)
{
}
