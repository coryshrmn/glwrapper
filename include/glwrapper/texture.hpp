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

enum class TexturePName : GLenum
{
    DEPTH_STENCIL_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
    BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
    COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC,
    COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
    LOD_BIAS = GL_TEXTURE_LOD_BIAS,
    MIN_FILTER = GL_TEXTURE_MIN_FILTER,
    MAG_FILTER = GL_TEXTURE_MAG_FILTER,
    MIN_LOD = GL_TEXTURE_MIN_LOD,
    MAX_LOD = GL_TEXTURE_MAX_LOD,
    MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
    SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
    SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
    SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
    SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
    WRAP_S = GL_TEXTURE_WRAP_S,
    WRAP_T = GL_TEXTURE_WRAP_T,
    WRAP_R = GL_TEXTURE_WRAP_R,
    BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
    SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA
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

#ifdef GLWRAPPER_SUPPORTS_DSA
    // TODO DSA parameter (glTextureParameter...)
#endif

    template <typename T>
    static void parameter(TexturePName pname, T param);
    // TODO

    template <typename T>
    static T getParameter(TexturePName pname);
    // TODO

};

} // namespace glwrapper

#endif // GLWRAPPER_TEXTURE_HPP
