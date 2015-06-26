FILE(GLOB_RECURSE ALL_FILES
		"./include/*.h"
		"./lib/*.cxx"
	)

#message(STATUS "all files: ${ALL_FILES}")

add_library(Glew SHARED ${ALL_FILES})