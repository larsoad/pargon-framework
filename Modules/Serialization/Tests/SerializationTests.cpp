#include "SerializationTests.h"

using namespace Pargon::Testing;

namespace
{
}

auto SerializationSuite() -> TestGroup&
{
	static auto _group = TestGroup("Serialization");
	return _group;
}

auto SerializersSuite() -> TestGroup&
{
	static auto _group = TestGroup("Serializers", SerializationSuite());
	return _group;
}

auto FundamentalSerializersSuite() -> TestGroup&
{
	static auto _group = TestGroup("Fundamental", SerializersSuite());
	return _group;
}

auto StlSerializersSuite() -> TestGroup&
{
	static auto _group = TestGroup("Stl", SerializationSuite());
	return _group;
}
