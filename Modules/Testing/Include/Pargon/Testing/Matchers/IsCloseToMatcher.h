#pragma once

#include "Pargon/Testing/TestMatcher.h"

#include <cstdint>
#include <cmath>

namespace Pargon::Testing::Matchers
{
	template<typename FloatType>
	class IsCloseToMatcher : public ValueMatcher<FloatType>
	{
		FloatType _matchValue;
		int _ulps;

		template<typename> struct IntType;
		template<> struct IntType<float> { using type = std::int32_t; };
		template<> struct IntType<double> { using type = std::int64_t; };

		union FloatInt
		{
			FloatType Float;
			typename IntType<FloatType>::type Int;

			FloatInt(FloatType f) : Float(f) { }
		};

	public:
		IsCloseToMatcher(FloatType matchValue, int ulps);

		auto Test(const FloatType& testValue) const -> bool override;
		auto Description(std::string_view name) const -> std::string override;
	};

	auto IsCloseTo(float value, int ulps) -> IsCloseToMatcher<float>;
	auto IsCloseTo(double value, int ulps) -> IsCloseToMatcher<double>;
}

template<typename FloatType>
Pargon::Testing::Matchers::IsCloseToMatcher<FloatType>::IsCloseToMatcher(FloatType matchValue, int ulps) :
	_matchValue(matchValue),
	_ulps(ulps)
{
}

template<typename FloatType>
auto Pargon::Testing::Matchers::IsCloseToMatcher<FloatType>::Test(const FloatType& testValue) const -> bool
{
	if (std::signbit(testValue) != std::signbit(_matchValue))
		return testValue == _matchValue;

	auto left = FloatInt(testValue);
	auto right = FloatInt(_matchValue);
	auto difference = std::abs(left.Int - right.Int);

	return static_cast<int>(difference) <= _ulps;
}

template<typename FloatType>
auto Pargon::Testing::Matchers::IsCloseToMatcher<FloatType>::Description(std::string_view name) const -> std::string
{
	return fmt::format("{} ~= {}", name, _matchValue);
}

inline
auto Pargon::Testing::Matchers::IsCloseTo(float value, int ulps) -> IsCloseToMatcher<float>
{
	return IsCloseToMatcher<float>(value, ulps);
}

inline
auto Pargon::Testing::Matchers::IsCloseTo(double value, int ulps) -> IsCloseToMatcher<double>
{
	return IsCloseToMatcher<double>(value, ulps);
}
