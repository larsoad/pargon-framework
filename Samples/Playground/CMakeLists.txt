set(SOURCES
)

set(WIN32_SOURCES
	Main.Win32.cpp
)

set(MODULES
	PargonShim
	PargonDebugging
)

if(IS_WINDOWS)
	list(APPEND SOURCES ${WIN32_SOURCES})
endif()

add_pargon_application(Playground "${SOURCES}" "${MODULES}")
