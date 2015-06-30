# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (GameEngine C CXX)

#find_package(Doxygen)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
#add_subdirectory (dependencies)
add_subdirectory (game)
add_subdirectory (graphics)
add_subdirectory (physics)
add_subdirectory (test)
add_subdirectory (tools)