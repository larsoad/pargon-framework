set(INCLUDES
	Pargon/Debugging.h
	Pargon/Debugging/Log.h
	Pargon/Debugging/StackTrace.h
)

set(SOURCES
	Core/Log.cpp
	Core/StackTrace.cpp
)

set(WIN32_INCLUDES
	Pargon/Debugging.Win32.h
	Pargon/Debugging/Log.Win32.h
)

set(WIN32_SOURCES
	Win32/Log.Win32.cpp
	Win32/StackTrace.Win32.cpp
)

set(LIBRARIES
	PargonShim
)

set(TESTS
	LogTests.cpp
)

if (IS_WINDOWS)
	list(APPEND INCLUDES ${WIN32_INCLUDES})
	list(APPEND SOURCES ${WIN32_SOURCES})
	list(APPEND LIBRARIES Dbghelp)
endif()

add_pargon_module(PargonDebugging "${INCLUDES}" "${SOURCES}" "${LIBRARIES}" "${TESTS}")
