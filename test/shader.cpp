#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/profile.hpp"

#include "glwrapper/shader.hpp"

#ifdef GLWRAPPER_PROFILE_DESKTOP
// OpenGL core profile always supports Shading Language 1.40
const char* shaderVersionLine = "#version 140\n";
#define GLSL_ATTRIBUTE "in "
#define GLSL_VARYING_VERT = "out "
#define GLSL_VARYING_FRAG = "in "
#else
// OpenGL ES 2.0+ supports ES Shading Language 1.00
const char* shaderVersionLine = "#version 100\n";
#define GLSL_ATTRIBUTE "attribute "
#define GLSL_VARYING_VERT = "varying "
#define GLSL_VARYING_FRAG = "varying "
#endif

const char* shaderErrorLine = "#error\n";

TEST(Shader, CompileFail) {
    using namespace glwrapper;

    Context context;

    const char* sourceStrings[] = {
        shaderVersionLine,
        shaderErrorLine
    };

    Shader shader(ShaderType::VERTEX);
    shader.setSource(sizeof(sourceStrings) / sizeof(sourceStrings[0]), sourceStrings);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), false);
}

TEST(Shader, VertexCompile) {
    using namespace glwrapper;

    Context context;

    const char* sourceStrings[] = {
        shaderVersionLine,
        "void main() {\n"
        "    gl_Position = vec4(0.0);\n"
        "}\n"
    };

    Shader shader(ShaderType::VERTEX);
    shader.setSource(sizeof(sourceStrings) / sizeof(sourceStrings[0]), sourceStrings);
    shader.compile();
    
    EXPECT_EQ(shader.getCompileSucceeded(), true);
}
