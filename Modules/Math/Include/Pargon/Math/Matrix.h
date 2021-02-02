#pragma once

#include "Pargon/Containers/Array.h"
#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Quaternion.h"
#include "Pargon/Math/Vector.h"

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class Matrix4x4;
	class Quaternion;
	class Rotation;
	class StringReader;
	class StringWriter;

	class Matrix3x3
	{
	public:
		struct Transform
		{
			Vector2 Translation;
			Vector2 Scale;
			Angle Rotation;
		};

		static constexpr auto CreateIdentity() -> Matrix3x3;
		static constexpr auto CreateTranslation(Vector2 translation) -> Matrix3x3;
		static constexpr auto CreateScale(Vector2 scale) -> Matrix3x3;
		static auto CreateRotation(Rotation angle) -> Matrix3x3;
		static auto CreateTransform(Vector2 position, Vector2 scale, Rotation angle, Vector2 offset) -> Matrix3x3;
			
		constexpr Matrix3x3() = default;
		constexpr Matrix3x3(float row1column1, float row1column2, float row1column3, float row2column1, float row2column2, float row2column3, float row3column1, float row3column2, float row3column3);

		Array<float, 9> Elements;

		auto operator==(const Matrix3x3& right) const -> bool;
		auto operator!=(const Matrix3x3& right) const -> bool;
		auto operator*=(const Matrix3x3& right) -> Matrix3x3&;
		auto operator*(const Matrix3x3& right) const -> Matrix3x3;

		auto Get(int row, int column) const -> float;
		void Set(int row, int column, float value);

		auto GetDeterminant() const -> float;
		auto GetTranslation() const -> Vector2;
		auto GetRotation() const -> Angle;
		auto GetScale() const -> Vector2;
		auto GetTransform() const -> Transform;
		auto Get4x4() const -> Matrix4x4;

		void Invert();
		void Transpose();
		void Translate(Vector2 translation);
		void Scale(Vector2 scale);
		void Rotate(Rotation angle);

		auto Inverted() const -> Matrix3x3;
		auto Transposed() const -> Matrix3x3;
		auto Translated(Vector2 translation) const -> Matrix3x3;
		auto Scaled(Vector2 scale) const -> Matrix3x3;
		auto Rotated(Rotation angle) const -> Matrix3x3;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};

	class Matrix4x4
	{
	public:
		struct Transform
		{
			Vector3 Translation;
			Vector3 Scale;
			Quaternion Rotation;
		};

		static constexpr auto CreateIdentity() -> Matrix4x4;
		static constexpr auto CreateTranslation(Vector3 translation) -> Matrix4x4;
		static constexpr auto CreateScale(Vector3 scale) -> Matrix4x4;
		static auto CreateRotation(Quaternion rotation) -> Matrix4x4;
		static auto CreateTransform(Vector3 translation, Vector3 scale, Quaternion rotation, Vector3 offset) -> Matrix4x4;
		static auto CreatePerspectiveProjection(Angle fieldOfView, float aspectRatio, float nearPlane, float farPlane) -> Matrix4x4;
		static auto CreateOrthographicProjection(float width, float height, float depth) -> Matrix4x4;

		constexpr Matrix4x4() = default;
		constexpr Matrix4x4(float row1column1, float row1column2, float row1column3, float row1column4, float row2column1, float row2column2, float row2column3, float row2column4, float row3column1, float row3column2, float row3column3, float row3column4, float row4column1, float row4column2, float row4column3, float row4column4);

		Array<float, 16> Elements;

		auto operator==(const Matrix4x4& right) const -> bool;
		auto operator!=(const Matrix4x4& right) const -> bool;
		auto operator*=(const Matrix4x4& right) -> Matrix4x4&;
		auto operator*(const Matrix4x4& right) const -> Matrix4x4;

		auto Get(int row, int column) const -> float;
		void Set(int row, int column, float value);

		auto GetDeterminant() const -> float;
		auto GetTranslation() const -> Vector3;
		auto GetScale() const -> Vector3;
		auto GetRotation() const -> Quaternion;
		auto GetTransform() const -> Transform;
		auto Get3x3() const -> Matrix3x3;

		void Transpose();
		void Invert();
		void Translate(Vector3 translation);
		void Scale(Vector3 scale);
		void Rotate(Quaternion rotation);

		auto Transposed() const -> Matrix4x4;
		auto Inverted() const -> Matrix4x4;
		auto Translated(Vector3 translation) const -> Matrix4x4;
		auto Scaled(Vector3 scale) const -> Matrix4x4;
		auto Rotated(Quaternion rotation) const -> Matrix4x4;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};
}

constexpr
auto Pargon::Matrix3x3::CreateIdentity() -> Matrix3x3
{
	return
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
}

constexpr
auto Pargon::Matrix3x3::CreateTranslation(Vector2 translation) -> Matrix3x3
{
	return
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		translation.X, translation.Y, 1.0f
	};
}

constexpr
auto Pargon::Matrix3x3::CreateScale(Vector2 scale) -> Matrix3x3
{
	return
	{
		scale.X, 0.0f, 0.0f,
		0.0f, scale.Y, 0.0f,
		0.0f, 0.0f, 1.0f
	};
}

constexpr
Pargon::Matrix3x3::Matrix3x3(float row1column1, float row1column2, float row1column3, float row2column1, float row2column2, float row2column3, float row3column1, float row3column2, float row3column3) :
	Elements{{ row1column1, row1column2, row1column3, row2column1, row2column2, row2column3, row3column1, row3column2, row3column3 }}
{
}

constexpr
auto Pargon::Matrix4x4::CreateIdentity() -> Matrix4x4
{
	return
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

constexpr
auto Pargon::Matrix4x4::CreateTranslation(Vector3 translation) -> Matrix4x4
{
	return
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		translation.X, translation.Y, translation.Z, 1.0f
	};
}

constexpr
auto Pargon::Matrix4x4::CreateScale(Vector3 scale) -> Matrix4x4
{
	return
	{
		scale.X, 0.0f, 0.0f, 0.0f,
		0.0f, scale.Y, 0.0f, 0.0f,
		0.0f, 0.0f, scale.Z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

constexpr
Pargon::Matrix4x4::Matrix4x4(float row1column1, float row1column2, float row1column3, float row1column4, float row2column1, float row2column2, float row2column3, float row2column4, float row3column1, float row3column2, float row3column3, float row3column4, float row4column1, float row4column2, float row4column3, float row4column4) :
	Elements{{ row1column1, row1column2, row1column3, row1column4, row2column1, row2column2, row2column3, row2column4, row3column1, row3column2, row3column3, row3column4, row4column1, row4column2, row4column3, row4column4 }}
{
}
