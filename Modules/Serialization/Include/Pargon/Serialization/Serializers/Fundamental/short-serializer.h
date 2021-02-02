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
	struct Serializer<short>
	{
		void Serialize(BlueprintWriter& writer, short value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, short& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<short>(i);
		}

		void Serialize(BufferWriter& writer, short value)
		{
			auto normalized = static_cast<std::int16_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, short& value)
		{
			std::int16_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<short>(normalized);
		}
	};
}
