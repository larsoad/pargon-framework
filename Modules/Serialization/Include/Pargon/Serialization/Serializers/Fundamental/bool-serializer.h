#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

namespace Pargon
{
	template<>
	struct Serializer<bool>
	{
		void Serialize(BlueprintWriter& writer, bool value)
		{
			writer.WriteBoolean(value);
		}

		void Serialize(BlueprintReader& reader, bool& value)
		{
			value = reader.ReadBoolean();
		}

		void Serialize(BufferWriter& writer, bool value)
		{
			writer.WriteByte(static_cast<uint8_t>(value));
		}

		void Serialize(BufferReader& reader, bool& value)
		{
			value = reader.ReadByte() != 0;
		}
	};
}
