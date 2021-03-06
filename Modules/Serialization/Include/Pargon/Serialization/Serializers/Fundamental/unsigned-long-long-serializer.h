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
	struct Serializer<unsigned long long>
	{
		void Serialize(BlueprintWriter& writer, unsigned long long value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, unsigned long long& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<unsigned long long>(i);
		}

		void Serialize(BufferWriter& writer, unsigned long long value)
		{
			auto normalized = static_cast<std::uint64_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, unsigned long long& value)
		{
			std::uint64_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<unsigned long long>(normalized);
		}
	};
}
