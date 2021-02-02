set(INCLUDES
	Pargon/Testing.h
	Pargon/Testing/TestContext.h
	Pargon/Testing/TestGroup.h
	Pargon/Testing/TestMatcher.h
	Pargon/Testing/TestResult.h
	Pargon/Testing/Matchers/IsCloseToMatcher.h
	Pargon/Testing/Matchers/IsEqualToMatcher.h
	Pargon/Testing/Matchers/IsGreaterThanMatcher.h
	Pargon/Testing/Matchers/IsGreaterThanOrEqualToMatcher.h
	Pargon/Testing/Matchers/IsInequalToMatcher.h
	Pargon/Testing/Matchers/IsLessThanMatcher.h
	Pargon/Testing/Matchers/IsLessThanOrEqualToMatcher.h
	Pargon/Testing/Matchers/MatchesMatcher.h
	Pargon/Testing/Matchers/ThrowsMatcher.h
)

set(SOURCES
	Core/TestGroup.cpp
)

set(LIBRARIES
	PargonShim
)

add_pargon_module(PargonTesting "${INCLUDES}" "${SOURCES}" "${LIBRARIES}" "")
