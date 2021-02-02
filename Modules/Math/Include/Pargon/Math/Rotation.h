#pragma once

namespace Pargon
{
	class Angle;
	class BufferReader;
	class BufferWriter;
	class StringReader;
	class StringView;
	class StringWriter;

	class Rotation
	{
	public:
		static constexpr auto FromDegrees(float degrees) -> Rotation;
		static constexpr auto FromRadians(float radians) -> Rotation;

		constexpr auto operator==(Rotation right) const -> bool;
		constexpr auto operator!=(Rotation right) const -> bool;
		constexpr auto operator<(Rotation right) const -> bool;
		constexpr auto operator>(Rotation right) const -> bool;
		constexpr auto operator<=(Rotation right) const -> bool;
		constexpr auto operator>=(Rotation right) const -> bool;

		constexpr auto operator-=(Rotation right) -> Rotation&;
		constexpr auto operator+=(Rotation right) -> Rotation&;
		constexpr auto operator*=(float scalar) -> Rotation&;
		constexpr auto operator/=(float scalar) -> Rotation&;

		constexpr auto operator-() const -> Rotation;
		constexpr auto operator+(Rotation right) const -> Rotation;
		constexpr auto operator-(Rotation right) const -> Rotation;
		constexpr auto operator*(float scalar) const -> Rotation;
		constexpr auto operator/(float scalar) const -> Rotation;

		constexpr auto InDegrees() const -> float;
		constexpr auto InRadians() const -> float;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);

	private:
		static constexpr float _pi = 3.1415927f;

		float _radians = 0.0f;
	};
}

constexpr
auto Pargon::Rotation::FromDegrees(float degrees) -> Rotation
{
	Rotation rotation;
	rotation._radians = degrees * _pi / 180.0f;
	return rotation;
}

constexpr
auto Pargon::Rotation::FromRadians(float radians) -> Rotation
{
	Rotation rotation;
	rotation._radians = radians;
	return rotation;
}

constexpr
auto Pargon::Rotation::operator==(Rotation right) const -> bool
{
	return _radians == right._radians;
}

constexpr
auto Pargon::Rotation::operator!=(Rotation right) const -> bool
{
	return _radians != right._radians;
}

constexpr
auto Pargon::Rotation::operator<(Rotation right) const -> bool
{
	return _radians < right._radians;
}

constexpr
auto Pargon::Rotation::operator>(Rotation right) const -> bool
{
	return _radians > right._radians;
}

constexpr
auto Pargon::Rotation::operator<=(Rotation right) const -> bool
{
	return _radians <= right._radians;
}

constexpr
auto Pargon::Rotation::operator>=(Rotation right) const -> bool
{
	return _radians >= right._radians;
}

constexpr
auto Pargon::Rotation::operator-=(Rotation right) -> Rotation&
{
	_radians -= right._radians;
	return *this;
}

constexpr
auto Pargon::Rotation::operator+=(Rotation right) -> Rotation&
{
	_radians += right._radians;
	return *this;
}

constexpr
auto Pargon::Rotation::operator*=(float scalar) -> Rotation&
{
	_radians *= scalar;
	return *this;
}

constexpr
auto Pargon::Rotation::operator/=(float scalar) -> Rotation&
{
	_radians /= scalar;
	return *this;
}

constexpr
auto Pargon::Rotation::operator-() const -> Rotation
{
	return FromRadians(-_radians);
}

constexpr
auto Pargon::Rotation::operator+(Rotation right) const -> Rotation
{
	return FromRadians(_radians + right._radians);
}

constexpr
auto Pargon::Rotation::operator-(Rotation right) const -> Rotation
{
	return FromRadians(_radians - right._radians);
}

constexpr
auto Pargon::Rotation::operator*(float scalar) const -> Rotation
{
	return FromRadians(_radians * scalar);
}

constexpr
auto Pargon::Rotation::operator/(float scalar) const -> Rotation
{
	return FromRadians(_radians / scalar);
}

constexpr
auto Pargon::Rotation::InDegrees() const -> float
{
	return _radians * 180.0f / _pi;
}

constexpr
auto Pargon::Rotation::InRadians() const -> float
{
	return _radians;
}
