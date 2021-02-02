#pragma once

#include "Pargon/Serialization/Buffer.h"
#include "Pargon/Serialization/Serializer.h"

#include <algorithm>
#include <bitset>
#include <utility>

namespace Pargon
{
	class BufferReader
	{
		BufferView _data;
		Pargon::Endian _endian;
		int _index = 0;
		int _bitIndex = 0;

	public:
		BufferReader(BufferView view, Pargon::Endian endian);

		auto Endian() const -> Endian;
		auto Index() const -> int;
		auto Remaining() const -> int;

		auto Advance(int count) -> bool;
		auto Retreat(int count) -> bool;
		auto MoveTo(int index) -> bool;

		auto ViewByte() -> std::uint8_t;
		auto ViewBytes(int count) -> BufferView;
		auto ViewBit() -> bool;
		template<size_t N> void ViewBits(std::bitset<N>& bits);

		template<typename T> void Read(T& item);
		template<typename T> void ReadPrimitive(T& value);

		auto ReadByte() -> std::uint8_t;
		auto ReadBytes(int count) -> BufferView;
		void AlignBytes(size_t alignment);

		auto ReadBit() -> bool;
		template<size_t N> void ReadBits(std::bitset<N>& bits);
		void AlignBits();

	private:
		friend class GenericSerializer;
		friend class BufferSerializer;

		template<typename T> void Serialize(T& item);
		template<typename T> void SerializePrimitive(T& value);
		void SerializeByte(std::uint8_t& byte);
		void SerializeBytes(BufferReference bytes);
		void AlignBytes(size_t alignment, std::uint8_t fill);
		void SerializeBit(bool& bit);
		template<size_t N> void SerializeBits(std::bitset<N>& bits);
		void AlignBits(bool fill);
	};
}

inline
auto Pargon::BufferReader::Endian() const -> Pargon::Endian
{
	return _endian;
}

inline
auto Pargon::BufferReader::Index() const -> int
{
	return _index;
}

inline
auto Pargon::BufferReader::Remaining() const -> int
{
	return _data.Size() - _index;
}

template<typename T>
void Pargon::BufferReader::Read(T& value)
{
	Pargon::Serializer<T>().Serialize(*this, value);
}

template<typename T>
void Pargon::BufferReader::ReadPrimitive(T& value)
{
	auto data = _data.GetSubview(_index, sizeof(T));
	auto buffer = BufferReference(value);

	if (_endian != NativeEndian)
		std::reverse_copy(data.begin(), data.end(), buffer.begin());
	else
		std::copy(data.begin(), data.end(), buffer.begin());
}

template<size_t N>
void Pargon::BufferReader::ViewBits(std::bitset<N>& bits)
{
	auto index = _index;
	auto bitIndex = _bitIndex;

	for (auto i = 0; i < N; i++)
	{
		bool bit;
		ReadBit(bit);
		bits.set(i, bit);
	}

	_index = index;
	_bitIndex = bitIndex;
}

template<size_t N>
void Pargon::BufferReader::ReadBits(std::bitset<N>& bits)
{
	for (auto i = 0; i < N; i++)
	{
		bool bit;
		ReadBit(bit);
		bits.set(i, bit);
	}
}

template<typename T>
void Pargon::BufferReader::Serialize(T& value)
{
	Pargon::Serializer<T>::Serialize(*this, value);
}

template<typename T>
void Pargon::BufferReader::SerializePrimitive(T& value)
{
	ReadPrimitive(value);
}

inline
void Pargon::BufferReader::SerializeByte(std::uint8_t& byte)
{
	byte = ReadByte();
}

inline
void Pargon::BufferReader::SerializeBytes(BufferReference bytes)
{
	auto data = ReadBytes(bytes.Size());
	std::copy(data.begin(), data.end(), bytes.begin());
}

inline
void Pargon::BufferReader::AlignBytes(size_t alignment, std::uint8_t fill)
{
	AlignBytes(alignment);
}

inline
void Pargon::BufferReader::SerializeBit(bool& bit)
{
	bit = ReadBit();
}

template<size_t N>
void Pargon::BufferReader::SerializeBits(std::bitset<N>& bits)
{
	ReadBits(bits);
}

inline
void Pargon::BufferReader::AlignBits(bool fill)
{
	AlignBits();
}
