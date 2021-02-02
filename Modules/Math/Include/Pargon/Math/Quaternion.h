#pragma once

#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Vector.h"

namespace Pargon
{
	class BufferReader;
	class BufferWriter;
	class Matrix4x4;
	class Rotation;
	class StringReader;
	class StringView;
	class StringWriter;

	class Quaternion
	{
	public:
		struct AxisAngle
		{
			Angle Angle;
			Vector3 Axis;
		};

		struct EulerAngles
		{
			Angle Yaw;
			Angle Pitch;
			Angle Roll;
		};

		static constexpr auto CreateIdentity() -> Quaternion;
		static auto CreateYaw(Rotation angle) -> Quaternion;
		static auto CreatePitch(Rotation angle) -> Quaternion;
		static auto CreateRoll(Rotation angle) -> Quaternion;
		static auto CreateFromAxisAngle(Vector3 axis, Rotation angle) -> Quaternion;
		static auto CreateFromEulerAngles(Rotation yaw, Rotation pitch, Rotation roll) -> Quaternion;

		float X;
		float Y;
		float Z;
		float W;

		constexpr auto operator==(const Quaternion& right) const -> bool;
		constexpr auto operator!=(const Quaternion& right) const -> bool;

		auto operator*=(Quaternion right) -> Quaternion&;
		auto operator*(Quaternion right) const -> Quaternion;

		auto GetAxisAngle() const -> AxisAngle;
		auto GetEulerAngles() const -> EulerAngles;

		void Invert();
		void Yaw(Rotation angle);
		void Pitch(Rotation angle);
		void Roll(Rotation angle);
		void Interpolate(Quaternion to, float time);

		auto Inverted() const -> Quaternion;
		auto Yawed(Rotation angle) const -> Quaternion;
		auto Pitched(Rotation angle) const -> Quaternion;
		auto Rolled(Rotation angle) const -> Quaternion;
		auto Interpolated(Quaternion to, float time) const -> Quaternion;

		void ToBuffer(BufferWriter& writer) const;
		void FromBuffer(BufferReader& reader);
		void ToString(StringWriter& writer, StringView format) const;
		void FromString(StringReader& reader, StringView format);
	};
}

constexpr
auto Pargon::Quaternion::CreateIdentity() -> Quaternion
{
	return { 0.0f, 0.0f, 0.0f, 1.0f };
}

constexpr
auto Pargon::Quaternion::operator==(const Quaternion& right) const -> bool
{
	return X == right.X
		&& Y == right.Y
		&& Z == right.Z
		&& W == right.W;
}

constexpr
auto Pargon::Quaternion::operator!=(const Quaternion& right) const -> bool
{
	return !operator==(right);
}
