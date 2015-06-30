FILE(GLOB_RECURSE ALL_FILES
		"./src/*.h"
		"./src/*.cpp"
		"./src/*.c"
	)

#message(STATUS "all files: ${ALL_FILES}")

add_library(Physics STATIC ${ALL_FILES})