#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

namespace Pargon
{
	template<>
	struct Serializer<char32_t>
	{
		void Serialize(BlueprintWriter& writer, char32_t value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, char32_t& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<char32_t>(i);
		}

		void Serialize(BufferWriter& writer, char32_t value)
		{
			writer.WritePrimitive(value);
		}

		void Serialize(BufferReader& reader, char32_t& value)
		{
			reader.ReadPrimitive(value);
		}
	};
}
