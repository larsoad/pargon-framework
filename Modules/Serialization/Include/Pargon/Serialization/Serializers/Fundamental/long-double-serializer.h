#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

namespace Pargon
{
	template<>
	struct Serializer<long double>
	{
		void Serialize(BlueprintWriter& writer, long double value)
		{
			writer.WriteFloatingPoint(value);
		}

		void Serialize(BlueprintReader& reader, long double& value)
		{
			auto d = reader.ReadFloatingPoint();
			value = static_cast<long double>(d);
		}

		void Serialize(BufferWriter& writer, long double value)
		{
			auto normalized = static_cast<double>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, long double& value)
		{
			double normalized;
			reader.ReadPrimitive(normalized);
			value = normalized;
		}
	};
}
