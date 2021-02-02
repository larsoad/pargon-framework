#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ExceptionType>
	struct ThrowsMatcher : InvocableMatcher
	{
		auto Test(std::function<void()> invocable) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ExceptionType> auto Throws() -> ThrowsMatcher<ExceptionType>;
}

template<typename ExceptionType>
auto Pargon::Testing::Matchers::ThrowsMatcher<ExceptionType>::Test(std::function<void()> invocable) const -> bool
{
	try
	{
		invocable();
	}
	catch (const ExceptionType& exception)
	{
		return true;
	}
	catch (...)
	{
	}

	return false;
}

template<typename ExceptionType>
auto Pargon::Testing::Matchers::ThrowsMatcher<ExceptionType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} throws {}", name, typeid(ExceptionType).name());
}

template<typename ExceptionType>
auto Pargon::Testing::Matchers::Throws() -> ThrowsMatcher<ExceptionType>
{
	return {};
}
