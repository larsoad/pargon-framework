#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

namespace Pargon
{
	template<>
	struct Serializer<char>
	{
		void Serialize(BlueprintWriter& writer, char value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, char& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<char>(i);
		}

		void Serialize(BufferWriter& writer, char value)
		{
			writer.WriteByte(value);
		}

		void Serialize(BufferReader& reader, char& value)
		{
			value = reader.ReadByte();
		}
	};
}
