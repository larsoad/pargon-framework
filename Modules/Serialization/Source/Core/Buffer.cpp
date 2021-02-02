#include "Pargon/Serialization/Buffer.h"

#include <algorithm>
#include <cassert>
#include <utility>

using namespace Pargon;

namespace
{
	class EndianDetector
	{
	private:
		static constexpr uint32_t _test = 0x01020304;
		static constexpr uint8_t _byte = (const uint8_t&)_test;

	public:
		static constexpr bool Little = _byte == 0x04;
		static constexpr bool Big = _byte == 0x01;

		static_assert(Little || Big, "cannot detect endianness");
	};
}

const Endian Pargon::NativeEndian = EndianDetector::Little ? Endian::Little : Endian::Big;

Buffer::Buffer(std::unique_ptr<uint8_t[]>&& bytes, int size) :
	_data(std::move(bytes)),
	_used(size),
	_available(size)
{
}

Buffer::Buffer(BufferView view)
{
	SetSize(view.Size());
	std::copy(view.begin(), view.end(), _data.get());
}

auto Buffer::operator=(BufferView view) -> Buffer&
{
	SetSize(view.Size());
	std::copy(view.begin(), view.end(), _data.get());
	return *this;
}

auto Buffer::Byte(int index) const -> uint8_t
{
	assert(index >= 0 && index < _used);
	return _data[index];
}

void Buffer::SetByte(int index, uint8_t value)
{
	assert(index >= 0 && index < _used);
	_data[index] = value;
}

void Buffer::SetBytes(int index, BufferView bytes)
{
	assert(index >= 0 && index + bytes.Size() <= _used);
	std::copy(bytes.begin(), bytes.end(), _data.get() + index);
}

void Buffer::SetSize(int size)
{
	if (size > _available)
	{
		auto newSize = _used + _used / 2;
		if (size > newSize)
			newSize = size;

		auto buffer = std::make_unique<uint8_t[]>(newSize);
		std::copy(_data.get(), _data.get() + _used, buffer.get());
		_data = std::move(buffer);
		_available = newSize;
	}

	_used = size;
}

void Buffer::Append(uint8_t value)
{
	auto start = _used;
	SetSize(_used + 1);
	_data[start] = value;
}

void Buffer::Append(BufferView view)
{
	auto start = _used;
	SetSize(_used + view.Size());
	std::copy(view.begin(), view.end(), _data.get() + start);
}

auto Buffer::Reserve(int size) -> BufferReference
{
	auto start = _used;
	SetSize(_used + size);
	return { _data.get() + start, size };
}

void Buffer::Erase(uint8_t value)
{
	std::fill(_data.get(), _data.get() + _used, value);
}

void Buffer::Clear()
{
	_used = 0;
	_available = 0;
	_data.reset();
}

auto Buffer::GetView() const -> BufferView
{
	return GetView(0, _used);
}

auto Buffer::GetView(int index) const -> BufferView
{
	return GetView(index, _used - index);
}

auto Buffer::GetView(int index, int count) const -> BufferView
{
	if (index < 0 || index + count > _used)
		return {};

	return { _data.get() + index, count };
}

auto Buffer::GetReference() -> BufferReference
{
	return GetReference(0, _used);
}

auto Buffer::GetReference(int index) -> BufferReference
{
	return GetReference(index, _used - index);
}

auto Buffer::GetReference(int index, int count) -> BufferReference
{
	if (index < 0 || index + count > _used)
		return {};

	return { _data.get() + index, count };
}

auto BufferView::Byte(int index) const -> uint8_t
{
	assert(index >= 0 && index < _size);
	return _data[index];
}

auto BufferView::GetSubview(int index) const -> BufferView
{
	return GetSubview(index, _size - index);
}

auto BufferView::GetSubview(int index, int count) const -> BufferView
{
	if (index < 0 || index + count > _size)
		return {};

	return { _data + index, count };
}

auto BufferView::GetBuffer() const -> Buffer
{
	return Buffer(*this);
}

auto Pargon::operator==(BufferView left, BufferView right) -> bool
{
	if (left.Size() != right.Size())
		return false;

	return std::equal(left.begin(), left.end(), right.begin());
}

auto Pargon::operator!=(BufferView left, BufferView right) -> bool
{
	return !operator==(left, right);
}

auto BufferReference::Byte(int index) const -> uint8_t
{
	assert(index >= 0 && index < _size);
	return _data[index];
}

void BufferReference::SetByte(int index, uint8_t value)
{
	assert(index >= 0 && index < _size);
	_data[index] = value;
}

void BufferReference::SetBytes(int index, BufferView bytes)
{
	assert(index >= 0 && index + bytes.Size() <= _size);
	std::copy(bytes.begin(), bytes.end(), _data + index);
}

void BufferReference::Erase(uint8_t value)
{
	std::fill(_data, _data + _size, value);
}

auto BufferReference::GetView() const -> BufferView
{
	return GetView(0, _size);
}

auto BufferReference::GetView(int index) const -> BufferView
{
	return GetView(index, _size - index);
}

auto BufferReference::GetView(int index, int count) const -> BufferView
{
	if (index < 0 || index + count > _size)
		return {};

	return { _data + index, count };
}

auto BufferReference::GetSubreference(int index) const -> BufferReference
{
	return GetSubreference(index, _size - index);
}

auto BufferReference::GetSubreference(int index, int count) const -> BufferReference
{
	if (index < 0 || index + count > _size)
		return {};

	return { _data + index, count };
}

auto BufferReference::GetBuffer() const -> Buffer
{
	return Buffer(*this);
}
