#pragma once

#include "Pargon/Containers/Array.h"

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class StringReader;
	class StringWriter;
	class StringView;

	class Guid
	{
	public:
		Guid() = default;
		explicit Guid(const Array<uint8_t, 16>& bytes);

		auto operator==(Guid other) const -> bool;
		auto operator!=(Guid other) const -> bool;

		auto Bytes() const -> const Array<unsigned char, 16>&;
		void SetBytes(const Array<unsigned char, 16>& bytes);

		auto GetHash() const -> unsigned int;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);

	private:
		Array<uint8_t, 16> _bytes = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
	};

	auto GenerateGuid() -> Guid;
}

inline
auto Pargon::Guid::Bytes() const -> const Array<uint8_t, 16>&
{
	return _bytes;
}
