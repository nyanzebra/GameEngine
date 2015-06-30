FILE(GLOB_RECURSE ALL_FILES
		"./include/*.h"
		"./lib/*.cxx"
	)

#message(STATUS "all files: ${ALL_FILES}")

add_library(Freeimage SHARED ${ALL_FILES})