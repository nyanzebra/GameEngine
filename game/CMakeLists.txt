FILE(GLOB_RECURSE ALL_FILES
		"./src/*.h"
		"./src/*.cpp"
		"./src/*.c"
	)

#message(STATUS "all files: ${ALL_FILES}")

add_executable(Game main.cpp ${ALL_FILES})