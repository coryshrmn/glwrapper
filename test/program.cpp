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
#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/profile.hpp"

#include "glwrapper/shader.hpp"
#include "glwrapper/program_util.hpp"
#include "glwrapper/shader_util.hpp"

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
using glwrapper::Program;

constexpr const char* VERTEX_SHADER_SOURCE =
        "#version 140\n"
        "void main() {\n"
        "    gl_Position = vec4(0.0);\n"
        "}\n";

constexpr const char* FRAGMENT_SHADER_SOURCE =
        "#version 140\n"
        "void main() {\n"
        "    gl_FragColor = vec4(1.0);\n"
        "}\n";

TEST(Program, Link) {
    Context context;
    Shader vert = glwrapper::shaderFromSource(ShaderType::VERTEX, VERTEX_SHADER_SOURCE);
    Shader frag = glwrapper::shaderFromSource(ShaderType::FRAGMENT, FRAGMENT_SHADER_SOURCE);
    Program program = glwrapper::programFromShaders({vert, frag});
}
