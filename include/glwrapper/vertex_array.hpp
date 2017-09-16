#ifndef GLWRAPPER_VERTEX_ARRAY_HPP
#define GLWRAPPER_VERTEX_ARRAY_HPP

#include "glwrapper/profile.hpp"

#include "cwrapper/resource.hpp"

namespace glwrapper {

namespace detail {

    struct VertexArrayDeleter {
        void operator()(GLuint handle) {
            glDeleteVertexArrays(1, &handle);
        }
    };

    using VertexArrayResource = cwrapper::Resource<GLuint, VertexArrayDeleter>;

} // namespace detail

class VertexArray {
private:
    detail::VertexArrayResource vertexArrayResource {};

public:
    VertexArray() = default;

    enum class CreationMethod {
        GENERATE,
        CREATE,
        CREATE_BIND
    };

    VertexArray(CreationMethod method) {
        switch(method) {
        case CreationMethod::GENERATE:
            generate();
            break;
        case CreationMethod::CREATE:
            create();
            break;
        case CreationMethod::CREATE_BIND:
            generate();
            bind();
            break;
        }
    }

    // allocates an uninitialized VAO
    void generate() {
        GLuint handle;
        glGenVertexArrays(1, &handle);
        vertexArrayResource = detail::VertexArrayResource{handle};
    }

    // uses DSA to initialize the VAO without binding, requires OpenGL 4.5 or *direct_state_access extension
    void create() {
        GLuint handle;
        glCreateVertexArrays(1, &handle);
        vertexArrayResource = detail::VertexArrayResource{handle};
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

    //TODO
    // * GetVertexArray(Indexed)
    // * BindingDivisor
    // * ElementBuffer
    // * VertexBuffer(s)
    // * Attrib functions
    // Who really cares? VAO's are not useful.
    // Some drivers perform like garbage with VAO switching,
    // So we generally just bind one and use it the entire run.
};

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_VERTEX_ARRAY_HPP
