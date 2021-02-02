#include "SerializationTests.h"

using namespace Pargon;
using namespace Pargon::Testing;
using namespace Pargon::Testing::Matchers;

namespace
{
	struct Context : TestContext
	{
		bool Value;

		auto Next(int iteration) -> bool override
		{
			Value = iteration == 0;
			return iteration < 2;
		}
	};

	struct Tests : TestGroup
	{
		Tests() : TestGroup("Bool", FundamentalSerializersSuite())
		{
			Add("Write to Buffer", &Tests::TestWriteToBuffer);
			Add("Read from Buffer", &Tests::TestReadFromBuffer);
		}

		void TestWriteToBuffer(Context& context)
		{
			auto writer = BlueprintWriter();
			writer.WriteBoolean(context.Value);

			Require("IsBoolean", [&] { return writer.ViewBlueprint().IsBoolean(); }, IsEqualTo(true));
			Check("AsBoolean", [&] { return writer.ViewBlueprint().AsBoolean(); }, IsEqualTo(context.Value));

			Check("Something", [&] { throw std::exception(); }, Throws<std::exception>());
		}

		void TestReadFromBuffer(Context& context)
		{
			auto buffer = Buffer();
			buffer.Append(context.Value ? 1 : 0);
			auto reader = BufferReader(buffer, NativeEndian);

			bool value;
			Serializer<bool>().Serialize(reader, value);

			Check("Serialize(BufferReader, bool)", value, IsEqualTo(context.Value));
		}

	} _tests;
}
