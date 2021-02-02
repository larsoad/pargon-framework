#include "Pargon/Debugging/Log.Win32.h"

#include <Windows.h>

using namespace Pargon;

namespace
{
	class WindowsLogger : public Logger
	{
		virtual void Log(const LogEntry& entry) const override
		{
			OutputDebugStringA(entry.Category.c_str());
			OutputDebugStringA(" - ");
			OutputDebugStringA(entry.Message.c_str());
			OutputDebugStringA("\n");

			// TODO: Log all the stuff - use thread id if thread isn't named
			// TODO: Per platform formatter for source_location so it is double-clickable in debuggers
		}
	};
}

void Pargon::AddWindowsDebugLogger()
{
	static WindowsLogger _logger; // TODO: Loggers need to clean themselves up in their destructor so static initialization order doesn't destroy them while logging still might happen
	AddLogger(std::addressof(_logger));
}
