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
#ifndef GLWRAPPER_UNIFORM_HPP
#define GLWRAPPER_UNIFORM_HPP

#include "glwrapper/profile.hpp"

#include <cgs/assert.hpp>

#include "glwrapper/glm_types.hpp"

#include <array>

namespace glwrapper {

enum class UniformType {
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4,
    UINT,
    UINT2,
    UINT3,
    UINT4,
    MATRIX2,
    MATRIX3,
    MATRIX4,
    MATRIX2X3,
    MATRIX3X2,
    MATRIX2X4,
    MATRIX4X2,
    MATRIX3X4,
    MATRIX4X3
};


namespace detail {

template <typename T>
void setUniformArray(GLint location, const T* start, GLsizei count);

template <>
inline void setUniformArray(GLint location, const GLfloat* start, GLsizei count)
{
    glUniform1fv(location, count, start);
}

template <>
inline void setUniformArray(GLint location, const GLint* start, GLsizei count)
{
    glUniform1iv(location, count, start);
}

template <>
inline void setUniformArray(GLint location, const GLuint* start, GLsizei count)
{
    glUniform1uiv(location, count, start);
}

template <>
inline void setUniformArray(GLint location, const vec2* start, GLsizei count)
{
    glUniform2fv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const vec3* start, GLsizei count)
{
    glUniform3fv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const vec4* start, GLsizei count)
{
    glUniform4fv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const i32vec2* start, GLsizei count)
{
    glUniform2iv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const i32vec3* start, GLsizei count)
{
    glUniform3iv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const i32vec4* start, GLsizei count)
{
    glUniform4iv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const u32vec2* start, GLsizei count)
{
    glUniform2uiv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const u32vec3* start, GLsizei count)
{
    glUniform3uiv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const u32vec4* start, GLsizei count)
{
    glUniform4uiv(location, count, &(*start)[0]);
}

template <>
inline void setUniformArray(GLint location, const mat2* start, GLsizei count)
{
    glUniformMatrix2fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat2x3* start, GLsizei count)
{
    glUniformMatrix2x3fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat2x4* start, GLsizei count)
{
    glUniformMatrix2x4fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat3* start, GLsizei count)
{
    glUniformMatrix3fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat3x2* start, GLsizei count)
{
    glUniformMatrix3x2fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat3x4* start, GLsizei count)
{
    glUniformMatrix3x4fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat4* start, GLsizei count)
{
    glUniformMatrix4fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat4x2* start, GLsizei count)
{
    glUniformMatrix4x2fv(location, count, false, &(*start)[0][0]);
}

template <>
inline void setUniformArray(GLint location, const mat4x3* start, GLsizei count)
{
    glUniformMatrix4x3fv(location, count, false, &(*start)[0][0]);
}

} // namespace detail

// single element uniforms
template <typename T>
class Uniform
{
public:

    GLint location = -1;

    void set(const T& val) const
    {
        detail::setUniformArray(location, &val, 1);
    }
};

// array uniforms
template <typename T>
struct Uniform<T[]>
{
public:

    GLint location = -1;

    void set(const T* start, std::int32_t count) const
    {
        cgs_assert(start != nullptr);
        detail::setUniformArray(location, start, count);
    }
};

#ifdef GLWRAPPER_SUPPORTS_DSA
template <typename T>
class ProgramUniform
{
    // TODO
};

template <typename T>
class ProgramUniform<T[]>
{
    // TODO
};
#endif // GLWRAPPER_SUPPORTS_DSA

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_UNIFORM_HPP
