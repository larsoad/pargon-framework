#pragma once

#include "Pargon/Shim.h"

#include <functional>
#include <string>

namespace Pargon::Testing
{
	struct TestMatcher
	{
		virtual auto Description(std::string_view name) const -> std::string = 0;
	};

	template<typename ValueType>
	struct ValueMatcher : TestMatcher
	{
		virtual auto Test(const ValueType& testValue) const -> bool = 0;
	};

	struct InvocableMatcher : TestMatcher
	{
		virtual auto Test(std::function<void()> invocable) const -> bool = 0;
	};
}
