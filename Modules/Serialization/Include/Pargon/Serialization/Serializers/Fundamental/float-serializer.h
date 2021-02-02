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
	struct Serializer<float>
	{
		static_assert(std::numeric_limits<float>::is_iec559, "float is not IEE 754"); // TODO: Not sure if this guarantees exact format (i.e mantissa and base).
		static_assert(sizeof(float) == 4, "float size is not 4 bytes");

		void Serialize(BlueprintWriter& writer, float value)
		{
			writer.WriteFloatingPoint(value);
		}

		void Serialize(BlueprintReader& reader, float& value)
		{
			auto d = reader.ReadFloatingPoint();
			value = static_cast<float>(d);
		}

		void Serialize(BufferWriter& writer, float value)
		{
			writer.WritePrimitive(value);
		}

		void Serialize(BufferReader& reader, float& value)
		{
			reader.ReadPrimitive(value);
		}
	};
}
