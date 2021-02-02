#pragma once

#include <type_traits>

namespace Pargon
{
	struct Division
	{
		int Quotient;
		int Remainder;
	};

	auto IsCloseTo(float left, float right, float difference = 0.0001f) -> bool;
	auto IsLessThan(float left, float right, float difference = 0.0001f) -> bool;
	auto IsLessThanOrCloseTo(float left, float right, float difference = 0.0001f) -> bool;
	auto IsGreaterThan(float left, float right, float difference = 0.0001f) -> bool;
	auto IsGreaterThanOrCloseTo(float left, float right, float difference = 0.0001f) -> bool;
	auto Ceiling(float number) -> int;
	auto Ceiling(double number) -> long long;
	auto Floor(float number) -> int;
	auto Floor(double number) -> long long;
	auto Round(float number) -> int;
	auto Round(double number) -> long long;
	auto Truncate(float number) -> int;
	auto Truncate(double number) -> long long;

	template<typename T> constexpr auto AbsoluteValue(T number) -> T;
	template<typename T> constexpr auto Minimum(T left, T right) -> T;
	template<typename T> constexpr auto Maximum(T left, T right) -> T;
	template<typename T> constexpr auto Clamp(T number, T minimum, T maximum) -> T;
	template<typename T> constexpr auto Wrap(T number, T minimum, T maximum) -> T;

	template<typename T, typename... Ts> constexpr auto Minimum(T&& first, T&& second, Ts&&... items) -> std::remove_reference_t<T>;
	template<typename T, typename... Ts> constexpr auto Maximum(T&& first, T&& second, Ts&&... items) -> std::remove_reference_t<T>;

	auto SquareRoot(float number) -> float;
	auto SquareRoot(double number) -> double;
	auto Power(float number, float exponent) -> float;
	auto Power(double number, double exponent) -> double;
	auto Log10(float number) -> float;

	auto Divide(int numerator, int denominator) -> Division;
}

template<typename T> constexpr
auto Pargon::AbsoluteValue(T number) -> T
{
	return number < 0 ? -number : number;
}

template<typename T> constexpr
auto Pargon::Minimum(T left, T right) -> T
{
	return left < right ? left : right;
}

template<typename T> constexpr
auto Pargon::Maximum(T left, T right) -> T
{
	return left > right ? left : right;
}

template<typename T> constexpr
auto Pargon::Clamp(T number, T minimum, T maximum) -> T
{
	return  number < minimum ? minimum : (number > maximum ? maximum : number);
}

template<typename T> constexpr
auto Pargon::Wrap(T number, T minimum, T maximum) -> T
{
	auto difference = maximum - minimum;
	
	if (difference <= 0)
		return 0;

	while (number >= maximum)
		number -= difference;

	while (number < minimum)
		number += difference;

	return number;
}

template<typename T, typename... Ts> constexpr
auto Pargon::Minimum(T&& first, T&& second, Ts&&... items) -> std::remove_reference_t<T>
{
	return Minimum(Minimum(std::forward<T>(first), std::forward<T>(second)), std::forward<Ts>(items)...);
}

template<typename T, typename... Ts> constexpr
auto Pargon::Maximum(T&& first, T&& second, Ts&&... items) -> std::remove_reference_t<T>
{
	return Maximum(Maximum(std::forward<T>(first), std::forward<T>(second)), std::forward<Ts>(items)...);
}
