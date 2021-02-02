#include "Pargon/Math/Matrix.h"
#include "Pargon/Math/Point.h"
#include "Pargon/Math/Vector.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

#include <cml/cml.h>

using namespace Pargon;

auto Point2::operator*=(const Matrix3x3& transform) -> Point2&
{
	*this = *this * transform;
	return *this;
}

auto Point2::operator*(const Matrix3x3& transform) const -> Point2
{
	cml::vector<float, cml::external<2>> vector(const_cast<float*>(&X));
	cml::matrix<float, cml::external<3, 3>, cml::row_basis, cml::row_major> m(const_cast<float*>(transform.Elements.begin()));

	auto result = cml::transform_point_2D(m, vector);
	return { result[0], result[1] };
}

auto Point2::AsOffset() const -> Vector2
{
	return { X, Y };
}

void Point2::ToBuffer(BufferWriter& writer) const
{
	writer.Write(X);
	writer.Write(Y);
}

void Point2::FromBuffer(BufferReader& reader)
{
	reader.Read(X);
	reader.Read(Y);
}

void Point2::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(X, format);
	writer.Write(",");
	writer.Write(Y, format);
}

namespace
{
	auto _point2Parse = ParseFormatString("{}{-|/\\s*,?\\s*/}{}");
}

void Point2::FromString(StringReader& reader, StringView format)
{
	if (!reader.Parse(_point2Parse, X, Y))
		reader.ReportError("the string could not be read as a Point2 (expected two floating point numbers separated by whitespace and/or a comma)");
}

auto Point3::operator*=(const Matrix4x4& transform) -> Point3&
{
	*this = *this * transform;
	return *this;
}

auto Point3::operator*(const Matrix4x4& transform) const -> Point3
{
	cml::vector<float, cml::external<3>> vector(const_cast<float*>(&X));
	cml::matrix<float, cml::external<4, 4>, cml::row_basis, cml::row_major> m(const_cast<float*>(transform.Elements.begin()));

	auto result = cml::transform_point_4D(m, vector);
	return { result[0], result[1], result[2] };
}

auto Point3::AsOffset() const -> Vector3
{
	return { X, Y, Z };
}

void Point3::ToBuffer(BufferWriter& writer) const
{
	writer.Write(X);
	writer.Write(Y);
	writer.Write(Z);
}

void Point3::FromBuffer(BufferReader& reader)
{
	reader.Read(X);
	reader.Read(Y);
	reader.Read(Z);
}

void Point3::ToString(StringWriter& writer, StringView format) const
{
	writer.Write(X, format);
	writer.Write(",");
	writer.Write(Y, format);
	writer.Write(",");
	writer.Write(Z, format);
}

namespace
{
	auto _point3Parse = ParseFormatString("{}{-|/\\s*,?\\s*/}{}{-|/\\s*,?\\s*/}{}");
}

void Point3::FromString(StringReader& reader, StringView format)
{
	if (!reader.Parse(_point3Parse, X, Y, Z))
		reader.ReportError("the string could not be read as a Point3 (expected three floating point numbers separated by whitespace and/or a comma)");
}
