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
	struct Serializer<long long>
	{
		void Serialize(BlueprintWriter& writer, long long value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, long long& value)
		{
			value = reader.ReadInteger();
		}

		void Serialize(BufferWriter& writer, long long value)
		{
			auto normalized = static_cast<std::int64_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, long long& value)
		{
			std::int64_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<long long>(normalized);
		}
	};
}
