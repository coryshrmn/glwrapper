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
