#pragma once

namespace Pargon
{
	class Angle;
	class BufferReader;
	class BufferWriter;
	class Matrix3x3;
	class Matrix4x4;
	class Quaternion;
	class StringReader;
	class StringView;
	class StringWriter;

	class Vector2
	{
	public:
		static auto CreateNormalized(float x, float y) -> Vector2;
		static auto CreateFromDirection(Angle angle) -> Vector2;

		float X;
		float Y;

		constexpr auto operator==(Vector2 right) const -> bool;
		constexpr auto operator!=(Vector2 right) const -> bool;
		
		constexpr auto operator+=(Vector2 right) -> Vector2&;
		constexpr auto operator-=(Vector2 right) -> Vector2&;
		constexpr auto operator*=(float scalar) -> Vector2&;
		auto operator*=(const Matrix3x3& transform) -> Vector2&;

		constexpr auto operator-() const -> Vector2;
		constexpr auto operator+(Vector2 right) const -> Vector2;
		constexpr auto operator-(Vector2 right) const -> Vector2;
		constexpr auto operator*(float scalar) const -> Vector2;
		auto operator*(const Matrix3x3& transform) const -> Vector2;

		auto GetLength() const -> float;
		constexpr auto GetLengthSquared() const -> float;
		constexpr auto GetDotProduct(Vector2 vector) const -> float;
		constexpr auto GetPerpendicularProduct(Vector2 vector) const -> float;
		auto GetOrientation() const -> Angle;
		auto GetPerpendicular() const -> Vector2;
		auto GetNormal() const -> Vector2;

		void Normalize();
		void Reflect(Vector2 normal, float restitution);
		void Rotate(Angle angle);

		auto Normalized() const -> Vector2;
		auto Reflected(Vector2 normal, float restitution) const -> Vector2;
		auto Rotated(Angle angle) const -> Vector2;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};

	class Vector3
	{
	public:
		static auto CreateNormalized(float x, float y, float z) -> Vector3;
		static auto CreateFromDirection(Quaternion rotation) -> Vector3;

		float X;
		float Y;
		float Z;

		constexpr auto operator==(Vector3 right) const -> bool;
		constexpr auto operator!=(Vector3 right) const -> bool;

		constexpr auto operator+=(Vector3 right) -> Vector3&;
		constexpr auto operator-=(Vector3 right) -> Vector3&;
		constexpr auto operator*=(float scalar) -> Vector3&;
		auto operator*=(const Matrix4x4& transform) -> Vector3&;

		constexpr auto operator-() const -> Vector3;
		constexpr auto operator+(Vector3 right) const -> Vector3;
		constexpr auto operator-(Vector3 right) const -> Vector3;
		constexpr auto operator*(float scalar) const -> Vector3;
		auto operator*(const Matrix4x4& transform) const -> Vector3;

		auto GetLength() const -> float;
		constexpr auto GetLengthSquared() const -> float;
		constexpr auto GetDotProduct(Vector3 vector) const -> float;
		auto GetCrossProduct(Vector3 vector) const -> Vector3;
		auto GetOrientation() const -> Quaternion;

		void Normalize();
		void Reflect(Vector3 normal, float restitution);
		void Rotate(Quaternion rotation);
		void RotateAbout(Vector3 axis, Angle angle);

		auto Normalized() const -> Vector3;
		auto Reflected(Vector3 normal, float restitution) const -> Vector3;
		auto Rotated(Quaternion rotation) const -> Vector3;
		auto RotatedAbout(Vector3 axis, Angle angle) const -> Vector3;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};
}

constexpr
auto Pargon::Vector2::operator==(Vector2 right) const -> bool
{
	return X == right.X && Y == right.Y;
}

constexpr
auto Pargon::Vector2::operator!=(Vector2 right) const -> bool
{
	return !operator==(right);
}

constexpr
auto Pargon::Vector2::operator+=(Vector2 right) -> Vector2&
{
	X += right.X;
	Y += right.Y;

	return *this;
}

constexpr
auto Pargon::Vector2::operator-=(Vector2 right) -> Vector2&
{
	X -= right.X;
	Y -= right.Y;

	return *this;
}

constexpr
auto Pargon::Vector2::operator*=(float scalar) -> Vector2&
{
	X *= scalar;
	Y *= scalar;

	return *this;
}

constexpr
auto Pargon::Vector2::operator-() const -> Vector2
{
	return { -X, -Y };
}

constexpr
auto Pargon::Vector2::operator+(Vector2 right) const -> Vector2
{
	return { X + right.X, Y + right.Y };
}

constexpr
auto Pargon::Vector2::operator-(Vector2 right) const -> Vector2
{
	return { X - right.X, Y - right.Y };
}

constexpr
auto Pargon::Vector2::operator*(float scalar) const -> Vector2
{
	return { X * scalar, Y * scalar };
}

constexpr
auto Pargon::Vector2::GetLengthSquared() const -> float
{
	return X * X + Y * Y;
}

constexpr
auto Pargon::Vector2::GetDotProduct(Vector2 vector) const -> float
{
	return X * vector.X + Y * vector.Y;
}

constexpr
auto Pargon::Vector2::GetPerpendicularProduct(Vector2 vector) const -> float
{
	return X * vector.Y - Y * vector.X;
}

constexpr
auto Pargon::Vector3::operator==(Vector3 right) const -> bool
{
	return X == right.X && Y == right.Y && Z == right.Z;
}

constexpr
auto Pargon::Vector3::operator!=(Vector3 right) const -> bool
{
	return !operator==(right);
}

constexpr
auto Pargon::Vector3::operator+=(Vector3 right) -> Vector3&
{
	X += right.X;
	Y += right.Y;
	Z += right.Z;

	return *this;
}

constexpr
auto Pargon::Vector3::operator-=(Vector3 right) -> Vector3&
{
	X -= right.X;
	Y -= right.Y;
	Z -= right.Z;

	return *this;
}

constexpr
auto Pargon::Vector3::operator*=(float scalar) -> Vector3&
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;

	return *this;
}

constexpr
auto Pargon::Vector3::operator-() const -> Vector3
{
	return { -X, -Y, -Z };
}

constexpr
auto Pargon::Vector3::operator+(Vector3 right) const -> Vector3
{
	return { X + right.X, Y + right.Y, Z + right.Z };
}

constexpr
auto Pargon::Vector3::operator-(Vector3 right) const -> Vector3
{
	return { X - right.X, Y - right.Y, Z - right.Z };
}

constexpr
auto Pargon::Vector3::operator*(float scalar) const -> Vector3
{
	return { X * scalar, Y * scalar, Z * scalar };
}

constexpr
auto Pargon::Vector3::GetLengthSquared() const -> float
{
	return X * X + Y * Y + Z * Z;
}

constexpr
auto Pargon::Vector3::GetDotProduct(Vector3 vector) const -> float
{
	return X * vector.X + Y * vector.Y + Z * vector.Z;
}
