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
#ifndef GLWRAPPER_BUFFER_HPP
#define GLWRAPPER_BUFFER_HPP

#include "glwrapper/profile.hpp"

#include "cwrapper/resource.hpp"

namespace glwrapper {

namespace detail {

    struct BufferDeleter {
        void operator()(GLuint handle) {
            glDeleteBuffers(1, &handle);
        }
    };

    using BufferResource = cwrapper::Resource<GLuint, BufferDeleter>;

} // namespace detail

enum class BufferBindingTarget {
    ARRAY               = GL_ARRAY_BUFFER,
    ATOMIC_COUNTER      = GL_ATOMIC_COUNTER_BUFFER,
    COPY_READ           = GL_COPY_READ_BUFFER,
    COPY_WRITE          = GL_COPY_WRITE_BUFFER,
    DISPATCH_INDIRECT   = GL_DISPATCH_INDIRECT_BUFFER,
    DRAW_INDIRECT       = GL_DRAW_INDIRECT_BUFFER,
    ELEMENT_ARRAY       = GL_ELEMENT_ARRAY_BUFFER,
    PIXEL_PACK          = GL_PIXEL_PACK_BUFFER,
    PIXEL_UNPACK        = GL_PIXEL_UNPACK_BUFFER,
    QUERY               = GL_QUERY_BUFFER,
    SHADER_STORAGE      = GL_SHADER_STORAGE_BUFFER,
    TEXTURE             = GL_TEXTURE_BUFFER,
    TRANSFORM_FEEDBACK  = GL_TRANSFORM_FEEDBACK_BUFFER,
    UNIFORM             = GL_UNIFORM_BUFFER
};

enum class BufferUsage {
    STREAM_DRAW     = GL_STREAM_DRAW,
    STREAM_READ     = GL_STREAM_READ,
    STREAM_COPY     = GL_STREAM_COPY,
    STATIC_DRAW     = GL_STATIC_DRAW,
    STATIC_READ     = GL_STATIC_READ,
    STATIC_COPY     = GL_STATIC_COPY,
    DYNAMIC_DRAW    = GL_DYNAMIC_DRAW,
    DYNAMIC_READ    = GL_DYNAMIC_READ,
    DYNAMIC_COPY    = GL_DYNAMIC_COPY
};

class Buffer {
private:
    detail::BufferResource bufferResource {};

public:
    Buffer() = default;

    void generate() {
        GLuint handle;
        glGenBuffers(1, &handle);
        bufferResource = detail::BufferResource{handle};
    }

    void create() {
        GLuint handle;
        glCreateBuffers(1, &handle);
        bufferResource = detail::BufferResource{handle};
    }

    bool exists() const {
        return bufferResource.getHandle() != 0;
    }

    void bind(BufferBindingTarget target) const {
        glBindBuffer(static_cast<GLenum>(target), bufferResource.getHandle());
    }

    static void unbind(BufferBindingTarget target) {
        glBindBuffer(static_cast<GLenum>(target), 0);
    }

    void setData(int size, const void* data, BufferUsage usage) {
        glNamedBufferData(bufferResource.getHandle(), size, data, static_cast<GLenum>(usage));
    }

    void setSubData(std::intptr_t offset, int size, const void* data) {
        glNamedBufferSubData(bufferResource.getHandle(), offset, size, data);
    }

    static void setData(BufferBindingTarget target, int size, const void* data, BufferUsage usage) {
        glBufferData(static_cast<GLenum>(target), size, data, static_cast<GLenum>(usage));
    }

    static void setSubData(BufferBindingTarget target, std::intptr_t offset, int size, const void* data) {
        glBufferSubData(static_cast<GLenum>(target), offset, size, data);
    }
};

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_BUFFER_HPP
