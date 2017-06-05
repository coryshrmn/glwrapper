# GLWrapper

Header-only C++ wrapper for modern OpenGL and OpenGLES

## Features

* Full support for OpenGL 3.2 - 4.5 core profile, and OpenGLES 2.0 - 3.2

* C++11 syntax, RAII with move support

* Optionally supports C++17 string\_view or boost::string\_view

* Minimal heap allocations.
  All features of OpenGL can be used without any GLWrapper allocations.
  Some functions allocate for convenience; they have an "Alloc" suffix.

* Header-only

* Packages OpenGL and OpenGLES headers (if you don't include your own before GLWrapper).

* Well tested

## Status

Barely started

## Testing

GLWrapper has a Comprehensive unit test suite, using Googletest, SDL2 and glew 2.
Tests are built with CMake.

### Testing Requirements

* CMake
* SDL2 development library
* glew 2 development library

### Running the Tests

```bash
git clone https://github.com/coryshrmn/glwrapper.git
cd glwrapper
mkdir build && cd build
cmake ..
cmake --build .
./glwrapper-test
```
