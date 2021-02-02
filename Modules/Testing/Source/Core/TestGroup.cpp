#include "Pargon/Testing/TestGroup.h"

using namespace Pargon::Testing;

namespace
{
	struct RootTest : TestGroup
	{
		RootTest() : TestGroup("Root", *this) { }
	};
}

auto Pargon::Testing::RootSuite() -> TestGroup&
{
	static RootTest _root;
	return _root;
}

auto TestGroup::RunAll() -> TestGroupResult
{
	TestGroupResult results;

	results.Name = _name;
	RunFunctions(results.Functions);
	RunGroups(results.Groups);

	return results;
}

TestGroup::TestGroup(std::string_view name) : TestGroup(name, RootSuite())
{
}

TestGroup::TestGroup(std::string_view name, TestGroup& parent) :
	_name(name)
{
	if (std::addressof(parent) != this)
		parent._groups.push_back(*this);
}

void TestGroup::RunFunctions(std::vector<TestFunctionResult>& results)
{
	for (auto& function : _functions)
	{
		auto result = RunFunction(*function);
		results.push_back(std::move(result));
	}
}

auto TestGroup::RunFunction(TestFunction& function) -> TestFunctionResult
{
	try
	{
		function.Execute(*this);
	}
	catch (const TestRunnerBreak&)
	{
	}
	catch (...)
	{
		// add this error to the results
	}

	return { function.Name, std::move(_currentResults) };
}

void TestGroup::RunGroups(std::vector<TestGroupResult>& results)
{
	for (auto& group : _groups)
	{
		auto result = RunGroup(group.get());
		results.push_back(std::move(result));
	}
}

auto TestGroup::RunGroup(TestGroup& group) -> TestGroupResult
{
	return group.RunAll();
}
