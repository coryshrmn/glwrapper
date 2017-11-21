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
#ifndef GLWRAPPER_TEXTURE_HPP
#define GLWRAPPER_TEXTURE_HPP

namespace glwrapper {

namespace detail {

    struct TextureDeleter {
        void operator()(GLuint handle) {
            glDeleteTextures(1, &handle);
        }
    };

    using TextureResource = cwrapper::Resource<GLuint, TextureDeleter>;

} // namespace detail

enum class TextureTarget : GLenum
{
    T_1D = GL_TEXTURE_1D,
    T_2D = GL_TEXTURE_2D,
    T_3D = GL_TEXTURE_3D,
    T_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
    T_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
    T_RECTANGLE = GL_TEXTURE_RECTANGLE,
    T_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
    T_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
    T_BUFFER = GL_TEXTURE_BUFFER,
    T_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
    T_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY
};


class Texture
{
private:
    detail::TextureResource textureResource {};

public:
    Texture() = default;

    void generate() {
        GLuint handle;
        glGenTextures(1, &handle);
        textureResource = detail::TextureResource{handle};
    }

#ifdef GLWRAPPER_SUPPORTS_DSA
    void create(TextureTarget target) {
        GLuint handle;
        glCreateTextures(static_cast<GLenum>(target), 1, &handle);
        textureResource = detail::TextureResource{handle};
    }
#endif

    bool exists() const {
        return textureResource.getHandle() != 0;
    }

    void bind(TextureTarget target) const {
        glBindTexture(static_cast<GLenum>(target), textureResource.getHandle());
    }

    static void unbind(TextureTarget target) {
        glBindTexture(static_cast<GLenum>(target), 0);
    }
};

} // namespace glwrapper

#endif // GLWRAPPER_TEXTURE_HPP
