#pragma once

#include <string>
#include <vector>

namespace Pargon
{
	struct StackFrame
	{
		std::string Name;
		std::string Filename;
		std::uint64_t LineNumber;
	};

	struct StackTrace
	{
		std::vector<StackFrame> Frames;
	};

	struct StackCapture
	{
		StackTrace StackTrace;
		StackCapture();
	};

	auto GetStackTrace() -> StackTrace;
}
