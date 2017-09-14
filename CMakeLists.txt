# The glwrapper library is header only, and does not require any compilation.
# This CMakeLists.txt builds glwrapper tests.

# The glwrapper tests depend on:
# SDL2
# glew 2.0.0+

cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(glwrapper-test)

enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(include)
include_directories("lib/cwrapper/include")

set(GLWRAPPER_HEADERS
    "include/glwrapper.hpp"
    "include/glwrapper/buffer.hpp"
    "include/glwrapper/detail/string_view.hpp"
    "include/glwrapper/error.hpp"
    "include/glwrapper/profile.hpp"
    "include/glwrapper/program.hpp"
    "include/glwrapper/program_util.hpp"
    "include/glwrapper/shader.hpp"
    "include/glwrapper/shader_util.hpp"
    "include/glwrapper/uniform.hpp"
    "include/glwrapper/vertex_array.hpp"
)
set(GLWRAPPER_TEST_HEADERS
    "test/context.hpp"
)

# main test
add_executable(glwrapper-test
    test/buffer.cpp
    test/error.cpp
    test/program.cpp
    test/shader.cpp
    test/vertex_array.cpp
    ${GLWRAPPER_HEADERS}
    ${GLWRAPPER_TEST_HEADERS}
)
add_test(NAME glwrapper-test COMMAND glwrapper-test)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

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

# find OpenGL library
find_package(OpenGL REQUIRED)
target_link_libraries(glwrapper-test ${OPENGL_gl_LIBRARY})

# find glew 2
find_package(GLEW 2 REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(glwrapper-test ${GLEW_LIBRARIES})

# find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(glwrapper-test ${SDL2_LIBRARY})
