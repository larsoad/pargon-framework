#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

#include <string>

namespace Pargon
{
	template<>
	struct Serializer<std::string>
	{
		void Serialize(BlueprintWriter& writer, const std::string& value)
		{
			writer.WriteString(value);
		}

		void Serialize(BlueprintReader& reader, std::string& value)
		{
			value = reader.ReadString();
		}

		void Serialize(BufferWriter& writer, const std::string& value)
		{
			auto length = static_cast<std::uint64_t>(value.size());
			auto data = reinterpret_cast<const std::uint8_t*>(value.c_str());

			writer.WritePrimitive(length);
			writer.WriteBytes({ data, static_cast<int>(length) });
		}

		void Serialize(BufferReader& reader, std::string& value)
		{
			std::uint64_t length;
			reader.ReadPrimitive(length);

			auto data = reader.ReadBytes(length);

			value.assign(reinterpret_cast<const char*>(data.begin()), length);
		}
	};
}
