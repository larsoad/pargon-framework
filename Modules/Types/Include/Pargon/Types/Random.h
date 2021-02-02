#pragma once

#include <limits>
#include <random>

namespace Pargon
{
	class StringReader;
	class StringWriter;

	class Random
	{
	public:
		Random();
		explicit Random(unsigned int seed);

		auto Seed() const -> unsigned int;
		void SetSeed(unsigned int seed);
		void ResetSeed();

		auto Generate(char min, char max = 127) -> char;
		auto Generate(int min, int max = std::numeric_limits<int>::max()) -> int;
		auto Generate(unsigned int min, unsigned int max = std::numeric_limits<unsigned int>::max()) -> unsigned int;
		auto Generate(float min, float max = 1.0f) -> float;
		auto Generate(double min, double max = 1.0) -> double;

		void ToString(StringWriter& writer) const;
		void FromString(StringReader& reader);

		auto operator==(const Random& other) const -> bool;
		auto operator!=(const Random& other) const -> bool;

	private:
		unsigned int _seed;
		std::mt19937 _generator;
	};

	template<typename T> auto Shuffle(Random& random, SequenceView<T> sequence) -> List<T>;
	template<typename T> void ShuffleInPlace(Random& random, SequenceReference<T> sequence);
}

inline
Pargon::Random::Random()
{
	ResetSeed();
}

inline
Pargon::Random::Random(unsigned int seed)
{
	SetSeed(seed);
}

inline
auto Pargon::Random::Seed() const -> unsigned int 
{
	return _seed;
}

inline
void Pargon::Random::SetSeed(unsigned int seed)
{
	_seed = seed;
	_generator.seed(_seed);
}

inline
auto Pargon::Random::operator==(const Random& other) const -> bool
{
	return _generator == other._generator;
}

inline
auto Pargon::Random::operator!=(const Random& other) const -> bool
{
	return !operator==(other);
}

template<typename T>
auto Pargon::Shuffle(Random& random, SequenceView<T> sequence) -> List<T>
{
	List<T> list = sequence;
	ShuffleInPlace<T>(random, list);
	return list;
}

template<typename T>
void Pargon::ShuffleInPlace(Random& random, SequenceReference<T> sequence)
{
	for (auto i = sequence.LastIndex(); i > 0; i--)
	{
		auto j = random.Generate(0, i);
		std::swap(sequence.Item(i), sequence.Item(j));
	}
}
