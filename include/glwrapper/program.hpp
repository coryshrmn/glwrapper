#ifndef GLWRAPPER_PROGRAM_HPP
#define GLWRAPPER_PROGRAM_HPP

#include "glwrapper/profile.hpp"

#include "glwrapper/shader.hpp"
#include "glwrapper/uniform.hpp"

namespace glwrapper {

namespace detail {
    struct ProgramResourceTag;

    template <>
    struct ResourceTraits<ProgramResourceTag> {
        using Handle = GLuint;
        static void destroy(Handle handle) {
            glDeleteProgram(handle);
        }
    };

    using ProgramResource = Resource<ProgramResourceTag>;
} // namespace detail

class Program {
private:

    // The ref pages are a disaster on this
    // OpenGL ref doesn't list GL_INFO_LOG_LENGTH, but it should work.
    //
    // This ignores the ref pages, and lists all valid enums.
    enum class ProgramParameter : GLenum {
        ACTIVE_ATOMIC_COUNTER_BUFFERS           = GL_ACTIVE_ATOMIC_COUNTER_BUFFERS,
        ACTIVE_ATTRIBUTES                       = GL_ACTIVE_ATTRIBUTES,
        ACTIVE_ATTRIBUTE_MAX_LENGTH             = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
        ACTIVE_UNIFORMS                         = GL_ACTIVE_UNIFORMS,
        ACTIVE_UNIFORM_BLOCKS                   = GL_ACTIVE_UNIFORM_BLOCKS,
        ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH    = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
        ACTIVE_UNIFORM_MAX_LENGTH               = GL_ACTIVE_UNIFORM_MAX_LENGTH,
        ATTACHED_SHADERS                        = GL_ATTACHED_SHADERS,
        COMPUTE_WORK_GROUP_SIZE                 = GL_COMPUTE_WORK_GROUP_SIZE,
        DELETE_STATUS                           = GL_DELETE_STATUS,
        GEOMETRY_INPUT_TYPE                     = GL_GEOMETRY_INPUT_TYPE,
        GEOMETRY_OUTPUT_TYPE                    = GL_GEOMETRY_OUTPUT_TYPE,
        GEOMETRY_SHADER_INVOCATIONS             = GL_GEOMETRY_SHADER_INVOCATIONS,
        GEOMETRY_VERTICES_OUT                   = GL_GEOMETRY_VERTICES_OUT,
        INFO_LOG_LENGTH                         = GL_INFO_LOG_LENGTH,
        LINK_STATUS                             = GL_LINK_STATUS,
        PROGRAM_BINARY_LENGTH                   = GL_PROGRAM_BINARY_LENGTH,
        PROGRAM_BINARY_RETRIEVABLE_HINT         = GL_PROGRAM_BINARY_RETRIEVABLE_HINT,
        PROGRAM_SEPARABLE                       = GL_PROGRAM_SEPARABLE,
        TESS_CONTROL_OUTPUT_VERTICES            = GL_TESS_CONTROL_OUTPUT_VERTICES,
        TESS_GEN_MODE                           = GL_TESS_GEN_MODE,
        TESS_GEN_POINT_MODE                     = GL_TESS_GEN_POINT_MODE,
        TESS_GEN_SPACING                        = GL_TESS_GEN_SPACING,
        TESS_GEN_VERTEX_ORDER                   = GL_TESS_GEN_VERTEX_ORDER,
        TRANSFORM_FEEDBACK_BUFFER_MODE          = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
        TRANSFORM_FEEDBACK_VARYINGS             = GL_TRANSFORM_FEEDBACK_VARYINGS,
        TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH   = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
        VALIDATE_STATUS                         = GL_VALIDATE_STATUS
    };

    detail::ProgramResource programResource;

public:
    Program() = default;
    
    void create() {
        programResource = { glCreateProgram() };
    }

    bool exists() const {
        return programResource.getHandle() != 0;
    }

    GLuint getHandle() const {
        return programResource.getHandle();
    }

    void attachShader(const Shader& shader) {
        glAttachShader(programResource.getHandle(), shader.getHandle());
    }

    void link() {
        glLinkProgram(programResource.getHandle());
    }

    bool getLinkSucceeded() const {
        return getParameterValue(ProgramParameter::LINK_STATUS) == GL_TRUE;
    }

    // including null terminator
    int getInfoLogLength() const {
        return getParameterValue(ProgramParameter::INFO_LOG_LENGTH);
    }

    // writes null-terminated info log string to buffer
    // returns length (excluding null terminator)
    int getInfoLog(int bufferSize, char* buffer) const {
        int length;
        glGetProgramInfoLog(programResource.getHandle(), bufferSize, &length, buffer);
        return length;
    }

    // allocates a new buffer and loads the program info log
    // returns {string, length (excluding null terminator)}
    // throws std::bad_alloc
    std::pair<std::unique_ptr<char[]>, int> getInfoLogAlloc() const {
        int size = getInfoLogLength();
        std::unique_ptr<char[]> buffer { new char[size] };
        int sizeNoNull = getInfoLog(size, buffer.get());
        return { std::move(buffer), sizeNoNull };
    }

    template <typename T>
    Uniform<T> getUniform(const char* name) const {
        return { glGetUniformLocation(programResource.getHandle(), name) };
    }

    void use() const {
        glUseProgram(programResource.getHandle());
    }

private:
    int getParameterValue(ProgramParameter parameter) const {
        int result;
        glGetProgramiv(programResource.getHandle(), static_cast<GLenum>(parameter), &result);
        return result;
    }
};

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_PROGRAM_HPP
