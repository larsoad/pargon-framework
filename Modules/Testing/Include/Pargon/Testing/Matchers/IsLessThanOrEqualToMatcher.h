#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsLessThanOrEqualToMatcher : ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsLessThanOrEqualToMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsLessThanOrEqualTo(const ValueType& value) -> IsLessThanOrEqualToMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsLessThanOrEqualToMatcher<ValueType>::IsLessThanOrEqualToMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThanOrEqualToMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue <= _matchValue;
}


template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThanOrEqualToMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} <= {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsLessThanOrEqualTo(const ValueType& value) -> IsLessThanOrEqualToMatcher<ValueType>
{
	return IsLessThanOrEqualToMatcher<ValueType>(value);
}
