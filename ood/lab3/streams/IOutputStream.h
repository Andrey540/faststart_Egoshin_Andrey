#pragma once
#include <vector>
#include <memory>
typedef unsigned char BYTE;

class IOutputStream
{
public:
	virtual ~IOutputStream() = default;
	virtual void WriteByte(BYTE byte) = 0;
	virtual void WriteBlock(const std::vector<BYTE>& srcData, size_t dataSize) = 0;
};

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;

