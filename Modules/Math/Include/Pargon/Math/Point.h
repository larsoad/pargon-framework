#pragma once

#include "Pargon/Math/Vector.h"

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class Matrix3x3;
	class Matrix4x4;
	class StringReader;
	class StringView;
	class StringWriter;

	class Point2
	{
	public:
		float X;
		float Y;

		constexpr auto operator==(const Point2& right) const -> bool;
		constexpr auto operator!=(const Point2& right) const -> bool;
		
		constexpr auto operator+=(Vector2 direction) -> Point2&;
		constexpr auto operator-=(Vector2 direction) -> Point2&;
		constexpr auto operator*=(float scalar) -> Point2&;
		auto operator*=(const Matrix3x3& transform) -> Point2&;

		constexpr auto operator+(Vector2 direction) const -> Point2;
		constexpr auto operator-(Vector2 direction) const -> Point2;
		constexpr auto operator-(Point2 point) const -> Vector2;
		constexpr auto operator*(float scalar) const -> Point2;
		auto operator*(const Matrix3x3& transform) const -> Point2;

		auto AsOffset() const -> Vector2;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};

	class Point3
	{
	public:
		float X;
		float Y;
		float Z;

		constexpr auto operator==(const Point3& right) const -> bool;
		constexpr auto operator!=(const Point3& right) const -> bool;

		constexpr auto operator+=(Vector3 direction) -> Point3&;
		constexpr auto operator-=(Vector3 direction) -> Point3&;
		constexpr auto operator*=(float scalar) -> Point3&;
		auto operator*=(const Matrix4x4& transform) -> Point3&;

		constexpr auto operator+(Vector3 direction) const -> Point3;
		constexpr auto operator-(Vector3 direction) const -> Point3;
		constexpr auto operator-(Point3 point) const -> Vector3;
		constexpr auto operator*(float scalar) const -> Point3;
		auto operator*(const Matrix4x4& transform) const -> Point3;

		auto AsOffset() const -> Vector3;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};
}

constexpr
auto Pargon::Point2::operator==(const Point2& right) const -> bool
{
	return X == right.X && Y == right.Y;
}

constexpr
auto Pargon::Point2::operator!=(const Point2& right) const -> bool
{
	return !operator==(right);
}

constexpr
auto Pargon::Point2::operator+=(Vector2 direction) -> Point2&
{
	X += direction.X;
	Y += direction.Y;
	return *this;
}

constexpr
auto Pargon::Point2::operator-=(Vector2 direction) -> Point2&
{
	X -= direction.X;
	Y -= direction.Y;
	return *this;
}

constexpr
auto Pargon::Point2::operator*=(float scalar) -> Point2&
{
	X *= scalar;
	Y *= scalar;
	return *this;
}

constexpr
auto Pargon::Point2::operator+(Vector2 direction) const -> Point2
{
	return { X + direction.X, Y + direction.Y };
}

constexpr
auto Pargon::Point2::operator-(Vector2 direction) const -> Point2
{
	return { X - direction.X, Y - direction.Y };
}

constexpr
auto Pargon::Point2::operator-(Point2 point) const -> Vector2
{
	return { X - point.X, Y - point.Y };
}

constexpr
auto Pargon::Point2::operator*(float scalar) const -> Point2
{
	return { X * scalar, Y * scalar };
}

constexpr
auto Pargon::Point3::operator==(const Point3& right) const -> bool
{
	return X == right.X && Y == right.Y && Z == right.Z;
}

constexpr
auto Pargon::Point3::operator!=(const Point3& right) const -> bool
{
	return !operator==(right);
}

constexpr
auto Pargon::Point3::operator+=(Vector3 direction) -> Point3&
{
	X += direction.X;
	Y += direction.Y;
	Z += direction.Z;

	return *this;
}

constexpr
auto Pargon::Point3::operator-=(Vector3 direction) -> Point3&
{
	X -= direction.X;
	Y -= direction.Y;
	Z -= direction.Z;

	return *this;
}

constexpr
auto Pargon::Point3::operator*=(float scalar) -> Point3&
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;

	return *this;
}

constexpr
auto Pargon::Point3::operator+(Vector3 direction) const -> Point3
{
	return { X + direction.X, Y + direction.Y, Z + direction.Z };
}

constexpr
auto Pargon::Point3::operator-(Vector3 direction) const -> Point3
{
	return { X - direction.X, Y - direction.Y, Z - direction.Z };
}

constexpr
auto Pargon::Point3::operator-(Point3 point) const -> Vector3
{
	return { X - point.X, Y - point.Y, Z - point.Z };
}

constexpr
auto Pargon::Point3::operator*(float scalar) const -> Point3
{
	return { X * scalar, Y * scalar, Z * scalar };
}
