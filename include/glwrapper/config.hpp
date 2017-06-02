#ifndef GLWRAPPER_CONFIG_HPP
#define GLWRAPPER_CONFIG_HPP

#ifndef GL_VERSION
    #error "OpenGL headers not included before glwrapper"
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

#endif // #ifndef GLWRAPPER_CONFIG_HPP
