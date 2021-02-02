function(add_pargon_application APPLICATION_NAME SOURCES MODULES)

	set(CMAKE_FOLDER "")

	source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" FILES ${SOURCES})

	add_executable(${APPLICATION_NAME} ${SOURCES})
	target_compile_features(${APPLICATION_NAME} PUBLIC cxx_std_17)
	target_include_directories(${APPLICATION_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
	target_link_libraries(${APPLICATION_NAME} PUBLIC ${MODULES})
	
	if(IS_WINDOWS)
		set_property(TARGET ${APPLICATION_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
	endif()

	if(MSVC)
		set_property(TARGET ${APPLICATION_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
		set_property(GLOBAL PROPERTY VS_STARTUP_PROJECT ${APPLICATION_NAME})
	endif()

endfunction()
