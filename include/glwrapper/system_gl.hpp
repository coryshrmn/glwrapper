#ifndef GLWRAPPER_SYSTEM_GL_HPP
#define GLWRAPPER_SYSTEM_GL_HPP

/*
Includes the primary OpenGL headers for the target platform.

If you want to target a different type of OpenGL, include the header yourself before including GLWrapper.
For example, you can include GLES headers on desktop Linux.

Mac         OpenGL      3+
Linux       OpenGL
Windows     OpenGL      1? Windows OpenGL is complicated.
iPhone      OpenGLES    3
Android     OpenGLES    3
Emscripten  OpenGLES    2

*/

#ifdef GL_VERSION
    #error OpenGL headers already included
#endif

#if defined(__APPLE__)
    #if TARGET_OS_IPHONE
        #warn not tested platform
        #include <OpenGLES/ES3/gl.h>
        #include <OpenGLES/ES3/glext.h>
    #else
        #include <OpenGL/gl3.h>
        #include <OpenGL/gl3ext.h>
    #endif
#elif defined(__ANDROID__)
    #warn not tested platform
    #include <GLES3/gl.h>
    #include <GLES3/glext.h>
#elif defined(__EMSCRIPTEN__)
    #include <GLES2/gl.h>
    #include <GLES2/glext.h>
#elif defined(__LINUX__)
    #warn not tested platform
    #include <gl/gl.h>
    #include <gl/glext.h>
#elif defined(_WIN32)
    #warn not tested platform
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    #error unknown platform
#endif

#endif // #ifndef GLWRAPPER_SYSTEM_GL_HPP
