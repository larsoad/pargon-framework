#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <algorithm>

using namespace Pargon;

void BufferWriter::WriteByte(std::uint8_t byte)
{
	_data.Append(byte);
}

void BufferWriter::WriteBytes(BufferView bytes)
{
	_data.Append(bytes);
}

void BufferWriter::AlignBytes(size_t alignment, std::uint8_t fill)
{
	auto padding = _data.Size() % alignment;
	while (padding < alignment)
	{
		_data.Append(fill);
		padding++;
	}
}

namespace
{
	auto GetBit(int index, bool bit) -> unsigned char
	{
		return bit ? 1 << index : 0;
	}
}

void BufferWriter::WriteBit(bool bit)
{
	if (_bitIndex == 7)
		WriteByte(0);

	auto index = _data.Size() - 1;
	auto byteValue = _data.Byte(index);
	auto bitValue = GetBit(_bitIndex, bit);

	_data.SetByte(_data.Size() - 1, byteValue | bitValue);

	if (_bitIndex == 0)
		_bitIndex = 7;
	else
		_bitIndex--;
}

void BufferWriter::AlignBits(bool fill)
{
	while (_bitIndex != 7)
		WriteBit(fill);
}
