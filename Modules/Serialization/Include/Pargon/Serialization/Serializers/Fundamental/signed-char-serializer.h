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
	struct Serializer<signed char>
	{
		void Serialize(BlueprintWriter& writer, signed char value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, signed char& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<signed char>(i);
		}

		void Serialize(BufferWriter& writer, signed char value)
		{
			writer.WriteByte(value);
		}

		void Serialize(BufferReader& reader, signed char& value)
		{
			value = reader.ReadByte();
		}
	};
}
