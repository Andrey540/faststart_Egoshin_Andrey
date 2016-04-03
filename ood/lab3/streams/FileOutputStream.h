#pragma once
#include "IOutputStream.h"
class CFileOutputStream :
	public IOutputStream
{
public:
	CFileOutputStream();
	~CFileOutputStream();

	void WriteByte(BYTE byte) override;
	void WriteBlock(const std::vector<BYTE>& srcData, size_t dataSize) override;
};

