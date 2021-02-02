#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Arithmetic.h"
#include "Pargon/Math/Matrix.h"
#include "Pargon/Math/Quaternion.h"
#include "Pargon/Math/Trigonometry.h"
#include "Pargon/Math/Vector.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

#include <cml/cml.h>

using namespace Pargon;

auto Vector2::CreateNormalized(float x, float y) -> Vector2
{
	return Vector2{ x, y }.Normalized();
}

auto Vector2::CreateFromDirection(Angle angle) -> Vector2
{
	return Vector2{ Cosine(angle), Sine(angle) };
}

auto Vector2::operator*=(const Matrix3x3& transform) -> Vector2&
{
	*this = *this * transform;
	return *this;
}

auto Vector2::operator*(const Matrix3x3& transform) const -> Vector2
{
	cml::vector<float, cml::external<2>> vector(const_cast<float*>(&X));
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(transform.Elements.begin()));

	auto result = cml::transform_vector_2D(m, vector);
	return { result[0], result[1] };
}

auto Vector2::GetLength() const -> float
{
	return SquareRoot(X * X + Y * Y);
}

auto Vector2::GetOrientation() const -> Angle
{
	return Angle::FromRadians(atan2(Y, X));
}

auto Vector2::GetPerpendicular() const -> Vector2
{
	return { -Y, X };
}

auto Vector2::GetNormal() const -> Vector2
{
	return GetPerpendicular().Normalized();
}

void Vector2::Normalize()
{
	cml::vector<float, cml::external<2>> vector(&X);
	vector.normalize();
}

void Vector2::Reflect(Vector2 normal, float restitution)
{
	*this = Reflected(normal, restitution);
}

void Vector2::Rotate(Angle angle)
{
	*this = Rotated(angle);
}

auto Vector2::Normalized() const -> Vector2
{
	cml::vector2f vector(X, Y);
	vector.normalize();
	return { vector[0], vector[1] };
}

auto Vector2::Reflected(Vector2 normal, float restitution) const -> Vector2
{
	auto difference = normal * GetDotProduct(normal);
	return *this + -difference * (1.0f + restitution);
}

auto Vector2::Rotated(Angle angle) const -> Vector2
{
	cml::vector<float, cml::external<2>> vector(const_cast<float*>(&X));
	auto result = cml::rotate_vector_2D(vector, angle.InRadians());
	return { result[0], result[1] };
}

void Vector2::ToBuffer(BufferWriter& writer) const
{
	writer.Write(X);
	writer.Write(Y);
}

void Vector2::FromBuffer(BufferReader& reader)
{
	reader.Read(X);
	reader.Read(Y);
}

void Vector2::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(X, format);
	writer.Write(",");
	writer.Write(Y, format);
}

namespace
{
	auto _vector2Parse = ParseFormatString("{}{-|/\\s*,?\\s*/}{}");
}

void Vector2::FromString(StringReader& reader, StringView format)
{
	if (!reader.Parse(_vector2Parse, X, Y))
		reader.ReportError("the string could not be read as a Vector2 (expected two floating point numbers separated by whitespace and/or a comma)");
}

auto Vector3::CreateNormalized(float x, float y, float z) -> Vector3
{
	return Vector3{ x, y, z }.Normalized();
}

auto Vector3::CreateFromDirection(Quaternion rotation) -> Vector3
{
	return Vector3{ 1.0f, 0.0f, 0.0f }.Rotated(rotation);
}

auto Vector3::operator*=(const Matrix4x4& transform) -> Vector3&
{
	*this = *this * transform;
	return *this;
}

auto Vector3::operator*(const Matrix4x4& transform) const -> Vector3
{
	cml::vector<float, cml::external<3>> vector(const_cast<float*>(&X));
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(transform.Elements.begin()));

	auto result = cml::transform_vector(m, vector);
	return { result[0], result[1], result[2] };
}

auto Vector3::GetLength() const -> float
{
	return SquareRoot(X * X + Y * Y + Z * Z);
}

auto Vector3::GetOrientation() const -> Quaternion
{
	Quaternion orientation;

	cml::vector<float, cml::external<3>> vector(const_cast<float*>(&X));
	cml::vector3f zero(0.0f, 0.0f, 0.0f);
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&orientation.X);

	cml::quaternion_rotation_aim_at(q, zero, vector);

	return orientation;
}

auto Vector3::GetCrossProduct(Vector3 vector) const -> Vector3
{
	cml::vector<float, cml::external<3>> from(const_cast<float*>(&X));
	cml::vector<float, cml::external<3>> to(const_cast<float*>(&vector.X));

	auto result = cml::cross(from, to);
	return { result[0], result[1], result[2] };
}

void Vector3::Normalize()
{
	cml::vector<float, cml::external<3>> vector(const_cast<float*>(&X));
	vector.normalize();
}

void Vector3::Reflect(Vector3 normal, float restitution)
{
	*this = Reflected(normal, restitution);
}

void Vector3::Rotate(Quaternion rotation)
{
	*this = Rotated(rotation);
}

void Vector3::RotateAbout(Vector3 axis, Angle angle)
{
	*this = RotatedAbout(axis, angle);
}

auto Vector3::Normalized() const -> Vector3
{
	cml::vector3f vector(X, Y, Z);
	vector.normalize();
	return { vector[0], vector[1], vector[2] };
}

auto Vector3::Reflected(Vector3 normal, float restitution) const -> Vector3
{
	auto difference = normal * GetDotProduct(normal);
	return *this + -difference * (1.0f + restitution);
}

auto Vector3::Rotated(Quaternion rotation) const -> Vector3
{
	auto matrix = Matrix4x4::CreateRotation(rotation);
	return *this * matrix;
}

auto Vector3::RotatedAbout(Vector3 axis, Angle angle) const -> Vector3
{
	axis.Normalize();

	cml::vector<float, cml::external<3>> vector(const_cast<float*>(&X));
	cml::vector<float, cml::external<3>> a(&axis.X);

	auto result = cml::rotate_vector(vector, a, angle.InRadians());
	return { result[0], result[1], result[2] };
}

void Vector3::ToBuffer(BufferWriter& writer) const
{
	writer.Write(X);
	writer.Write(Y);
	writer.Write(Z);
}

void Vector3::FromBuffer(BufferReader& reader)
{
	reader.Read(X);
	reader.Read(Y);
	reader.Read(Z);
}

void Vector3::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(X, format);
	writer.Write(",");
	writer.Write(Y, format);
	writer.Write(",");
	writer.Write(Z, format);
}

namespace
{
	auto _vector3Parse = ParseFormatString("{}{-|/\\s*,?\\s*/}{}{-|/\\s*,?\\s*/}{}");
}

void Vector3::FromString(StringReader& reader, StringView format)
{
	if (!reader.Parse(_vector3Parse, X, Y, Z))
		reader.ReportError("the string could not be read as a Vector3 (expected three floating point numbers separated by whitespace and/or a comma)");
}
