#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <limits>

namespace Pargon
{
	template<>
	struct Serializer<unsigned char>
	{
		static_assert(std::numeric_limits<unsigned char>::digits == 8, "char is not 8 bits");

		void Serialize(BlueprintWriter& writer, unsigned char value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, unsigned char& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<unsigned char>(i);
		}

		void Serialize(BufferWriter& writer, unsigned char value)
		{
			writer.WriteByte(value);
		}

		void Serialize(BufferReader& reader, unsigned char& value)
		{
			value = reader.ReadByte();
		}
	};
}
