#include "Pargon/Debugging.h"
#include "Pargon/Testing.h"

#include <iostream>

using namespace Pargon;
using namespace Pargon::Testing;

namespace
{
	auto GetStatusText(TestStatus status) -> const char*
	{
		switch (status)
		{
			case TestStatus::Success: return "Success";
			case TestStatus::Failure: return "Failure";
			case TestStatus::Error: return "Error";
		}

		return "Unknown";
	}

	void PrintResult(const TestResult& result, std::string indent)
	{
		auto status = GetStatusText(result.Status);
		Log("{}{} - {}", indent, status, result.Description);
	}

	void PrintResults(const TestFunctionResult& results, std::string indent)
	{
		Log("{}{}", indent, results.Name);

		for (auto& result : results.Results)
			PrintResult(result, indent + "\t");
	}

	void PrintResults(const TestGroupResult& results, std::string indent)
	{
		Log("{}{}", indent, results.Name);

		for (auto& test : results.Functions)
			PrintResults(test, indent + "\t");

		for (auto& group : results.Groups)
			PrintResults(group, indent + "\t");
	}

	struct CoutLogger : Logger
	{
		void Log(const LogEntry& entry) const override
		{
			std::cout << entry.Message << "\n";
		}
	};
}

auto main(int argc, char* argv[]) -> int
{
	auto fs = RootSuite().Functions();

	CoutLogger logger;

	AddLogger(std::addressof(logger));

	for (auto f : fs)
		Log("{}", f);

	auto results = RootSuite().RunAll();
	PrintResults(results, "");
	return 0;
}
