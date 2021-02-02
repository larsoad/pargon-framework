set(MODULE_NAME Math)

set(PUBLIC_HEADERS
	Include/Pargon/Math/Angle.h
	Include/Pargon/Math/Arithmetic.h
	Include/Pargon/Math/Matrix.h
	Include/Pargon/Math/Point.h
	Include/Pargon/Math/Quaternion.h
	Include/Pargon/Math/Rotation.h
	Include/Pargon/Math/Trigonometry.h
	Include/Pargon/Math/Vector.h
)

set(SOURCES
	Source/Core/Angle.cpp
	Source/Core/Arithmetic.cpp
	Source/Core/Matrix.cpp
	Source/Core/Point.cpp
	Source/Core/Quaternion.cpp
	Source/Core/Rotation.cpp
	Source/Core/Trigonometry.cpp
	Source/Core/Vector.cpp
)

set(DEPENDENCIES
	PargonContainers
	PargonSerialization
)

add_subdirectory(Source/Dependencies/CML)

set(TARGET_NAME Pargon${MODULE_NAME})
set(MAIN_HEADER Include/Pargon/${MODULE_NAME}.h)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include/Pargon/" FILES ${MAIN_HEADER})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Include/Pargon/${MODULE_NAME}/" PREFIX Include FILES ${PUBLIC_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/Source/" FILES ${SOURCES})

add_library(${TARGET_NAME} STATIC)
target_compile_features(${TARGET_NAME} PUBLIC cxx_std_17)
target_include_directories(${TARGET_NAME} PUBLIC Include)
target_include_directories(${TARGET_NAME} PRIVATE Source)
target_link_libraries(${TARGET_NAME} PUBLIC ${DEPENDENCIES})
target_link_libraries(${TARGET_NAME} PRIVATE CML)
target_sources(${TARGET_NAME} PRIVATE "${MAIN_HEADER}" "${PUBLIC_HEADERS}" "${SOURCES}")
