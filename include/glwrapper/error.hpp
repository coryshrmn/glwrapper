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
#ifndef GLWRAPPER_ERROR_HPP
#define GLWRAPPER_ERROR_HPP

#include "glwrapper/profile.hpp"

#include <stdexcept>
#include <ostream>

namespace glwrapper {

enum class ErrorCode : GLenum {
    NO_ERROR = GL_NO_ERROR,
    INVALID_ENUM = GL_INVALID_ENUM,
    INVALID_VALUE = GL_INVALID_VALUE,
    INVALID_OPERATION = GL_INVALID_OPERATION,
    STACK_OVERFLOW = 0x0503,
    STACK_UNDERFLOW = 0x0504,
    OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
    INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
    // GL_CONTEXT_LOST is not defined until OpenGL 4.5
    CONTEXT_LOST = 0x0507
};

inline const char* getErrorName(ErrorCode errorCode) {
    switch(errorCode) {
    case ErrorCode::NO_ERROR: return "NO_ERROR";
    case ErrorCode::INVALID_ENUM: return "INVALID_ENUM";
    case ErrorCode::INVALID_VALUE: return "INVALID_VALUE";
    case ErrorCode::INVALID_OPERATION: return "INVALID_OPERATION";
    case ErrorCode::STACK_OVERFLOW: return "STACK_OVERFLOW";
    case ErrorCode::STACK_UNDERFLOW: return "STACK_UNDERFLOW";
    case ErrorCode::OUT_OF_MEMORY: return "OUT_OF_MEMORY";
    case ErrorCode::INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
    case ErrorCode::CONTEXT_LOST: return "CONTEXT_LOST";
    default: return "UNKNOWN_ERROR";
    }
}

inline ErrorCode getErrorCode() {
    return static_cast<ErrorCode>(glGetError());
}

class Error : public std::exception {
    ErrorCode errorCode;

public:
    Error(ErrorCode errorCode)
        : errorCode(errorCode) {
    }

    ErrorCode getErrorCode() const {
        return errorCode;
    }

    const char* what() const noexcept override {
        return getErrorName(errorCode);
    }
};

// throws glwrapper::Error if glGetError() != NO_ERROR
inline void checkError() {
    ErrorCode errorCode = getErrorCode();
    if(errorCode != ErrorCode::NO_ERROR) {
        throw Error(errorCode);
    }
}

} // namespace glwrapper

inline std::ostream& operator<<(std::ostream& out, const glwrapper::ErrorCode& errorCode)
{
    return out << glwrapper::getErrorName(errorCode);
}

#endif // #ifndef GLWRAPPER_ERROR_HPP
