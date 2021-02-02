#pragma once

#include "Pargon/Math/Angle.h"
#include "Pargon/Math/Rotation.h"

namespace Pargon
{
	constexpr Angle Tau = 6.2831853_radians;
	constexpr Angle Pi = 3.1415927_radians;
	constexpr Angle PiOver2 = 1.5707963_radians;

	auto Sine(Rotation rotation) -> float;
	auto Cosine(Rotation rotation) -> float;
	auto Tangent(Rotation rotation) -> float;

	auto ArcSine(float value) -> Rotation;
	auto ArcCosine(float value) -> Rotation;
	auto ArcTangent(float x, float y) -> Rotation;
}
