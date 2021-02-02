function(set_pargon_defaults)

	add_definitions(-DUNICODE -D_UNICODE)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER CMake)
	
	if(CMAKE_SYSTEM_NAME STREQUAL Windows)
		set(IS_WINDOWS ON PARENT_SCOPE)
	endif()

endfunction()
