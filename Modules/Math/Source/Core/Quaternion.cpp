#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Arithmetic.h"
#include "Pargon/Math/Matrix.h"
#include "Pargon/Math/Quaternion.h"
#include "Pargon/Math/Rotation.h"
#include "Pargon/Math/Vector.h"
#include "Pargon/Serialization/BufferReader.h"
#include "Pargon/Serialization/BufferWriter.h"
#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"

#include <cml/cml.h>

using namespace Pargon;

auto Quaternion::CreateYaw(Rotation angle) -> Quaternion
{
	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion_rotation_euler(q, angle.InRadians(), 0.0f, 0.0f, cml::euler_order_yxz);

	return quaternion;
}

auto Quaternion::CreatePitch(Rotation angle) -> Quaternion
{
	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion_rotation_euler(q, 0.0f, angle.InRadians(), 0.0f, cml::euler_order_yxz);

	return quaternion;
}

auto Quaternion::CreateRoll(Rotation angle) -> Quaternion
{
	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion_rotation_euler(q, 0.0f, 0.0f, angle.InRadians(), cml::euler_order_yxz);

	return quaternion;
}

auto Quaternion::CreateFromAxisAngle(Vector3 axis, Rotation angle) -> Quaternion
{
	auto vector = cml::vector3f(axis.X, axis.Y, axis.Z);
	vector.normalize();

	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion_rotation_axis_angle(q, vector, angle.InRadians());

	return quaternion;
}

auto Quaternion::CreateFromEulerAngles(Rotation yaw, Rotation pitch, Rotation roll) -> Quaternion
{
	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion_rotation_euler(q, yaw.InRadians(), pitch.InRadians(), roll.InRadians(), cml::euler_order_yxz);

	return quaternion;
}

auto Quaternion::operator*=(Quaternion right) -> Quaternion&
{
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> l(&X);
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> r(&right.X);

	l = l * r;
	l.normalize();
	return *this;
}

auto Quaternion::operator*(Quaternion right) const -> Quaternion
{
	Quaternion result;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> l(const_cast<float*>(&X));
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> r(&right.X);
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&result.X);

	q = l * r;
	q.normalize();
	return result;
}

auto Quaternion::GetAxisAngle() const -> AxisAngle
{
	AxisAngle result;

	float radians;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(const_cast<float*>(&X));
	cml::vector<float, cml::external<3>> v(&result.Axis.X);
	cml::quaternion_to_axis_angle(q, v, radians);

	result.Angle = Angle::FromRadians(radians);
	return result;
}

auto Quaternion::GetEulerAngles() const -> EulerAngles
{
	float yaw, pitch, roll;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(const_cast<float*>(&X));
	cml::quaternion_to_euler(q, yaw, pitch, roll, cml::euler_order_yxz);

	return
	{
		Angle::FromRadians(yaw),
		Angle::FromRadians(pitch),
		Angle::FromRadians(roll)
	};
}

void Quaternion::Invert()
{
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&X);
	q.inverse();
	q.normalize();
}

void Quaternion::Yaw(Rotation angle)
{
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&X);
	cml::quaternion_rotate_about_local_y(q, angle.InRadians());
	q.normalize();
}

void Quaternion::Pitch(Rotation angle)
{
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&X);
	cml::quaternion_rotate_about_local_x(q, angle.InRadians());
	q.normalize();
}

void Quaternion::Roll(Rotation angle)
{
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&X);
	cml::quaternion_rotate_about_local_z(q, angle.InRadians());
	q.normalize();
}

void Quaternion::Interpolate(Quaternion to, float time)
{
	*this = Interpolated(to, time);
}

auto Quaternion::Inverted() const -> Quaternion
{
	auto copy = *this;
	copy.Invert();
	return copy;
}

auto Quaternion::Yawed(Rotation angle) const -> Quaternion
{
	auto copy = *this;
	copy.Yaw(angle);
	return copy;
}

auto Quaternion::Pitched(Rotation angle) const -> Quaternion
{
	auto copy = *this;
	copy.Pitch(angle);
	return copy;
}

auto Quaternion::Rolled(Rotation angle) const -> Quaternion
{
	auto copy = *this;
	copy.Roll(angle);
	return copy;
}

auto Quaternion::Interpolated(Quaternion to, float time) const -> Quaternion
{
	Quaternion quaternion;
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> q(&quaternion.X);
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> f(const_cast<float*>(&X));
	cml::quaternion<float, cml::external<>, cml::vector_first, cml::negative_cross> t(const_cast<float*>(&to.X));

	q = cml::slerp(f, t, time);
	return quaternion;
}

void Quaternion::ToBuffer(BufferWriter& writer) const
{
	writer.Write(X);
	writer.Write(Y);
	writer.Write(Z);
	writer.Write(W);
}

void Quaternion::FromBuffer(BufferReader& reader)
{
	reader.Read(X);
	reader.Read(Y);
	reader.Read(Z);
	reader.Read(W);
}

void Quaternion::ToString(StringWriter& writer, StringView format) const
{
	if (StartsWith(format, "euler", true))
	{
		auto angles = GetEulerAngles();
		auto angleFormat = format.GetSubview(6);

		writer.Write(angles.Yaw, angleFormat);
		writer.Write(" ");
		writer.Write(angles.Pitch, angleFormat);
		writer.Write(" ");
		writer.Write(angles.Roll, angleFormat);
	}
	else if (StartsWith(format, "axis", true))
	{
		auto axis = GetAxisAngle();
		auto angleFormat = format.GetSubview(5);

		writer.Write(axis.Axis, "");
		writer.Write(" ");
		writer.Write(axis.Angle, angleFormat);
	}
	else
	{
		writer.Format("{} {} {} {}", X, Y, Z, W);
	}
}

void Quaternion::FromString(StringReader& reader, StringView format)
{
	if (Equals(format, "euler", true))
	{
		Angle yaw, pitch, roll;

		if (reader.Parse("{} {} {}", yaw, pitch, roll))
			*this = CreateFromEulerAngles(yaw, pitch, roll);
	}
	else if (Equals(format, "axis", true))
	{
		Vector3 axis;
		Angle angle;

		if (reader.Parse("{} {}", axis, angle))
			*this = CreateFromAxisAngle(axis, angle);
	}
	else
	{
		if (!reader.Parse("{} {} {} {}", X, Y, Z, W))
			reader.ReportError("the string could not be read as a Quaternion (expected four floating point numbers separated by a space");
	}
}
