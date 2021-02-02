cmake_minimum_required(VERSION 3.16)
project(Pargon VERSION 0.1 LANGUAGES CXX)

include(Modules/Project/CMake/add_pargon_module.cmake)
include(Modules/Project/CMake/add_pargon_dependency.cmake)
include(Modules/Project/CMake/add_pargon_integration.cmake)
include(Modules/Project/CMake/add_pargon_application.cmake)
include(Modules/Project/CMake/set_pargon_defaults.cmake)

set_pargon_defaults()
set(PARGON_TESTS "Tests")

add_executable(${PARGON_TESTS} "Tests/main.cpp")

add_subdirectory(Modules/Shim)
add_subdirectory(Modules/Debugging)
add_subdirectory(Modules/Testing)
add_subdirectory(Modules/Serialization)
add_subdirectory(Samples/Playground)

target_link_libraries(${PARGON_TESTS} PargonTesting)
