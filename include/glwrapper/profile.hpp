/*
   Copyright 2017 Cory Sherman

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#ifndef GLWRAPPER_PROFILE_HPP
#define GLWRAPPER_PROFILE_HPP

#if defined(GL_VERSION)

    // OpenGL headers can be included before GLWrapper,
    // but they must be OpenGL 4.5+.

    #if !defined(GL_VERSION_4_5)
        #error OpenGL header version not supported. GLWrapper can only use headers for OpenGL 4.5+
    #endif

#else

    // GLWrapper ships with its own OpenGL 4.5 headers
    #define GL_GLEXT_PROTOTYPES
    #include "GL/glcorearb.h"

#endif

namespace glwrapper {

enum class Profile {
    DESKTOP
};

constexpr Profile getProfile() {
    return Profile::DESKTOP;
}

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_PROFILE_HPP
