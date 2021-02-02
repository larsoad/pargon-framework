set(MODULE_NAME Types)

set(INCLUDES
	Types.h
)

set(HEADERS
	Color.h
	Guid.h
	Random.h
	Time.h
)

set(SOURCES
	Core/Color.cpp
	Core/Guid.cpp
	Core/Random.cpp
	Core/Time.cpp
)

set(MODULES
	Containers
	Serialization
)

set(DEPENDENCIES
)

set(WIN32_SOURCES
	Win32/Guid.Win32.cpp
	Win32/Time.Win32.cpp
)

set(TESTS
	TypesTests.h
	TypesTests.cpp
	ColorTests.cpp
)

set(TARGET_NAME ${MODULE_PREFIX}${MODULE_NAME})
set(INCLUDE_LOCATION Include/Pargon/)
set(HEADER_LOCATION ${INCLUDE_LOCATION}${MODULE_NAME}/)
set(SOURCE_LOCATION Source/)
set(DEPENDENCY_LOCATION Dependencies/)

foreach(DEPENDENCY ${DEPENDENCIES})
	add_subdirectory(${DEPENDENCY_LOCATION}${DEPENDENCY})
endforeach()

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
	list(APPEND SOURCES ${WIN32_SOURCES})
endif()

list(TRANSFORM INCLUDES PREPEND ${INCLUDE_LOCATION})
list(TRANSFORM HEADERS PREPEND ${HEADER_LOCATION})
list(TRANSFORM SOURCES PREPEND ${SOURCE_LOCATION})
list(TRANSFORM MODULES PREPEND ${MODULE_PREFIX})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_LOCATION}" FILES ${INCLUDES})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_LOCATION}" PREFIX Include FILES ${HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_LOCATION}" FILES ${SOURCES})

add_library(${TARGET_NAME} STATIC)
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
target_include_directories(${TARGET_NAME} PUBLIC Include)
target_include_directories(${TARGET_NAME} PRIVATE Source)
target_sources(${TARGET_NAME} PRIVATE "${INCLUDES}" "${HEADERS}" "${SOURCES}")
target_link_libraries(${TARGET_NAME} PUBLIC ${MODULES})
target_link_libraries(${TARGET_NAME} PRIVATE ${DEPENDENCIES})

if(TEST_TARGET)
	set(TESTS ${TESTS} PARENT_SCOPE)
endif()
