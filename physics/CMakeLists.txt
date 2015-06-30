FILE(GLOB_RECURSE ALL_FILES
		"./src/*.h"
		"./src/*.cpp"
		"./src/*.c"
	)

#message(STATUS "all files: ${ALL_FILES}")

add_library(Physics STATIC ${ALL_FILES})
target_link_libraries(Physics LINK_PUBLIC Tools)
target_include_directories(Physics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
