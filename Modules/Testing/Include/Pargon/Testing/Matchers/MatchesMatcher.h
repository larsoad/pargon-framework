#pragma once

#include "Pargon/Testing/TestMatcher.h"

#include <regex>
#include <string>

namespace Pargon::Testing::Matchers
{
	class MatchesMatcher : ValueMatcher<std::string>
	{
		std::string _pattern;
		std::regex _expression;

	public:
		MatchesMatcher(std::string_view pattern);

		auto Test(const std::string& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	auto Matches(std::string_view pattern) -> MatchesMatcher;
}

inline
Pargon::Testing::Matchers::MatchesMatcher::MatchesMatcher(std::string_view pattern) :
	_pattern(pattern),
	_expression(_pattern)
{
}

inline
auto Pargon::Testing::Matchers::MatchesMatcher::Test(const std::string& testValue) const -> bool
{
	return std::regex_match(testValue, _expression);
}


inline
auto Pargon::Testing::Matchers::MatchesMatcher::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} matches /{}/", name, _pattern);
}

inline
auto Pargon::Testing::Matchers::Matches(std::string_view pattern) -> MatchesMatcher
{
	return MatchesMatcher(pattern);
}
