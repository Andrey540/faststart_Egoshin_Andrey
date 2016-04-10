#pragma once
#include "IOutputStream.h"
class CMemoryOutputStream :
	public IOutputStream
{
public:
	CMemoryOutputStream();
	~CMemoryOutputStream();

	void WriteByte(uint8_t byte) override;
	void WriteBlock(const void * srcData, std::streamsize size) override;

private:
	std::vector<uint8_t> m_buffer;
};

