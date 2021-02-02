#include "Pargon/Math/Arithmetic.h"

#include <cmath>

auto Pargon::IsCloseTo(float left, float right, float difference) -> bool
{
	return std::abs(left - right) < difference;
}

auto Pargon::IsLessThan(float left, float right, float difference) -> bool
{
	return left + difference < right;
}

auto Pargon::IsLessThanOrCloseTo(float left, float right, float difference) -> bool
{
	return IsLessThan(left, right, difference) || IsCloseTo(left, right, difference);
}

auto Pargon::IsGreaterThan(float left, float right, float difference) -> bool
{
	return left - difference > right;
}

auto Pargon::IsGreaterThanOrCloseTo(float left, float right, float difference) -> bool
{
	return IsGreaterThan(left, right, difference) || IsCloseTo(left, right, difference);
}

auto Pargon::Ceiling(float number) -> int
{
	return static_cast<int>(std::ceil(number));
}

auto Pargon::Ceiling(double number) -> long long
{
	return static_cast<long long>(std::ceil(number));
}

auto Pargon::Floor(float number) -> int
{
	return static_cast<int>(std::floor(number));
}

auto Pargon::Floor(double number) -> long long
{
	return static_cast<long long>(std::floor(number));
}

auto Pargon::Round(float number) -> int
{
	return static_cast<int>(std::round(number));
}

auto Pargon::Round(double number) -> long long
{
	return static_cast<long long>(std::round(number));
}

auto Pargon::Truncate(float number) -> int
{
	return static_cast<int>(std::trunc(number));
}

auto Pargon::Truncate(double number) -> long long
{
	return static_cast<long long>(std::trunc(number));
}

auto Pargon::SquareRoot(float number) -> float
{
	return std::sqrt(number);
}

auto Pargon::SquareRoot(double number) -> double
{
	return std::sqrt(number);
}

auto Pargon::Power(float number, float exponent) -> float
{
	return std::pow(number, exponent);
}

auto Pargon::Power(double number, double exponent) -> double
{
	return std::pow(number, exponent);
}

auto Pargon::Log10(float number) -> float
{
	return std::log10f(number);
}

auto Pargon::Divide(int numerator, int denominator) -> Division
{
	return { numerator / denominator, numerator % denominator };
}
