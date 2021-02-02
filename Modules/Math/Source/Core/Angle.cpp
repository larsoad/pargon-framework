#include "Pargon/Math/Angle.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

using namespace Pargon;

void Angle::ToBuffer(BufferWriter& writer) const
{
	writer.Write(_radians);
}

void Angle::FromBuffer(BufferReader& reader)
{
	reader.Read(_radians);
}

void Angle::ToString(StringWriter& writer, StringView format) const
{
	if (StartsWith(format, "degrees", true))
	{
		writer.Write(InDegrees(), format.GetSubview(7));
		writer.Write("_degrees", "");
	}
	else
	{
		auto radiansFormat = StartsWith(format, "radians", true) ? format.GetSubview(7) : format;

		writer.Write(InRadians(), radiansFormat);
		writer.Write("_radians", "");
	}
}

void Angle::FromString(StringReader& reader, StringView format)
{
	float amount;

	if (!reader.Read(amount, ""))
		reader.ReportError("the string could not be read as an Angle (expected a floating point number optionally followed by '_degrees' or '_radians')");

	if (Equals(format, "degrees", true) || StartsWith(reader.ViewRemaining(), "_degrees", true))
	{
		reader.AdvancePast("_degrees", true);
		*this = FromDegrees(amount);
	}
	else
	{
		reader.AdvancePast("_radians", true);
		*this = FromRadians(amount);
	}
}
