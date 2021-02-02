#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsGreaterThanMatcher : ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsGreaterThanMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsGreaterThan(const ValueType& value) -> IsGreaterThanMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsGreaterThanMatcher<ValueType>::IsGreaterThanMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThanMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue > _matchValue;
}


template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThanMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} > {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsGreaterThan(const ValueType& value) -> IsGreaterThanMatcher<ValueType>
{
	return IsGreaterThanMatcher<ValueType>(value);
}
