#include "Pargon/Math/Arithmetic.h"
#include "Pargon/Math/Matrix.h"
#include "Pargon/Math/Rotation.h"
#include "Pargon/Math/Trigonometry.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

#include <algorithm>
#include <cml/cml.h>

using namespace Pargon;

auto Matrix3x3::CreateRotation(Rotation angle) -> Matrix3x3
{
	auto sine = Sine(angle);
	auto cosine = Cosine(angle);

	return
	{
		cosine, -sine, 0.0f,
		sine, cosine, 0.0f,
		0.0f, 0.0f, 1.0f
	};
}

auto Matrix3x3::CreateTransform(Vector2 translation, Vector2 scale, Rotation angle, Vector2 offset) -> Matrix3x3
{
	auto matrix = CreateTranslation(-offset);
	matrix.Scale(scale);
	matrix.Rotate(angle);
	matrix.Translate(translation);

	return matrix;
}

auto Matrix3x3::operator==(const Matrix3x3& right) const -> bool
{
	return std::equal(Elements.begin(), Elements.end(), right.Elements.begin());
}

auto Matrix3x3::operator!=(const Matrix3x3& right) const -> bool
{
	return !operator==(right);
}

auto Matrix3x3::operator*=(const Matrix3x3& right) -> Matrix3x3&
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> l(Elements.begin());
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> r(const_cast<float*>(right.Elements.begin()));

	l *= r;
	return *this;
}

auto Matrix3x3::operator*(const Matrix3x3& right) const -> Matrix3x3
{
	Matrix3x3 matrix;
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(matrix.Elements.begin());
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> l(const_cast<float*>(Elements.begin()));
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> r(const_cast<float*>(right.Elements.begin()));

	m = l * r;
	return matrix;
}

auto Matrix3x3::Get(int row, int column) const -> float
{
	assert(row >= 0 && row < 3 && column >= 0 && column < 3);
	return Elements.Item(row * 3 + column);
}

void Matrix3x3::Set(int row, int column, float value)
{
	assert(row >= 0 && row < 3 && column >= 0 && column < 3);
	Elements.Item(row * 3 + column) = value;
}

auto Matrix3x3::GetDeterminant() const -> float
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	return cml::determinant(m);
}

auto Matrix3x3::GetTranslation() const -> Vector2
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	auto translation = cml::matrix_get_translation_2D(m);

	return { translation[0], translation[1] };
}

auto Matrix3x3::GetRotation() const -> Angle
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	auto rotation = cml::matrix_to_rotation_2D(m);

	return Angle::FromRadians(rotation);
}

auto Matrix3x3::GetScale() const -> Vector2
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	float width, height, angle;
	cml::vector2f translation;
	cml::matrix_decompose_SRT_2D(m, width, height, angle, translation);

	return { width, height };
}

auto Matrix3x3::GetTransform() const -> Transform
{
	float radians;
	Transform transform;

	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	cml::vector<float, cml::external<2>> v(&transform.Translation.X);
	cml::matrix_decompose_SRT_2D(m, transform.Scale.X, transform.Scale.Y, radians, v);

	transform.Rotation = Angle::FromRadians(radians);

	return transform;
}

auto Matrix3x3::Get4x4() const -> Matrix4x4
{
	return
	{
		Elements.Item(0), Elements.Item(1), 0, Elements.Item(2),
		Elements.Item(3), Elements.Item(4), 0, Elements.Item(5),
		0, 0, 1, 0,
		Elements.Item(6), Elements.Item(7), 0, Elements.Item(8)
	};
}

void Matrix3x3::Invert()
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(Elements.begin());
	m.inverse();
}

void Matrix3x3::Transpose()
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(Elements.begin());
	m = transpose(m);
}

void Matrix3x3::Translate(Vector2 translation)
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(Elements.begin());
	cml::matrix33f_r result;
	cml::matrix_translation_2D(result, translation.X, translation.Y);

	m *= result;
}

void Matrix3x3::Scale(Vector2 scale)
{
	Elements.Item(0) *= scale.X;
	Elements.Item(3) *= scale.X;
	Elements.Item(6) *= scale.X;
	Elements.Item(1) *= scale.Y;
	Elements.Item(4) *= scale.Y;
	Elements.Item(7) *= scale.Y;
}

void Matrix3x3::Rotate(Rotation angle)
{
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(Elements.begin());
	cml::matrix33f_r rotation;
	cml::matrix_rotation_2D(rotation, angle.InRadians());

	m *= rotation;
}

auto Matrix3x3::Inverted() const -> Matrix3x3
{
	auto copy = *this;
	copy.Invert();
	return copy;
}

auto Matrix3x3::Transposed() const -> Matrix3x3
{
	auto copy = *this;
	copy.Transpose();
	return copy;
}

auto Matrix3x3::Translated(Vector2 translation) const -> Matrix3x3
{
	auto copy = *this;
	copy.Translate(translation);
	return copy;
}

auto Matrix3x3::Scaled(Vector2 scale) const -> Matrix3x3
{
	auto copy = *this;
	copy.Scale(scale);
	return copy;
}

auto Matrix3x3::Rotated(Rotation angle) const -> Matrix3x3
{
	auto copy = *this;
	copy.Rotate(angle);
	return copy;
}

void Matrix3x3::ToBuffer(BufferWriter& writer) const
{
	writer.Write(Elements);
}

void Matrix3x3::FromBuffer(BufferReader& reader)
{
	reader.Read(Elements);
}

void Matrix3x3::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(Elements, format);
}

void Matrix3x3::FromString(StringReader& reader, StringView format)
{
	reader.Read(Elements, format);
}

auto Matrix4x4::CreateRotation(Quaternion rotation) -> Matrix4x4
{
	Matrix4x4 matrix;
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(matrix.Elements.begin());
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(const_cast<float*>(&rotation.X));
	cml::matrix_rotation_quaternion(m, q);

	return matrix;
}

auto Matrix4x4::CreateTransform(Vector3 translation, Vector3 scale, Quaternion rotation, Vector3 offset) -> Matrix4x4
{
	auto matrix = CreateTranslation(-offset);
	matrix.Scale(scale);
	matrix.Rotate(rotation);
	matrix.Translate(translation + offset);

	return matrix;
}

auto Matrix4x4::CreatePerspectiveProjection(Angle angle, float aspectRatio, float nearPlane, float farPlane) -> Matrix4x4
{
	Matrix4x4 matrix;
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(matrix.Elements.begin());
	cml::matrix_perspective_xfov_LH(m, angle.InRadians(), aspectRatio, nearPlane, farPlane, cml::z_clip_zero);

	return matrix;
}

auto Matrix4x4::CreateOrthographicProjection(float width, float height, float depth) -> Matrix4x4
{
	Matrix4x4 matrix;
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(matrix.Elements.begin());
	cml::matrix_orthographic_LH(m, 0.0f, width, 0.0f, height, 0.0f, depth, cml::z_clip_zero);

	return matrix;
}

auto Matrix4x4::operator==(const Matrix4x4& right) const -> bool
{
	return std::equal(Elements.begin(), Elements.end(), right.Elements.begin());
}

auto Matrix4x4::operator!=(const Matrix4x4& right) const -> bool
{
	return !operator==(right);
}

auto Matrix4x4::operator*=(const Matrix4x4& right) -> Matrix4x4&
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> l(Elements.begin());
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> r(const_cast<float*>(right.Elements.begin()));

	l *= r;
	return *this;
}

auto Matrix4x4::operator*(const Matrix4x4& right) const -> Matrix4x4
{
	Matrix4x4 matrix;
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(matrix.Elements.begin());
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> l(const_cast<float*>(Elements.begin()));
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> r(const_cast<float*>(right.Elements.begin()));

	m = l * r;
	return matrix;
}

auto Matrix4x4::Get(int row, int column) const -> float
{
	assert(row >= 0 && row < 4 && column >= 0 && column < 4);
	return Elements.Item(row * 4 + column);
}

void Matrix4x4::Set(int row, int column, float value)
{
	assert(row >= 0 && row < 4 && column >= 0 && column < 4);
	Elements.Item(row * 4 + column) = value;
}

auto Matrix4x4::GetDeterminant() const -> float
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	return cml::determinant(m);
}

auto Matrix4x4::GetTranslation() const -> Vector3
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	auto result = cml::matrix_get_translation(m);

	return { result[0], result[1], result[2] };
}

auto Matrix4x4::GetScale() const -> Vector3
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	cml::vector3f translation;
	cml::quaternionf_n quaternion;

	Vector3 scale;
	cml::matrix_decompose_SRT(m, scale.X, scale.Y, scale.Z, quaternion, translation);

	return scale;
}

auto Matrix4x4::GetRotation() const -> Quaternion
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	cml::quaternionf_n quaternion;
	cml::vector3f translation, scale;
	cml::matrix_decompose_SRT(m, scale[0], scale[1], scale[2], quaternion, translation);

	return 
	{
		quaternion[0],
		quaternion[1],
		quaternion[2],
		quaternion[3]
	};
}

auto Matrix4x4::GetTransform() const -> Transform
{
	Transform transform;

	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(Elements.begin()));
	cml::quaternionf_n q;
	cml::vector3f t;

	cml::matrix_decompose_SRT(m, transform.Scale.X, transform.Scale.Y, transform.Scale.Z, q, t);

	transform.Translation.X = t[0];
	transform.Translation.Y = t[1];
	transform.Translation.Z = t[2];

	transform.Rotation.X = q[0];
	transform.Rotation.Y = q[1];
	transform.Rotation.Z = q[2];
	transform.Rotation.W = q[3];

	return transform;
}

auto Matrix4x4::Get3x3() const -> Matrix3x3
{
	return
	{
		Elements.Item(0), Elements.Item(1), Elements.Item(3),
		Elements.Item(4), Elements.Item(5), Elements.Item(7),
		Elements.Item(12), Elements.Item(13), Elements.Item(15)
	};
}

void Matrix4x4::Invert()
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> matrix(Elements.begin());
	matrix.inverse();
}

void Matrix4x4::Transpose()
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> matrix(Elements.begin());
	matrix = transpose(matrix);
}

void Matrix4x4::Translate(Vector3 translation)
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> matrix(Elements.begin());
	cml::matrix44f_r result;
	cml::matrix_translation(result, translation.X, translation.Y, translation.Z);

	matrix *= result;
}

void Matrix4x4::Scale(Vector3 scale)
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> matrix(Elements.begin());
	cml::matrix44f_r result;
	cml::matrix_scale(result, scale.X, scale.Y, scale.Z);

	matrix *= result;
}

void Matrix4x4::Rotate(Quaternion rotation)
{
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> matrix(Elements.begin());
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(const_cast<float*>(&rotation.X));
	cml::matrix44f_r result;
	cml::matrix_rotation_quaternion(result, q);

	matrix *= result;
}

auto Matrix4x4::Inverted() const -> Matrix4x4
{
	auto copy = *this;
	copy.Invert();
	return copy;
}

auto Matrix4x4::Transposed() const -> Matrix4x4
{
	auto copy = *this;
	copy.Transpose();
	return copy;
}

auto Matrix4x4::Translated(Vector3 translation) const -> Matrix4x4
{
	auto copy = *this;
	copy.Translate(translation);
	return copy;
}

auto Matrix4x4::Scaled(Vector3 scale) const -> Matrix4x4
{
	auto copy = *this;
	copy.Scale(scale);
	return copy;
}

auto Matrix4x4::Rotated(Quaternion rotation) const -> Matrix4x4
{
	auto copy = *this;
	copy.Rotate(rotation);
	return copy;
}

void Matrix4x4::ToBuffer(BufferWriter& writer) const
{
	writer.Write(Elements);
}

void Matrix4x4::FromBuffer(BufferReader& reader)
{
	reader.Read(Elements);
}

void Matrix4x4::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(Elements, format);
}

void Matrix4x4::FromString(StringReader& reader, StringView format)
{
	reader.Read(Elements, format);
}
