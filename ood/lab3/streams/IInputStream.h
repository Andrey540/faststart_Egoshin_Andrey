#pragma once
#include <vector>
#include <memory>
typedef unsigned char BYTE;

class IInputStream
{
public:
	virtual ~IInputStream() = default;
	virtual bool IsEOF() const = 0;
	virtual BYTE ReadByte() = 0;
	virtual void ReadBlock(std::vector<BYTE>& dstData, size_t dataSize) = 0;
};

typedef std::unique_ptr<IInputStream> IInputStreamPtr;

