cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(GOOGLETEST_INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest-install")

include(ExternalProject)
ExternalProject_Add(googletest
    GIT_URL https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${GOOGLETEST_INSTALL_DIR}
)
