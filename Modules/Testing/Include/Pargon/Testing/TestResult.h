#pragma once

#include <string>
#include <vector>

namespace Pargon::Testing
{
	enum class TestStatus
	{
		Success,
		Failure,
		Error
	};

	struct TestResult
	{
		TestStatus Status;
		std::string Description;
	};

	struct TestFunctionResult
	{
		std::string Name;
		std::vector<TestResult> Results;
	};

	struct TestGroupResult
	{
		std::string Name;
		std::vector<TestFunctionResult> Functions;
		std::vector<TestGroupResult> Groups;
	};
}
