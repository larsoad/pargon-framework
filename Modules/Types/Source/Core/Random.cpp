#include "Pargon/Serialization/StringReader.h"
#include "Pargon/Serialization/StringWriter.h"
#include "Pargon/Types/Random.h"

#include <chrono>
#include <cmath>

using namespace Pargon;

void Random::ResetSeed()
{
	_seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
	_generator.seed(_seed);
}

namespace
{
	template<typename T>
	auto DistributeFloatingPoint(std::mt19937& generator, T min, T max) -> T
	{
		auto scale = (max - min) / (generator.max() - generator.min() + 1.0f);
		return static_cast<T>((generator() - generator.min()) * scale + min);
	}

	template<typename T>
	auto DistributeIntegral(std::mt19937& generator, T min, T max) -> T
	{
		auto scale = (max - min) / (generator.max() - generator.min() + 1.0f);
		return static_cast<T>(std::round((generator() - generator.min()) * scale + min));
	}
}

auto Random::Generate(char min, char max) -> char
{
	return DistributeIntegral(_generator, min, max);
}

auto Random::Generate(int min, int max) -> int
{
	return DistributeIntegral(_generator, min, max);
}

auto Random::Generate(unsigned int min, unsigned int max) -> unsigned int
{
	return DistributeIntegral(_generator, min, max);
}

auto Random::Generate(float min, float max) -> float
{
	return DistributeFloatingPoint(_generator, min, max);
}

auto Random::Generate(double min, double max) -> double
{
	return DistributeFloatingPoint(_generator, min, max);
}

void Random::ToString(StringWriter& writer) const
{
	writer.Format("Seed({})", _seed);
}

void Random::FromString(StringReader& reader)
{
	unsigned int seed;
	if (reader.Parse("Seed({})", seed))
		SetSeed(seed);
}
