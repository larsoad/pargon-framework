#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Types/Guid.h"

#include <algorithm>

using namespace Pargon;

Guid::Guid(const Array<uint8_t, 16>& bytes)
{
	SetBytes(bytes);
}

auto Guid::operator==(Guid other) const -> bool
{
	return std::equal(_bytes.begin(), _bytes.end(), other._bytes.begin());
}

auto Guid::operator!=(Guid other) const -> bool
{
	return !operator==(other);
}

void Guid::SetBytes(const Array<uint8_t, 16>& bytes)
{
	_bytes = bytes;
}

auto Guid::GetHash() const -> unsigned int
{
	auto first = *reinterpret_cast<const unsigned int*>(_bytes.begin());
	auto second = *reinterpret_cast<const unsigned int*>(_bytes.begin() + 4);
	auto third = *reinterpret_cast<const unsigned int*>(_bytes.begin() + 8);
	auto fourth = *reinterpret_cast<const unsigned int*>(_bytes.begin() + 12);

	return first ^ second ^ third ^ fourth;
}

void Guid::ToBuffer(BufferWriter& writer) const
{
	writer.Write(_bytes);
}

void Guid::FromBuffer(BufferReader& reader)
{
	reader.Read(_bytes);
}

void Guid::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(_bytes.Item(0), "#");
	writer.Write(_bytes.Item(1), "#");
	writer.Write(_bytes.Item(2), "#");
	writer.Write(_bytes.Item(3), "#");
	writer.Write("-"_sv, {});
	writer.Write(_bytes.Item(4), "#");
	writer.Write(_bytes.Item(5), "#");
	writer.Write("-"_sv, {});
	writer.Write(_bytes.Item(6), "#");
	writer.Write(_bytes.Item(7), "#");
	writer.Write("-"_sv, {});
	writer.Write(_bytes.Item(8), "#");
	writer.Write(_bytes.Item(9), "#");
	writer.Write("-"_sv, {});
	writer.Write(_bytes.Item(10), "#");
	writer.Write(_bytes.Item(11), "#");
	writer.Write(_bytes.Item(12), "#");
	writer.Write(_bytes.Item(13), "#");
	writer.Write(_bytes.Item(14), "#");
	writer.Write(_bytes.Item(15), "#");
}

void Guid::FromString(StringReader& reader, StringView format)
{
	reader.Read(_bytes.Item(0), "#");
	reader.Read(_bytes.Item(1), "#");
	reader.Read(_bytes.Item(2), "#");
	reader.Read(_bytes.Item(3), "#");
	reader.Advance(1);
	reader.Read(_bytes.Item(4), "#");
	reader.Read(_bytes.Item(5), "#");
	reader.Advance(1);
	reader.Read(_bytes.Item(6), "#");
	reader.Read(_bytes.Item(7), "#");
	reader.Advance(1);
	reader.Read(_bytes.Item(8), "#");
	reader.Read(_bytes.Item(9), "#");
	reader.Advance(1);
	reader.Read(_bytes.Item(10), "#");
	reader.Read(_bytes.Item(11), "#");
	reader.Read(_bytes.Item(12), "#");
	reader.Read(_bytes.Item(13), "#");
	reader.Read(_bytes.Item(14), "#");
	reader.Read(_bytes.Item(15), "#");
}
