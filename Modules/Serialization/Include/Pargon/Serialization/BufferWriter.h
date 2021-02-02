#pragma once

#include "Pargon/Serialization/Buffer.h"
#include "Pargon/Serialization/Serializer.h"

#include <algorithm>
#include <bitset>
#include <string_view>
#include <type_traits>
#include <utility>

namespace Pargon
{
	class BufferWriter
	{
		Buffer _data;
		Pargon::Endian _endian;
		int _bitIndex = 7;

	public:
		explicit BufferWriter(Pargon::Endian endian);
		
		auto Endian() const -> Endian;
		auto Size() const -> int;

		auto ViewBuffer() const -> BufferView;
		auto TakeBuffer() -> Buffer;

		template<typename T> void Write(const T& item);
		template<typename T> void WritePrimitive(T value);

		void WriteByte(std::uint8_t byte);
		void WriteBytes(BufferView bytes);
		void AlignBytes(size_t alignment, std::uint8_t fill);

		void WriteBit(bool bit);
		template<size_t N> void WriteBits(std::bitset<N> bits);
		void AlignBits(bool fill);

	private:
		friend class GenericSerializer;
		friend class BufferSerializer;

		template<typename T> void Serialize(const T& item);
		template<typename T> void SerializePrimitive(T value);
		void SerializeByte(std::uint8_t byte);
		void SerializeBytes(BufferReference bytes);
		void SerializeBit(bool bit);
		template<size_t N> void SerializeBits(std::bitset<N> bits);
	};
}

inline
Pargon::BufferWriter::BufferWriter(Pargon::Endian endian) :
	_endian(endian)
{
}

inline
auto Pargon::BufferWriter::Endian() const -> Pargon::Endian
{
	return _endian;
}

inline
auto Pargon::BufferWriter::Size() const -> int
{
	return _data.Size();
}

inline
auto Pargon::BufferWriter::ViewBuffer() const -> BufferView
{
	return { _data };
}

inline
auto Pargon::BufferWriter::TakeBuffer() -> Buffer
{
	return std::move(_data);
}

template<typename T>
void Pargon::BufferWriter::Write(const T& t)
{
	Pargon::Serializer<T>::Serialize(*this, t);
}

template<typename T>
void Pargon::BufferWriter::WritePrimitive(T t)
{
	auto data = BufferView(t);
	auto buffer = _data.Reserve(sizeof(T));

	if (_endian != NativeEndian)
		std::reverse_copy(data.begin(), data.end(), buffer.begin());
	else
		std::copy(data.begin(), data.end(), buffer.begin());
}

template<size_t N>
void Pargon::BufferWriter::WriteBits(std::bitset<N> bits)
{
	for (auto i = 0; i < N; i++)
		WriteBit(bits.test(i));
}

template<typename T>
void Pargon::BufferWriter::Serialize(const T& value)
{
	Pargon::Serializer<T>::Serialize(*this, value);
}

template<typename T>
void Pargon::BufferWriter::SerializePrimitive(T t)
{
	WritePrimitive(t);
}

inline
void Pargon::BufferWriter::SerializeByte(std::uint8_t byte)
{
	WriteByte(byte);
}

inline
void Pargon::BufferWriter::SerializeBytes(BufferReference bytes)
{
	WriteBytes(bytes);
}

inline
void Pargon::BufferWriter::SerializeBit(bool bit)
{
	WriteBit(bit);
}

template<size_t N>
void Pargon::BufferWriter::SerializeBits(std::bitset<N> bits)
{
	WriteBits(bits);
}
