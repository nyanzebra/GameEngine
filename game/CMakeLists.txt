IF (MSVC)
	set(GLEW_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glew-1.12.0)
	set(GLFW_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glfw-3.1.1)
	set(FREEIMAGE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/freeimage/Dist)
ENDIF(MSVC)

find_package(GLFW REQUIRED)

if(GLFW_FOUND)
    message(STATUS "Found GLFW")
	include_directories(${GLFW_INCLUDE_DIRS})
endif(GLFW_FOUND)

find_package(GLEW REQUIRED)

if(GLEW_FOUND)
    message(STATUS "Found GLEW")
	include_directories(${GLEW_INCLUDE_DIR})
endif(GLEW_FOUND)

find_package(FreeImage REQUIRED)

if(FREEIMAGE_FOUND)
    message(STATUS "Found FreeImage")
	include_directories(${FREEIMAGE_INCLUDE_DIRS})
endif(FREEIMAGE_FOUND)

FILE(GLOB_RECURSE ALL_FILES
		"./src/*.h"
		"./src/*.cpp"
		"./src/*.c"
	)

#message(STATUS "all files: ${ALL_FILES}")
add_executable(Game main.cpp ${ALL_FILES})
target_link_libraries(Game LINK_PUBLIC Graphics Physics Tools ${GLEW_LIBRARY} ${FREEIMAGE_LIBRARY} ${GLFW_LIBRARIES})
