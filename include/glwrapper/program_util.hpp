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
#ifndef PROGRAM_UTIL_HPP
#define PROGRAM_UTIL_HPP

#include "glwrapper/program.hpp"

#include <sstream>
#include <stdexcept>
#include <functional>

namespace glwrapper
{

/**
 * @brief Create, attach shaders to, and link a program.
 * @param shaderList
 * @return linked program
 * @throws std::runtime_error   link failed
 * @throws std::bad_alloc       link failed and error message allocation failed
 */
inline Program programFromShaders(std::initializer_list<std::reference_wrapper<const Shader>> shaderList) {
    Program program;
    program.create();

    for(const Shader& shader : shaderList) {
        program.attachShader(shader);
    }

    program.link();

    if(program.getLinkSucceeded()) {
        return program;
    }

    std::ostringstream sstr;
    sstr << "Program link failed.\n"
         << program.getInfoLogAlloc().first.get();

    throw std::runtime_error(sstr.str());
}

} // namespace glwrapper

#endif // PROGRAM_UTIL_HPP
