#ifndef GLWRAPPER_ERROR_HPP
#define GLWRAPPER_ERROR_HPP

#include <stdexcept>

namespace glwrapper {

enum class ErrorCode : GLEnum {
    NO_ERROR = 0,
    INVALID_ENUM = 0x0500,
    INVALID_VALUE = 0x0501,
    INVALID_OPERATION = 0x0502,
    STACK_OVERFLOW = 0x0503,
    STACK_UNDERFLOW = 0x0504,
    OUT_OF_MEMORY = 0x0505,
    INVALID_FRAMEBUFFER_OPERATION = 0x0506,
    CONTEXT_LOST = 0x0507,
    TABLE_TOO_LARGE = 0x8031
};

inline const char* getErrorName(ErrorCode errorCode) {
    switch(errorCode) {
    case NO_ERROR: return "NO_ERROR";
    case INVALID_ENUM: return "INVALID_ENUM";
    case INVALID_VALUE: return "INVALID_VALUE";
    case INVALID_OPERATION: return "INVALID_OPERATION";
    case STACK_OVERFLOW: return "STACK_OVERFLOW";
    case STACK_UNDERFLOW: return "STACK_UNDERFLOW";
    case OUT_OF_MEMORY: return "OUT_OF_MEMORY";
    case INVALID_FRAMEBUFFER_OPERATION: return "INVALID_FRAMEBUFFER_OPERATION";
    case CONTEXT_LOST: return "CONTEXT_LOST";
    case TABLE_TOO_LARGE: return "TABLE_TOO_LARGE";
    default: return "UNKNOWN_ERROR";
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

    const char* what() const override {
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
