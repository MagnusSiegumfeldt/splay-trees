cmake_minimum_required(VERSION 3.15)
project(splay-trees)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")

include_directories(include)

set(IMPL_FILES ${IMPL_FILES}
#src/splay_tree.cpp
)

set(TEST_FILES ${TEST_FILES}
test/test.cpp
)

# Main target
add_executable(main src/main.cpp)
add_executable(test_runner src/test_runner.cpp)

add_subdirectory(src/lib/Catch2)

# Removes extra CTest targets
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)

# Add Ctest and Catch to CMake
include(CTest)
include(Catch)
enable_testing()

# Create tests target and add it to test list
add_executable(tests ${TEST_FILES} ${IMPL_FILES})
target_link_libraries(tests PRIVATE Catch2 Catch2WithMain)
catch_discover_tests(tests)
