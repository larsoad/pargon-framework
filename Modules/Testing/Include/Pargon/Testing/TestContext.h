#pragma once

#include <memory>
#include <vector>

namespace Pargon::Testing
{
	struct TestContext
	{
		virtual auto Next(int iteration) -> bool = 0;
	};
}
