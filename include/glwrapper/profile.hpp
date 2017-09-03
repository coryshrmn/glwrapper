#ifndef GLWRAPPER_PROFILE_HPP
#define GLWRAPPER_PROFILE_HPP

#if defined(GL_VERSION)

    // OpenGL headers can be included before GLWrapper,
    // but they must be OpenGL 4.5+ or OpenGLES 3.2+.

    #if defined(GL_VERSION_4_5)
        #define GLWRAPPER_PROFILE_DESKTOP
        #undef GLWRAPPER_PROFILE_ES
    #elif defined(GL_ES_VERSION_3_2)
        #define GLWRAPPER_PROFILE_ES
        #undef GLWRAPPER_PROFILE_DESKTOP
    #else
        #error OpenGL header version not supported. GLWrapper can only use headers for OpenGL 4.5+ or OpenGLES 3.2+
    #endif

#else

    // GLWrapper ships with its own OpenGL 4.5 and OpenGLES 3.2 headers.
    // You can force the GL API Profile type (OpenGL or OpenGLES) by defining GLWRAPPER_PROFILE_DESKTOP or GLWRAPPER_PROFILE_ES

    #if defined(GLWRAPPER_PROFILE_DESKTOP) && defined(GLWRAPPER_PROFILE_ES)
        #error Defined both GLWRAPPER_PROFILE_DESKTOP and GLWRAPPER_PROFILE_ES.
        #undef GLWRAPPER_PROFILE_ES
    #endif

    #if !defined(GLWRAPPER_PROFILE_DESKTOP) && !defined(GLWRAPPER_PROFILE_ES)
        // define a profile based off the target OS/platform
        #if TARGET_OS_IPHONE || defined(__ANDROID__) || defined(__EMSCRIPTEN__)
            #define GLWRAPPER_PROFILE_ES
        #else
            #define GLWRAPPER_PROFILE_DESKTOP
        #endif
    #endif

    #if defined(GLWRAPPER_PROFILE_DESKTOP)
        #define GL_GLEXT_PROTOTYPES
        #include "GL/glcorearb.h"
    #else
        #include "GLES3/gl32.h"
    #endif

#endif

namespace glwrapper {

enum class Profile {
    DESKTOP,
    ES
};

constexpr Profile getProfile() {
#ifdef GLWRAPPER_PROFILE_DESKTOP
    return Profile::DESKTOP;
#elif GLWRAPPER_PROFILE_ES
    return Profile::ES;
#else
    #error Unknown profile
#endif
}

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_PROFILE_HPP
