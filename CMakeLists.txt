# The glwrapper library is header only, and does not require any compilation.
# This CMakeLists.txt builds glwrapper tests.

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(glwrapper-test)
enable_testing()

include_directories(include)

# main test
add_executable(glwrapper-test
    test/error.cpp
)
add_test(NAME glwrapper-test COMMAND glwrapper-test)

# Download and compile Googletest library
include(ExternalProject)
set(gtest_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/gtest-install")
ExternalProject_Add(gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${gtest_INSTALL_PREFIX}
)
set(gtest_INCLUDE_DIRS "${gtest_INSTALL_PREFIX}/include")
set(gtest_LIBRARIES
    "${gtest_INSTALL_PREFIX}/lib/libgtest${CMAKE_STATIC_LIBRARY_SUFFIX}"
    "${gtest_INSTALL_PREFIX}/lib/libgtest_main${CMAKE_STATIC_LIBRARY_SUFFIX}"
)
add_dependencies(glwrapper-test gtest)
include_directories(${gtest_INCLUDE_DIRS})
target_link_libraries(glwrapper-test ${gtest_LIBRARIES})

# find system OpenGL and library
find_package(OpenGL REQUIRED)
target_link_libraries(glwrapper-test ${OPENGL_gl_LIBRARY})
