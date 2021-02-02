#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <cstdint>

namespace Pargon
{
	template<>
	struct Serializer<unsigned int>
	{
		void Serialize(BlueprintWriter& writer, unsigned int value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, unsigned int& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<unsigned int>(i);
		}

		void Serialize(BufferWriter& writer, unsigned int value)
		{
			auto normalized = static_cast<std::uint32_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, unsigned int& value)
		{
			std::uint32_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<unsigned int>(normalized);
		}
	};
}
