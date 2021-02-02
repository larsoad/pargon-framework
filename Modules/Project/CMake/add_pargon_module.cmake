function(add_pargon_module MODULE_NAME INCLUDES SOURCES LIBRARIES TESTS)

	set(SOLUTION_FOLDER Modules)
	set(INCLUDE_LOCATION Include)
	set(SOURCE_LOCATION Source)
	set(TESTS_LOCATION Tests)
	
	list(TRANSFORM INCLUDES PREPEND ${INCLUDE_LOCATION}/)
	list(TRANSFORM SOURCES PREPEND ${SOURCE_LOCATION}/)
	list(TRANSFORM TESTS PREPEND ${TESTS_LOCATION}/)

	if(SOURCES)
		set(CMAKE_FOLDER ${SOLUTION_FOLDER})
		source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${INCLUDES} ${SOURCES})

		add_library(${MODULE_NAME} STATIC)
		target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)
		target_include_directories(${MODULE_NAME} PUBLIC ${INCLUDE_LOCATION})
		target_include_directories(${MODULE_NAME} PRIVATE ${SOURCE_LOCATION})
		target_sources(${MODULE_NAME} PRIVATE "${INCLUDES}" "${SOURCES}")
		target_link_libraries(${MODULE_NAME} PUBLIC ${LIBRARIES})
	else()
		add_library(${MODULE_NAME} INTERFACE)
		target_include_directories(${MODULE_NAME} INTERFACE ${INCLUDE_LOCATION})
		target_link_libraries(${MODULE_NAME} INTERFACE ${LIBRARIES})
	endif()

	if(TESTS AND TARGET ${PARGON_TESTS})
		source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/${TESTS_LOCATION}" PREFIX ${MODULE_NAME} FILES ${TESTS}) # TODO: This doesn't Work
		target_sources(${PARGON_TESTS} PRIVATE ${TESTS})
		target_link_libraries(${PARGON_TESTS} ${MODULE_NAME})
	endif()

endfunction()
