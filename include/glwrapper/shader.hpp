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
#ifndef GLWRAPPER_SHADER_HPP
#define GLWRAPPER_SHADER_HPP

#include "glwrapper/profile.hpp"

#include "glwrapper/detail/string_view.hpp"
#include "cwrapper/resource.hpp"

// unique_ptr
#include <memory>

// pair
#include <utility>

namespace glwrapper {

namespace detail {

    struct ShaderDeleter {
        void operator()(GLuint handle) {
            glDeleteShader(handle);
        }
    };

    using ShaderResource = cwrapper::Resource<GLuint, ShaderDeleter>;

} // namespace detail

enum class ShaderType : GLenum {
    COMPUTE = 0x91B9,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    VERTEX = GL_VERTEX_SHADER
};

inline const char* getShaderTypeName(ShaderType shaderType) {
    switch(shaderType) {
    case ShaderType::COMPUTE: return "COMPUTE";
    case ShaderType::FRAGMENT: return "FRAGMENT";
    case ShaderType::GEOMETRY: return "GEOMETRY";
    case ShaderType::TESS_CONTROL: return "TESS_CONTROL";
    case ShaderType::VERTEX: return "VERTEX";
    default: return "UNKNOWN_SHADER";
    }
}

class Shader {
private:
    enum class ShaderParameter : GLenum {
        COMPILE_STATUS = GL_COMPILE_STATUS,
        DELETE_STATUS = GL_DELETE_STATUS,
        INFO_LOG_LENGTH = GL_INFO_LOG_LENGTH,
        SHADER_TYPE = GL_SHADER_TYPE
    };

    detail::ShaderResource shaderResource;

public:
    Shader() = default;

    explicit Shader(ShaderType shaderType)
        : shaderResource(glCreateShader(static_cast<GLenum>(shaderType))) {
    }

    GLuint getHandle() const {
        return shaderResource.getHandle();
    }

    bool exists() const {
        return shaderResource.getHandle() != 0;
    }

    void setSource(detail::string_view source) {
        const char* data = source.data();
        int length = source.length();
        setSource(1, &data, &length);
    }

    void setSource(const char* source) {
        setSource(1, &source);
    }

    void setSource(int count, const char** sourceStrings, const int* sourceStringLengths = nullptr) {
        glShaderSource(shaderResource.getHandle(), count, sourceStrings, sourceStringLengths);
    }

    void compile() {
        glCompileShader(shaderResource.getHandle());
    }

    bool getCompileSucceeded() const {
        return getParameterValue(ShaderParameter::COMPILE_STATUS) == GL_TRUE;
    }

    // including null terminator
    int getInfoLogLength() const {
        return getParameterValue(ShaderParameter::INFO_LOG_LENGTH);
    }

    // writes null-terminated info log string to buffer
    // returns length (excluding null terminator)
    int getInfoLog(int bufferSize, char* buffer) const {
        int length;
        glGetShaderInfoLog(shaderResource.getHandle(), bufferSize, &length, buffer);
        return length;
    }

    // allocates a new buffer and loads the shader info log
    // returns {string, length (excluding null terminator)}
    // throws std::bad_alloc
    std::pair<std::unique_ptr<char[]>, int> getInfoLogAlloc() const {
        int size = getInfoLogLength();
        std::unique_ptr<char[]> buffer { new char[size] };
        int sizeNoNull = getInfoLog(size, buffer.get());
        return { std::move(buffer), sizeNoNull };
    }

private:
    int getParameterValue(ShaderParameter parameter) const {
        int result;
        glGetShaderiv(shaderResource.getHandle(), static_cast<GLenum>(parameter), &result);
        return result;
    }
};

} // namespace glwrapper

static std::ostream& operator<<(std::ostream& out, const glwrapper::ShaderType& shaderType)
{
    return out << glwrapper::getShaderTypeName(shaderType);
}

#endif // #ifndef GLWRAPPER_SHADER_HPP
