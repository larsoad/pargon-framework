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
	struct Serializer<unsigned short>
	{
		void Serialize(BlueprintWriter& writer, unsigned short value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, unsigned short& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<unsigned short>(i);
		}

		void Serialize(BufferWriter& writer, unsigned short value)
		{
			auto normalized = static_cast<std::uint16_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, unsigned short& value)
		{
			std::uint16_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<unsigned short>(normalized);
		}
	};
}
