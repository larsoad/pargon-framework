#pragma once

#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Serialization/BlueprintReader.h"
#include "Pargon/Serialization/BlueprintWriter.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"

namespace Pargon
{
	template<>
	struct Serializer<wchar_t>
	{
		void Serialize(BlueprintWriter& writer, wchar_t value)
		{
			writer.WriteInteger(value);
		}

		void Serialize(BlueprintReader& reader, wchar_t& value)
		{
			auto i = reader.ReadInteger();
			value = static_cast<wchar_t>(i);
		}

		void Serialize(BufferWriter& writer, wchar_t value)
		{
			auto normalized = static_cast<char32_t>(value);
			writer.WritePrimitive(normalized);
		}

		void Serialize(BufferReader& reader, wchar_t& value)
		{
			char32_t normalized;
			reader.ReadPrimitive(normalized);
			value = static_cast<wchar_t>(normalized);

		}
	};
}
