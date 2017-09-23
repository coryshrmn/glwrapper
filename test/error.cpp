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
