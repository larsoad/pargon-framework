#pragma once

#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <functional>
#include <string_view>
#include <utility>
#include <variant>

namespace Pargon
{
	class GenericSerializer
	{
	public:
		GenericSerializer(BufferReader& reader);
		GenericSerializer(BufferWriter& writer);
		GenericSerializer(BlueprintReader& reader);
		GenericSerializer(BlueprintWriter& writer);

		template<typename T> void Serialize(T&& value);

	private:
		using Variant = std::variant<
			std::reference_wrapper<BufferReader>,
			std::reference_wrapper<BufferWriter>,
			std::reference_wrapper<BlueprintReader>,
			std::reference_wrapper<BlueprintWriter>
		>;

		Variant _serializer;
	};
}

inline
Pargon::GenericSerializer::GenericSerializer(BufferReader& reader) :
	_serializer(reader)
{
}

inline
Pargon::GenericSerializer::GenericSerializer(BufferWriter& writer) :
	_serializer(writer)
{
}

inline
Pargon::GenericSerializer::GenericSerializer(BlueprintReader& reader) :
	_serializer(reader)
{
}

inline
Pargon::GenericSerializer::GenericSerializer(BlueprintWriter& writer) :
	_serializer(writer)
{
}

template<typename T>
void Pargon::GenericSerializer::Serialize(T&& value)
{
	std::visit([&](auto&& variant)
	{
		variant.get().Serialize(std::forward<T>(value));
	}, _serializer);
}
