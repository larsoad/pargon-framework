#include "Pargon/Debugging.Win32.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <csignal>

using namespace Pargon;

auto CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) -> int
{
	AddWindowsDebugLogger();

	Log(LogEntryType::Debug, "Main", "Test {} {}", "Hello", 5);

	return 0;
}
