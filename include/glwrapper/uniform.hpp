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
    template <UniformType T>
    struct UniformTypeTraits;
    /*
        using Value = // primitive type

        constexpr std::size_t getCount();

        constexpr 

    */
    /*
        template <typename... Args>
        static void set(GLint location, Args... args);
        // primitive, or std::array
        static ? get(GLint location)
    */

//    template <>
//    struct UniformTypeTraits<UniformType::FLOAT> {
//        static void set(GLint location, float value) {
//            glUniform1f(location, value);
//        }
//        static float get(GLint location) {
//            return glGetUniform1f(location);
//        }
//    };

//    template <>
//    struct UniformTypeTraits<UniformType::FLOAT2> {
//        static void set(GLint location, float value1, float value2) {
//            glUniform2f(location, value1, value2);
//        }
//        static float get(GLint location) {
//            return glGetUniform1f(location);
//        }
//    };

} // namespace detail

template <typename T>
class Uniform {
private:
    GLint location;

public:
    Uniform() = default;

    explicit Uniform(GLint location)
        : location(location)
    { }


};

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_UNIFORM_HPP
