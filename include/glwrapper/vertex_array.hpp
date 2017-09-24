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
        GENERATE_BIND,
#ifdef GLWRAPPER_SUPPORTS_DSA
        CREATE,
        CREATE_BIND
#endif
    };

    VertexArray(CreationMethod method) {
        switch(method) {
        case CreationMethod::GENERATE:
            generate();
            break;
        case CreationMethod::GENERATE_BIND:
            generate();
            bind();
            break;
#ifdef GLWRAPPER_SUPPORTS_DSA
        case CreationMethod::CREATE:
            create();
            break;
        case CreationMethod::CREATE_BIND:
            create();
            bind();
            break;
#endif
        }
    }

    // allocates an uninitialized VAO
    void generate() {
        GLuint handle;
        glGenVertexArrays(1, &handle);
        vertexArrayResource = detail::VertexArrayResource{handle};
    }

    // uses DSA to initialize the VAO without binding, requires OpenGL 4.5 or *direct_state_access extension
#ifdef GLWRAPPER_SUPPORTS_DSA
    void create() {
        GLuint handle;
        glCreateVertexArrays(1, &handle);
        vertexArrayResource = detail::VertexArrayResource{handle};
    }
#endif

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
