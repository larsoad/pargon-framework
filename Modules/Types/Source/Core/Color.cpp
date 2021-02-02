#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Types/Color.h"

using namespace Pargon;

void Color::ToBuffer(BufferWriter& writer) const
{
	writer.Write(R);
	writer.Write(G);
	writer.Write(B);
	writer.Write(A);
}

void Color::FromBuffer(BufferReader& reader)
{
	reader.Read(R);
	reader.Read(G);
	reader.Read(B);
	reader.Read(A);
}

namespace
{
	auto WriteColor(const Color& value, StringWriter& writer, StringView name, Color set) -> bool
	{
		if (value != set)
			return false;

		writer.Write(name, {});
		return true;
	}

	auto ReadColor(Color& value, StringReader& reader, StringView name, Color set)
	{
		if (StartsWith(reader.ViewRemaining(), name, true))
		{
			value = set;
			reader.Advance(name.Length());
			return true;
		}

		return false;
	}
}

void Color::ToString(StringWriter& writer, StringView format) const
{
	// formats
	// "#" -> "#RRGGBBAA"
	// "," -> "R, G, B, A"
	// "*" -> name, fallback to # (default)

	auto style = format.IsEmpty() ? '*' : format.Character(0);

	if (style == '*')
	{
		if (WriteColor(*this, writer, "White", White)
			|| WriteColor(*this, writer, "Black", Black)
			|| WriteColor(*this, writer, "Red", Red)
			|| WriteColor(*this, writer, "Green", Green)
			|| WriteColor(*this, writer, "Blue", Blue)
			|| WriteColor(*this, writer, "Yellow", Yellow)
			|| WriteColor(*this, writer, "Purple", Purple)
			|| WriteColor(*this, writer, "Turquoise", Turquoise)
			|| WriteColor(*this, writer, "Grey", Grey)
			|| WriteColor(*this, writer, "TransparentWhite", TransparentWhite)
			|| WriteColor(*this, writer, "Transparent", Transparent))
		{
			return;
		}
	}
	else if (style == ',')
	{
		writer.Format("{}, {}, {}, {}", R, G, B, A);
		return;
	}

	writer.Write('#');
	writer.Write(R, "#");
	writer.Write(G, "#");
	writer.Write(B, "#");
	writer.Write(A, "#");
}

void Color::FromString(StringReader& reader, StringView format)
{
	if (reader.ViewNext() == '#')
	{
		reader.Advance(1);

		reader.Read(R, '#');
		reader.Read(G, '#');
		reader.Read(B, '#');
		reader.Read(A, '#');
	}
	else if (ReadColor(*this, reader, "White", White)
		|| ReadColor(*this, reader, "Black", Black)
		|| ReadColor(*this, reader, "Red", Red)
		|| ReadColor(*this, reader, "Green", Green)
		|| ReadColor(*this, reader, "Blue", Blue)
		|| ReadColor(*this, reader, "Yellow", Yellow)
		|| ReadColor(*this, reader, "Purple", Purple)
		|| ReadColor(*this, reader, "Turquoise", Turquoise)
		|| ReadColor(*this, reader, "Grey", Grey)
		|| ReadColor(*this, reader, "TransparentWhite", TransparentWhite)
		|| ReadColor(*this, reader, "Transparent", Transparent))
	{
	}
	else
	{
		reader.Parse("{}, {}, {}, {}", R, G, B, A);
	}
}


namespace
{
	auto Clamp(float value) -> unsigned char
	{
		auto clamped = static_cast<int>(value * 256);
		return clamped < 0 ? 0 : (clamped > 255 ? 255 : clamped);
	}
}

auto ColorHdr::Clamped() const -> Color
{
	return
	{
		Clamp(R),
		Clamp(G),
		Clamp(B),
		Clamp(A)
	};
}

void ColorHdr::ToBuffer(BufferWriter& writer) const
{
	writer.Write(R);
	writer.Write(G);
	writer.Write(B);
	writer.Write(A);
}

void ColorHdr::FromBuffer(BufferReader& reader)
{
	reader.Read(R);
	reader.Read(G);
	reader.Read(B);
	reader.Read(A);
}

void ColorHdr::ToString(StringWriter& writer, StringView format) const
{
	writer.Format("{} {} {} {}", R, G, B, A);
}

void ColorHdr::FromString(StringReader& reader, StringView format)
{
	float rf, gf, bf, af = 1.0f;
	if (reader.Parse("{} {} {} {}", rf, gf, bf, af) || reader.Parse("{} {} {}", rf, gf, bf))
		*this = { rf, gf, bf, af };
	else
		reader.ReportError("not a valid ColorHdr: input must be 3 or four floating point numbers separated by spaces");
}
