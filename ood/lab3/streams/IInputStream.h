#pragma once
#include <vector>
#include <memory>

class IInputStream
{
public:
	virtual ~IInputStream() = default;
	virtual bool IsEOF() const = 0;
	virtual uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void * dstBuffer, std::streamsize size) = 0;
};

typedef std::unique_ptr<IInputStream> IInputStreamPtr;

