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
	struct Serializer<double>
	{
		static_assert(std::numeric_limits<double>::is_iec559, "double is not IEE 754");
		static_assert(sizeof(double) == 8, "double size is not 8 bytes.");

		void Serialize(BlueprintWriter& writer, double value)
		{
			writer.WriteFloatingPoint(value);
		}

		void Serialize(BlueprintReader& reader, double& value)
		{
			value = reader.ReadFloatingPoint();
		}

		void Serialize(BufferWriter& writer, double value)
		{
			writer.WritePrimitive(value);
		}

		void Serialize(BufferReader& reader, double& value)
		{
			reader.ReadPrimitive(value);
		}
	};
}
