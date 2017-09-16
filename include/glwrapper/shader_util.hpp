#ifndef SHADER_UTIL_HPP
#define SHADER_UTIL_HPP

#include "glwrapper/shader.hpp"

#include <sstream>
#include <stdexcept>

namespace glwrapper {

/**
 * @brief Create and compile a shader.
 * @param shaderType
 * @param source
 * @return compiled shader
 * @throws std::runtime_error   compilation failed
 * @throws std::bad_alloc       compilation failed and error message allocation failed
 */
inline Shader shaderFromSource(ShaderType shaderType, std::string_view source)
{
    Shader shader(shaderType);
    shader.setSource(source);
    shader.compile();

    if(shader.getCompileSucceeded()) {
        return std::move(shader);
    }

    std::ostringstream sstr;
    sstr << "Shader compilation failed. Type \"" << shaderType << "\"\n"
         << shader.getInfoLogAlloc().first.get();

    throw std::runtime_error(sstr.str());
}

} // namespace glwrapper


#endif // SHADER_UTIL_HPP
