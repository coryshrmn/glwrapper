#ifndef GLWRAPPER_ERROR_HPP
#define GLWRAPPER_ERROR_HPP

#include "glwrapper/profile.hpp"

#include <stdexcept>

namespace glwrapper {

enum class ErrorCode : GLenum {
    NO_ERROR = GL_NO_ERROR,
    INVALID_ENUM = GL_INVALID_ENUM,
    INVALID_VALUE = GL_INVALID_VALUE,
    INVALID_OPERATION = GL_INVALID_OPERATION,
    STACK_OVERFLOW = GL_STACK_OVERFLOW,
    STACK_UNDERFLOW = GL_STACK_UNDERFLOW,
    OUT_OF_MEMORY = GL_OUT_OF_MEMORY,
    INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
    CONTEXT_LOST = GL_CONTEXT_LOST
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

#endif // #ifndef GLWRAPPER_ERROR_HPP
