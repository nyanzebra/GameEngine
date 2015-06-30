FILE(GLOB_RECURSE ALL_FILES
		"./src/*.h"
		"./src/*.cpp"
		"./src/*.c"
	)


#message(STATUS "all files: ${ALL_FILES}")

add_library(Graphics STATIC ${ALL_FILES})
#set_target_properties(Graphics PROPERTIES LINKER_LANGUAGE C++)