#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsGreaterThanOrEqualToMatcher : ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsGreaterThanOrEqualToMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsGreaterThanOrEqualTo(const ValueType& value) -> IsGreaterThanOrEqualToMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsGreaterThanOrEqualToMatcher<ValueType>::IsGreaterThanOrEqualToMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThanOrEqualToMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue >= _matchValue;
}


template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThanOrEqualToMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} >= {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThanOrEqualTo(const ValueType& value) -> IsGreaterThanOrEqualToMatcher<ValueType>
{
	return IsGreaterThanOrEqualToMatcher<ValueType>(value);
}
