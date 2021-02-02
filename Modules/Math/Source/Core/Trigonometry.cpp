#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Trigonometry.h"

#include <cmath>
#include <cml/cml.h>

auto Pargon::Sine(Rotation rotation) -> float
{
	return std::sin(rotation.InRadians());
}

auto Pargon::Cosine(Rotation rotation) -> float
{
	return std::cos(rotation.InRadians());
}

auto Pargon::Tangent(Rotation rotation) -> float
{
	return std::tan(rotation.InRadians());
}

auto Pargon::ArcSine(float value) -> Rotation
{
	return Rotation::FromRadians(cml::asin_safe(value));
}

auto Pargon::ArcCosine(float value) -> Rotation
{
	return Rotation::FromRadians(cml::acos_safe(value));
}

auto Pargon::ArcTangent(float x, float y) -> Rotation
{
	if (x == 0.0f && y == 0.0f)
		return Rotation::FromRadians(0.0f);

	return Rotation::FromRadians(std::atan2(y, x));
}
