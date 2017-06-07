#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/profile.hpp"

#include "glwrapper/shader.hpp"

#include <iostream>
#include <string>

#ifdef GLWRAPPER_PROFILE_DESKTOP
// OpenGL core profile always supports Shading Language 1.40
#define GLSL_VERSION_LINE "#version 140\n"
#define GLSL_ATTRIBUTE "in "
#define GLSL_VARYING_VERT = "out "
#define GLSL_VARYING_FRAG = "in "
#else
// OpenGL ES 2.0+ supports ES Shading Language 1.00
#define GLSL_VERSION_LINE "#version 100\n"
#define GLSL_ATTRIBUTE "attribute "
#define GLSL_VARYING_VERT = "varying "
#define GLSL_VARYING_FRAG = "varying "
#endif

using glwrapper::Shader;
using glwrapper::ShaderType;

TEST(Shader, CompileFail) {
    Context context;

    const char* sourceStrings[] = {
        GLSL_VERSION_LINE,
        "#error\n"
    };

    Shader shader(ShaderType::VERTEX);
    shader.setSource(sizeof(sourceStrings) / sizeof(sourceStrings[0]), sourceStrings);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), false);
}

TEST(Shader, CompileFailInfoLog) {
    Context context;

    const char* sourceStrings[] = {
        GLSL_VERSION_LINE,
        "#error CompileFailInfoLog\n"
    };

    Shader shader(ShaderType::VERTEX);
    shader.setSource(sizeof(sourceStrings) / sizeof(sourceStrings[0]), sourceStrings);
    shader.compile();

    std::string infoLog {shader.getInfoLogAlloc().first.get()};
    bool foundErrorMessage = infoLog.find("CompileFailInfoLog") != std::string::npos;
    EXPECT_TRUE(foundErrorMessage);
}

TEST(Shader, VertexCompileMultiSource) {
    Context context;

    const char* sourceStrings[] = {
        GLSL_VERSION_LINE,
        "void main() {\n"
        "    gl_Position = vec4(0.0);\n"
        "}\n"
    };

    Shader shader(ShaderType::VERTEX);
    shader.setSource(sizeof(sourceStrings) / sizeof(sourceStrings[0]), sourceStrings);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), true);
}

TEST(Shader, VertexCompileSingleSource) {
    Context context;

    const char* source = 
        GLSL_VERSION_LINE
        "void main() {\n"
        "    gl_Position = vec4(0.0);\n"
        "}\n";

    Shader shader(ShaderType::VERTEX);
    shader.setSource(source);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), true);
}

#ifndef GLWRAPPER_NO_STRING_VIEW
TEST(Shader, VertexCompileStringView) {
    Context context;

    std::string source = 
        GLSL_VERSION_LINE
        "void main() {\n"
        "    gl_Position = vec4(0.0);\n"
        "}\n";

    Shader shader(ShaderType::VERTEX);
    shader.setSource(source);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), true);
}
#endif
