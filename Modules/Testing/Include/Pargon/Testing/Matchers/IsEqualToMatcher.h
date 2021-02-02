#pragma once

#include "Pargon/Testing/TestMatcher.h"

namespace Pargon::Testing::Matchers
{
	template<typename ValueType>
	class IsEqualToMatcher : public ValueMatcher<ValueType>
	{
		const ValueType& _matchValue;

	public:
		IsEqualToMatcher(const ValueType& matchValue);

		auto Test(const ValueType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	template<typename ValueType> auto IsEqualTo(const ValueType& value) -> IsEqualToMatcher<ValueType>;
}

template<typename ValueType>
Pargon::Testing::Matchers::IsEqualToMatcher<ValueType>::IsEqualToMatcher(const ValueType& matchValue) :
	_matchValue(matchValue)
{
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsEqualToMatcher<ValueType>::Test(const ValueType& testValue) const -> bool
{
	return testValue == _matchValue;
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsEqualToMatcher<ValueType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} == {}", name, _matchValue);
}

template<typename ValueType>
auto Pargon::Testing::Matchers::IsEqualTo(const ValueType& value) -> IsEqualToMatcher<ValueType>
{
	return IsEqualToMatcher<ValueType>(value);
}
