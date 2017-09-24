# GLWrapper

Header-only C++17 wrapper for modern OpenGL

## Features

* Support for OpenGL 4.1-4.6 core profile

* C++11 syntax, RAII with move support

* Requires C++17 `string_view` or `boost::string_view`

* Minimal heap allocations.
  Some functions allocate for convenience; they have an "Alloc" suffix.

* Header-only

* Somewhat tested

## Status

Barely started. Initial goal is to support use cases for my game.

### Supported

* errors (error codes, error names, get error, check error and throw)
* shaders (compile, get compilation status and info log)

### Roadmap

1. Finish core features
  * programs
  * buffers
  * vertex array objects
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

You must include OpenGL headers before including glwrapper.

You can add the [include](include) directory to your project,
and add `#include "glwrapper.hpp"` in your code.
GLWrapper will work out of the box.

If your compiler has full C++17 support,
or you use `boost::string_view` by defining `GLWRAPPER_BOOST_STRING_VIEW`,
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
