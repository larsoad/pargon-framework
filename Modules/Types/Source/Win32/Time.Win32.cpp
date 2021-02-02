#include "Pargon/Types/Time.h"

#include <objbase.h>
#include <shellapi.h>
#include <shlobj.h>

using namespace Pargon;

#undef GetCurrentTime

namespace
{
	struct FrequencyRetrieval
	{
		FrequencyRetrieval()
		{
			QueryPerformanceFrequency(&Frequency);
		}

		LARGE_INTEGER Frequency;
	};

	auto GetFrequency() -> LARGE_INTEGER
	{
		static FrequencyRetrieval _frequency;
		return _frequency.Frequency;
	};

	auto GetTime() -> LARGE_INTEGER
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return time;
	};
}

auto Pargon::GetCurrentTime() -> Time
{
	auto frequency = GetFrequency();
	auto time = GetTime();

	return Time::FromMicroseconds(time.QuadPart * 1000000 / frequency.QuadPart);
}
