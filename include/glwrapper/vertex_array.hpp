#ifndef GLWRAPPER_VERTEX_ARRAY_HPP
#define GLWRAPPER_VERTEX_ARRAY_HPP

#include "glwrapper/profile.hpp"

#include "glwrapper/detail/resource.hpp"

namespace glwrapper {

namespace detail {
    struct VertexArrayResourceTag;

    template <>
    struct ResourceTraits<VertexArrayResourceTag> {
        using Handle = GLuint;
        static void destroy(Handle handle) {
            glDeleteVertexArrays(1, handle);
        }
    };

    using VertexArrayResource = Resource<VertexArrayResourceTag>;

} // namespace detail

class VertexArray {
private:
    detail::VertexArrayResource vertexArrayResource;

public:
    VertexArray() = default;

    void generate() {
        GLuint handle;
        glGenVertexArrays(1, &handle);
        vertexArrayResource = {handle};
    }

    bool exists() const {
        return vertexArrayResource.getHandle() != 0;
    }

    void bind() const {
        glBindVertexArray(vertexArrayResource.getHandle());
    }

    static void unbind() {
        glBindVertexArray(0);
    }

// DSA requires OpenGL 4.5+
#ifdef GLWRAPPER_PROFILE_DESKTOP
    void setData(int size, const void* data, BufferUsage usage) {
        glNamedBufferData(bufferResource.getHandle(), size, data, static_cast<GLenum>(usage));
    }

    void setSubData(std::intptr_t offset, int size, const void* data) {
        glNamedBufferSubData(bufferResource.getHandle(), offset, size, data);
    }
#endif

    static void setData(BufferBindingTarget target, int size, const void* data, BufferUsage usage) {
        glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
    }

    static void setSubData(BufferBindingTarget target, std::intptr_t offset, int size, const void* data) {
        glBufferSubData(static_cast<GLenum>(target), offset, size, data);
    }
};

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_VERTEX_ARRAY_HPP
