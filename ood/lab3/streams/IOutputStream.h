#pragma once
#include <vector>
#include <memory>

class IOutputStream
{
public:
	virtual ~IOutputStream() = default;
	virtual void WriteByte(uint8_t byte) = 0;
	virtual void WriteBlock(const void * srcData, std::streamsize size) = 0;
};

typedef std::unique_ptr<IOutputStream> IOutputStreamPtr;

