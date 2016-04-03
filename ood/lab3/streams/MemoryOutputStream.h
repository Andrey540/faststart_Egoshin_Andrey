#pragma once
#include "IOutputStream.h"
class CMemoryOutputStream :
	public IOutputStream
{
public:
	CMemoryOutputStream();
	~CMemoryOutputStream();

	void WriteByte(BYTE byte) override;
	void WriteBlock(const std::vector<BYTE>& srcData, size_t dataSize) override;
};

