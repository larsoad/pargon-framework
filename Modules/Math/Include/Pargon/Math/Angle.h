#pragma once

#include "Pargon/Math/Rotation.h"

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class StringReader;
	class StringView;
	class StringWriter;

	class Angle
	{
	public:
		static constexpr auto FromDegrees(float degrees) -> Angle;
		static constexpr auto FromRadians(float radians) -> Angle;

		Angle() = default;
		explicit constexpr Angle(Rotation rotation);

		constexpr operator Rotation() const;

		constexpr auto operator==(Angle angle) const -> bool;
		constexpr auto operator!=(Angle angle) const -> bool;
		constexpr auto operator<(Angle angle) const -> bool;
		constexpr auto operator>(Angle angle) const -> bool;
		constexpr auto operator<=(Angle angle) const -> bool;
		constexpr auto operator>=(Angle angle) const -> bool;

		constexpr auto operator+=(Rotation right) -> Angle&;
		constexpr auto operator-=(Rotation right) -> Angle&;
		constexpr auto operator*=(float scalar) -> Angle&;
		constexpr auto operator/=(float scalar) -> Angle&;

		constexpr auto operator-() const -> Angle;
		constexpr auto operator+(Rotation right) const -> Angle;
		constexpr auto operator-(Rotation right) const -> Angle;
		constexpr auto operator*(float scalar) const -> Angle;
		constexpr auto operator/(float scalar) const -> Angle;

		constexpr auto InDegrees() const -> float;
		constexpr auto InRadians() const -> float;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);

	private:
		static constexpr float _tau = 6.2831853f;
		static constexpr float _pi = 3.1415927f;

		float _radians = 0.0f;

		constexpr void SetRadians(float radians);
	};

	constexpr auto operator""_degrees(long double degrees) -> Angle;
	constexpr auto operator""_degrees(unsigned long long degrees) -> Angle;
	constexpr auto operator""_radians(long double radians) -> Angle;
}

constexpr
void Pargon::Angle::SetRadians(float radians)
{
	if (radians < 0.0f)
		_radians = radians + (static_cast<int>(-radians / _tau) + 1) * _tau;
	else if (radians >= _tau)
		_radians = radians - static_cast<int>(radians / _tau) * _tau;
	else
		_radians = radians;
}

constexpr
auto Pargon::Angle::FromDegrees(float degrees) -> Angle
{
	Angle angle;
	angle.SetRadians(degrees * _pi / 180.0f);
	return angle;
}

constexpr
auto Pargon::Angle::FromRadians(float radians) -> Angle
{
	Angle angle;
	angle.SetRadians(radians);
	return angle;
}

constexpr 
Pargon::Angle::Angle(Rotation rotation)
{
	SetRadians(rotation.InRadians());
}

constexpr
Pargon::Angle::operator Pargon::Rotation() const
{
	return Rotation::FromRadians(_radians);
}

constexpr
auto Pargon::Angle::operator==(Angle right) const -> bool
{
	return _radians == right._radians;
}

constexpr
auto Pargon::Angle::operator!=(Angle right) const -> bool
{
	return _radians != right._radians;
}

constexpr
auto Pargon::Angle::operator<(Angle right) const -> bool
{
	return _radians < right._radians;
}

constexpr
auto Pargon::Angle::operator>(Angle right) const -> bool
{
	return _radians > right._radians;
}

constexpr
auto Pargon::Angle::operator<=(Angle right) const -> bool
{
	return _radians <= right._radians;
}

constexpr
auto Pargon::Angle::operator>=(Angle right) const -> bool
{
	return _radians >= right._radians;
}

constexpr
auto Pargon::Angle::operator+=(Rotation right) -> Angle&
{
	SetRadians(_radians + right.InRadians());
	return *this;
}

constexpr
auto Pargon::Angle::operator-=(Rotation right) -> Angle&
{
	SetRadians(_radians - right.InRadians());
	return *this;
}

constexpr
auto Pargon::Angle::operator*=(float scalar) -> Angle&
{
	SetRadians(_radians * scalar);
	return *this;
}

constexpr
auto Pargon::Angle::operator/=(float scalar) -> Angle&
{
	SetRadians(_radians / scalar);
	return *this;
}

constexpr
auto Pargon::Angle::operator-() const -> Angle
{
	return FromRadians(-_radians);
}

constexpr
auto Pargon::Angle::operator+(Rotation right) const -> Angle
{
	return FromRadians(_radians + right.InRadians());
}

constexpr
auto Pargon::Angle::operator-(Rotation right) const -> Angle
{
	return FromRadians(_radians - right.InRadians());
}

constexpr
auto Pargon::Angle::operator*(float scalar) const -> Angle
{
	return Angle::FromRadians(_radians * scalar);
}

constexpr
auto Pargon::Angle::operator/(float scalar) const -> Angle
{
	return Angle::FromRadians(_radians / scalar);
}

constexpr
auto Pargon::Angle::InDegrees() const -> float
{
	return _radians * 180.0f / _pi;
}

constexpr
auto Pargon::Angle::InRadians() const -> float
{
	return _radians;
}

constexpr
auto Pargon::operator""_degrees(long double degrees) -> Angle
{
	return Angle::FromDegrees(static_cast<float>(degrees));
}

constexpr
auto Pargon::operator""_degrees(unsigned long long degrees) -> Angle
{
	return Angle::FromDegrees(static_cast<float>(degrees));
}

constexpr
auto Pargon::operator""_radians(long double radians) -> Angle
{
	return Angle::FromRadians(static_cast<float>(radians));
}
