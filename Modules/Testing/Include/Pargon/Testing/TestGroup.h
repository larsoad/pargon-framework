#pragma once

#include "Pargon/Testing/TestContext.h"
#include "Pargon/Testing/TestMatcher.h"
#include "Pargon/Testing/TestResult.h"

#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace Pargon::Testing
{
	class TestGroup
	{
		struct TestFunction
		{
			std::string Name;
			virtual void Execute(TestGroup& test) = 0;
		};

		std::string _name;
		std::vector<std::unique_ptr<TestFunction>> _functions;
		std::vector<std::reference_wrapper<TestGroup>> _groups;
		std::vector<TestResult> _currentResults;

	public:
		TestGroup(std::string_view name);
		TestGroup(std::string_view name, TestGroup& parent);

		auto Name() const -> std::string_view;
		auto Functions() const -> std::vector<std::string_view>; // PENDING: Return a ranges view into _functions.
		auto Groups() const -> const std::vector<std::reference_wrapper<TestGroup>>&; // PENDING Return a ranges view of const TestGroup&.

		auto RunAll() -> TestGroupResult;

	protected:
		template<typename TestSignature> void AddTest(std::string_view name, TestSignature test);

		template<typename TestType, typename MatcherType> void Require(std::string_view name, const TestType& test, MatcherType&& matcher);
		template<typename TestType, typename MatcherType> void Check(std::string_view name, const TestType& test, MatcherType&& matcher);

	private:
		template<typename Signature> struct TestRunner;
		struct TestRunnerBreak {};

		void RunFunctions(std::vector<TestFunctionResult>& results);
		auto RunFunction(TestFunction& function) -> TestFunctionResult;
		void RunGroups(std::vector<TestGroupResult>& results);
		auto RunGroup(TestGroup& group) -> TestGroupResult;

		template<typename TestType, typename MatcherType> auto RunTest(const TestType& test, MatcherType& matcher) -> bool;
	};
	
	auto RootSuite() -> TestGroup&;
}

inline
auto Pargon::Testing::TestGroup::Name() const -> std::string_view
{
	return _name;
}

inline
auto Pargon::Testing::TestGroup::Functions() const -> std::vector<std::string_view>
{
	std::vector<std::string_view> functions;

	for (auto& f : _functions)
		functions.emplace_back(f->Name);

	return functions;
}

inline
auto Pargon::Testing::TestGroup::Groups() const -> const std::vector<std::reference_wrapper<TestGroup>>&
{
	return _groups;
}

template<typename TestType, typename ContextType>
struct Pargon::Testing::TestGroup::TestRunner<void(TestType::*)(ContextType&)> : TestFunction
{
	void(TestType::* Function)(ContextType&);

	void Execute(TestGroup& test) override
	{
		auto i = 0;
		ContextType context;

		while (context.Next(i++))
			(static_cast<TestType&>(test).*Function)(context);
	}
};

template<typename TestType>
struct Pargon::Testing::TestGroup::TestRunner<void(TestType::*)()> : TestFunction
{
	void(TestType::*Function)();

	void Execute(TestGroup& test) override
	{
		auto i = 0;
		(static_cast<TestType&>(test).*Function)();
	}
};

template<typename TestSignature>
void Pargon::Testing::TestGroup::AddTest(std::string_view name, TestSignature test)
{
	auto function = std::make_unique<TestRunner<TestSignature>>();
	function->Name = name;
	function->Function = test;
	_functions.push_back(std::move(function));
}

template<typename TestType, typename MatcherType>
void Pargon::Testing::TestGroup::Require(std::string_view name, const TestType& test, MatcherType&& matcher)
{
	auto success = RunTest(test, matcher);
	auto status = success ? TestStatus::Success : TestStatus::Error;
	auto description = matcher.Description(name);

	_currentResults.push_back({ status, std::move(description) });

	if (!success)
		throw TestRunnerBreak();
}

template<typename TestType, typename MatcherType>
void Pargon::Testing::TestGroup::Check(std::string_view name, const TestType& test, MatcherType&& matcher)
{
	auto success = RunTest(test, matcher);
	auto status = success ? TestStatus::Success : TestStatus::Failure;
	auto description = matcher.Description(name);

	_currentResults.push_back({ status, std::move(description) });
}

template<typename TestType, typename MatcherType>
auto Pargon::Testing::TestGroup::RunTest(const TestType& test, MatcherType& matcher) -> bool
{
	if constexpr (std::is_base_of_v<ValueMatcher<TestType>, MatcherType>)
	{
		return matcher.Test(test);
	}
	else if constexpr (std::is_invocable_v<TestType>)
	{
		if constexpr (std::is_void_v<std::invoke_result_t<TestType>>&& std::is_base_of_v<InvocableMatcher, MatcherType>)
		{
			return matcher.Test(test);
		}
		else if constexpr (std::is_base_of_v<ValueMatcher<std::invoke_result_t<TestType>>, MatcherType>)
		{
			auto result = std::invoke(test);
			return matcher.Test(result);
		}
		else
		{
			static_assert("Invocable tests must return a type corresponding to the matcher");
		}
	}
	else
	{
		static_assert("Test types must match the type of the Matcher or return a type that matches the type of the Matcher");
	}

	return false;
}
