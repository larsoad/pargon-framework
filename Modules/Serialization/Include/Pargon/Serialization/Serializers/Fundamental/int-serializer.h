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
	struct Serializer<int>
	{
		void Serialize(BlueprintWriter& writer, int value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, int& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<int>(i);
		}

		void Serialize(BufferWriter& writer, int value)
		{
			auto normalized = static_cast<std::int32_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, int& value)
		{
			std::int32_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<int>(normalized);
		}
	};
}
