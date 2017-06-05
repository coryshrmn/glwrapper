#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/error.hpp"
#include "glwrapper/shader.hpp"

TEST(Error, NoError) {
    Context context;
    EXPECT_EQ(glwrapper::getErrorCode(), glwrapper::ErrorCode::NO_ERROR);
}

TEST(Error, InvalidEnum) {
    Context context;
    glwrapper::Shader shader { static_cast<glwrapper::ShaderType>(-1) };
    EXPECT_EQ(glwrapper::getErrorCode(), glwrapper::ErrorCode::INVALID_ENUM);
}

TEST(Error, Check) {
    Context context;
    glwrapper::Shader shader { static_cast<glwrapper::ShaderType>(-1) };
    EXPECT_THROW(glwrapper::checkError(), glwrapper::Error);
}

TEST(Error, Name) {
    const char* what = nullptr;
    try {
        Context context;
        glwrapper::Shader shader { static_cast<glwrapper::ShaderType>(-1) };
        glwrapper::checkError();
    }
    catch(const std::exception& e) {
        what = e.what();
    }
    EXPECT_EQ(what, "INVALID_ENUM");
}
