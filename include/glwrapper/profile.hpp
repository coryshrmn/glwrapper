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
