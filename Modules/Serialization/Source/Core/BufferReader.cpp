#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <algorithm>

using namespace Pargon;

BufferReader::BufferReader(BufferView view, Pargon::Endian endian) :
	_data(view),
	_endian(endian)
{
}

auto BufferReader::Advance(int count) -> bool
{
	return MoveTo(_index + count);
}

auto BufferReader::Retreat(int count) -> bool
{
	return MoveTo(_index - count);
}

auto BufferReader::MoveTo(int index) -> bool
{
	_bitIndex = 0;
	_index = index;
	return true;
}

auto BufferReader::ViewByte() -> std::uint8_t
{
	return _data.Byte(_index);
}

auto BufferReader::ViewBytes(int count) -> BufferView
{
	return _data.GetSubview(_index, count);
}

auto BufferReader::ViewBit() -> bool
{
	auto byte = _data.Byte(_index);
	auto mask = 1 << _bitIndex;

	return (byte & mask) != 0;
}

auto BufferReader::ReadByte() -> std::uint8_t
{
	return _data.Byte(_index++);
}

auto BufferReader::ReadBytes(int count) -> BufferView
{
	_index += count;
	return _data.GetSubview(_index - count, count);
}

void BufferReader::AlignBytes(size_t alignment)
{
	auto offset = _index % alignment;
	_index += alignment - offset;
}

auto BufferReader::ReadBit() -> bool
{
	auto bit = ViewBit();

	_bitIndex++;

	if (_bitIndex > 7)
	{
		_bitIndex = 0;
		_index++;
	}

	return bit;
}

void BufferReader::AlignBits()
{
	if (_bitIndex > 0)
	{
		_bitIndex = 0;
		_index++;
	}
}
