#include "Pargon/Debugging/Log.h"
#include "Pargon/Debugging/StackTrace.h"

#include <Windows.h>
#include <DbgHelp.h>
#include <winnt.h>

using namespace Pargon;

namespace
{
	const char* _symbolSystemInitializationFailedError = "Failed to initialize symbol system";
	const char* _symbolSystemCleanupFailedError = "Failed to cleanup symbol system";

	void LogLastError(std::string_view prefix)
	{
		auto error = GetLastError();
		auto code = std::error_code(error, std::system_category());

		Log("{}: {}", prefix, code.message());
	}

	class SymbolSystem
	{
		bool _isActive;
		HANDLE _process;

	public:
		SymbolSystem()
		{
			SymSetOptions(SYMOPT_UNDNAME | SYMOPT_LOAD_LINES | SYMOPT_DEFERRED_LOADS);

			_process = GetCurrentProcess();
			_isActive = SymInitialize(_process, NULL, TRUE);

			if (!_isActive)
				LogLastError(_symbolSystemInitializationFailedError);
		}

		~SymbolSystem()
		{
			if (_isActive)
			{
				if (!SymCleanup(_process))
					LogLastError(_symbolSystemCleanupFailedError);
			}
		}

		auto GetSymbol(void* address) -> StackFrame
		{
			char infoData[sizeof(SYMBOL_INFO) + MAX_SYM_NAME - 1]; // SYMBOL_INFO includes only one byte for the name
			auto info = reinterpret_cast<SYMBOL_INFO*>(infoData);
			info->SizeOfStruct = sizeof(infoData);
			info->MaxNameLen = MAX_SYM_NAME;

			auto symbol = StackFrame{};
			auto success = SymFromAddr(_process, (DWORD64)address, 0, info);

			if (success)
			{
				symbol.Name = info->Name;

				DWORD displacement;
				IMAGEHLP_LINE line;

				memset(&line, 0, sizeof(line));
				line.SizeOfStruct = sizeof(IMAGEHLP_LINE);

				auto result = SymGetLineFromAddr(_process, (DWORD64)info->Address, &displacement, &line);

				if (result)
				{
					symbol.Filename = line.FileName;
					symbol.LineNumber = line.LineNumber;
				}
			}

			return symbol;
		}
	};

	auto SymbolSystem() -> class SymbolSystem&
	{
		static class SymbolSystem _system;
		return _system;
	}
}

auto Pargon::GetStackTrace() -> StackTrace
{
	static const int _frameCount = 16;

	void* trace[_frameCount];

	auto frames = StackTrace{};
	auto count = RtlCaptureStackBackTrace(1, _frameCount, trace, NULL);

	for (auto i = 1; i < count; i++)
	{
		auto frame = SymbolSystem().GetSymbol(trace[i]);
		frames.Frames.push_back(frame);

		printf(frame.Name.c_str());
		printf("\n");
	}

	return frames;
}
