#pragma once

#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <functional>
#include <string_view>
#include <utility>
#include <variant>

namespace Pargon
{
	class BufferSerializer
	{
		using Variant = std::variant<
			std::reference_wrapper<BufferReader>,
			std::reference_wrapper<BufferWriter>
		>;

		Variant _serializer;

	public:
		BufferSerializer(BufferReader& reader);
		BufferSerializer(BufferWriter& writer);

		template<typename T> void Serialize(T& value);
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
Pargon::BufferSerializer::BufferSerializer(BufferReader& reader) :
	_serializer(reader)
{
}

inline
Pargon::BufferSerializer::BufferSerializer(BufferWriter& writer) :
	_serializer(writer)
{
}

template<typename T>
void Pargon::BufferSerializer::Serialize(T& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(value);
	}, _serializer);
}

template<typename T>
void Pargon::BufferSerializer::SerializePrimitive(T& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializePrimitive(value);
	}, _serializer);
}

inline
void Pargon::BufferSerializer::SerializeByte(std::uint8_t& byte)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializeByte(byte);
	}, _serializer);
}

inline
void Pargon::BufferSerializer::SerializeBytes(BufferReference bytes)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializeBytes(bytes);
	}, _serializer);
}

inline
void Pargon::BufferSerializer::SerializeBit(bool& bit)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializeBit(bit);
	}, _serializer);
}

template<size_t N>
void Pargon::BufferSerializer::SerializeBits(std::bitset<N>& bits)
{
	std::visit([&](auto&& variant)
	{
		variant.get().SerializeBits(bits);
	}, _serializer);
}

inline
void Pargon::BufferSerializer::AlignBytes(size_t alignment, std::uint8_t fill)
{
	std::visit([&](auto&& variant)
	{
		variant.get().AlignBytes(alignment, fill);
	}, _serializer);
}

inline
void Pargon::BufferSerializer::AlignBits(bool fill)
{
	std::visit([&](auto&& variant)
	{
		variant.get().AlignBits(fill);
	}, _serializer);
}
