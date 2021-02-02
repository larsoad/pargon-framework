#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsInequalToMatcher : ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsInequalToMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsInequalTo(const ValueType& value) -> IsInequalToMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsInequalToMatcher<ValueType>::IsInequalToMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsInequalToMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue != _matchValue;
}


template<typename ValueType>
auto Pargon::Testing::Matchers::IsInequalToMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} != {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsInequalTo(const ValueType& value) -> IsInequalToMatcher<ValueType>
{
	return IsInequalToMatcher<ValueType>(value);
}
