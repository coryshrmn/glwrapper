#ifndef GLWRAPPER_CONFIG_HPP
#define GLWRAPPER_CONFIG_HPP

#ifndef GL_VERSION
    // If you don't include OpenGL headers before including GLWrapper,
    // we will try to find the target's default OpenGL headers
    #include "glwrapper/system_gl.hpp"
#endif

#ifdef GL_VERSION_3_2
    #define GLWRAPPER_HAS_GEOMETRY_SHADER
#endif

#ifdef GL_VERSION_4_0
    #define GLWRAPPER_HAS_TESS_SHADER
#endif

#ifdef GL_VERSION_4_3
    #define GLWRAPPER_HAS_COMPUTE_SHADER
#endif

#if defined(GL_VERSION_2_0)
    #define GLWRAPPER_PROFILE_DESKTOP
#elif defined(GL_ES_VERSION_2_0)
    #define GLWRAPPER_PROFILE_ES
#else
    #error GLWrapper requires OpenGL 2.0+ or OpenGLES 2.0+
#endif

namespace glwrapper {

enum class Profile {
    DESKTOP,
    ES
};

constexpr getProfile() {
#ifdef GLWRAPPER_PROFILE_DESKTOP
    return Profile::DESKTOP;
#elif GLWRAPPER_PROFILE_ES
    return Profile::ES;
#else
    #error Unknown profile
#endif
}

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_CONFIG_HPP
