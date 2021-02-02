#include "Pargon/Serialization/Serializer.h"
#include "Pargon/Types/Time.h"

using namespace Pargon;

void Time::ToString(StringWriter& writer) const
{
	return writer.Format("{}ms", InMilliseconds());
}

void Time::FromString(StringReader& reader)
{
	long long i;
	double f;

	if (reader.Parse("{}ns", i))
		SetNanoseconds(i);
	else if (reader.Parse("{}us", i))
		SetMicroseconds(i);
	else if (reader.Parse("{}ms", i))
		SetMilliseconds(i);
	else if (reader.Parse("{}sec", f))
		SetSeconds(f);
	else if (reader.Parse("{}min", f))
		SetMinutes(f);
	else if (reader.Parse("{}hr", f))
		SetHours(f);
}
