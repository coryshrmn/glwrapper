#ifndef PROGRAM_UTIL_HPP
#define PROGRAM_UTIL_HPP

#include "glwrapper/program.hpp"

#include <sstream>
#include <stdexcept>

namespace glwrapper
{

/**
 * @brief Create, attach shaders to, and link a program.
 * @param shaderList
 * @return linked program
 * @throws std::runtime_error   link failed
 * @throws std::bad_alloc       link failed and error message allocation failed
 */
static Program programFromShaders(std::initializer_list<const Shader&> shaderList) {
    Program program;
    program.create();

    for(const Shader& shader : shaderList) {
        program.attachShader(shader);
    }

    program.link();

    if(program.getLinkSucceeded()) {
        return std::move(program);
    }

    std::ostringstream sstr;
    sstr << "Program link failed.\n"
         << program.getInfoLogAlloc().first.get();

    throw std::runtime_error(sstr.str());
}


} // namespace glwrapper

#endif // PROGRAM_UTIL_HPP
