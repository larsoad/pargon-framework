#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsLessThanMatcher : ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsLessThanMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsLessThan(const ValueType& value) -> IsLessThanMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsLessThanMatcher<ValueType>::IsLessThanMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThanMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue < _matchValue;
}


template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThanMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} < {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThan(const ValueType& value) -> IsLessThanMatcher<ValueType>
{
	return IsLessThanMatcher<ValueType>(value);
}
