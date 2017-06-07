#ifndef GLWRAPPER_SHADER_HPP
#define GLWRAPPER_SHADER_HPP

#include "glwrapper/profile.hpp"

#include "glwrapper/detail/resource.hpp"
#include "glwrapper/detail/string_view.hpp"

// unique_ptr
#include <memory>

// pair
#include <utility>

namespace glwrapper {

namespace detail {
    struct ShaderResourceTag;

    template <>
    struct ResourceTraits<ShaderResourceTag> {
        using Handle = GLuint;
        static void destroy(Handle handle) {
            glDeleteShader(handle);
        }
    };

    using ShaderResource = Resource<ShaderResourceTag>;

} // namespace detail

enum class ShaderType : GLenum {
    COMPUTE = GL_COMPUTE_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    VERTEX = GL_VERTEX_SHADER
};

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

    Shader(ShaderType shaderType)
        : shaderResource(glCreateShader(static_cast<GLenum>(shaderType))) {
    }

    bool exists() const {
        return shaderResource.getHandle() != 0;
    }

#ifndef GLWRAPPER_NO_STRING_VIEW
    void setSource(detail::string_view source) {
        const char* data = source.data();
        int length = source.length();
        setSource(1, &data, &length);
    }
#endif

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

#endif // #ifndef GLWRAPPER_SHADER_HPP
