function(add_pargon_dependency DEPENDENCY_NAME)

	set(CMAKE_FOLDER Dependencies)
	add_subdirectory(Dependencies/${DEPENDENCY_NAME})

endfunction()
