# GLWrapper

Header-only C++ wrapper for modern OpenGL and OpenGLES

## Features

* Support for OpenGL 3.2 - 4.5 core profile, and OpenGLES 2.0 - 3.2

* C++11 syntax, RAII with move support

* Optionally supports C++17 `string_view` or `boost::string_view`

* Minimal heap allocations.
  All features of OpenGL can be used without any GLWrapper allocations.
  Some functions allocate for convenience; they have an "Alloc" suffix.

* Header-only

* Packages OpenGL and OpenGLES headers (if you don't include your own before GLWrapper).

* Well tested

## Status

Barely started. Initial goal is to support use cases for my game.

### Supported

* errors (error codes, error names, get error, check error and throw)
* shaders (compile, get compilation status and info log)

### Roadmap

1. Finish core features
  * programs
  * buffers
  * uniforms
  * attributes
  * textures
  * misc gl functions
2. Nice to have features
  * binary shaders/programs
  * direct state access
3. Popular extensions
4. (Maybe) some more obscure OpenGL functions

## Using GLWrapper

### Including GLWrapper

You can add the [include](include) directory to your project,
and add `#include "glwrapper.hpp"` in your code.
GLWrapper will work out of the box.

If you include your own OpenGL 4.5+ or OpenGL ES 3.2+ header files before including GLWrapper,
then you don't need the [GL](include/GL), [GLES3](include/GLES3), or [KHR](include/KHR) directories.

If your compiler has full C++17 support,
you use `boost::string_view` by defining `GLWRAPPER_BOOST_STRING_VIEW`,
or you disable GLWrapper's `string_view` support by defining `GLWRAPPER_NO_STRING_VIEW`,
then you don't need the [stx](stx) directory.

### Compling GLWrapper

GLWrapper is header only, there is nothing to compile.

### Examples

See [test](test) files.

## Testing

GLWrapper has a comprehensive unit test suite, using Googletest, SDL2 and glew 2.
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
