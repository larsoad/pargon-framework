#include "Pargon/Debugging/StackTrace.h"

using namespace Pargon;

StackCapture::StackCapture()
{
	StackTrace = GetStackTrace();
}
