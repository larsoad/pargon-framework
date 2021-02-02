#include "TypesTests.h"
#include "Pargon/Types/Color.h"

using namespace Pargon;
using namespace Pargon::Testing;

namespace
{
	struct ColorContext : TestContext
	{
	};

	TestGroup ColorTests(TypesTests(), "Color");

	Test<> TestAsHex(ColorTests, "AsHex", [](TestContext& context)
	{
		context.AssertEqual(Black.AsHex(), 0u);
	});

	Test<ColorContext> TestAsHdr(ColorTests, "AsHdr", [](ColorContext& context)
	{
		//Assert(Black.AsHex() == 0u);
	});
}
