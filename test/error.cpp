#include "gtest/gtest.h"

#include "glwrapper/error.hpp"

TEST(Error, NoError) {
    //EXPECT_EQ(glwrapper::getErrorCode(), glwrapper::ErrorCode::NO_ERROR);
    EXPECT_EQ(glwrapper::ErrorCode::NO_ERROR, glwrapper::ErrorCode::NO_ERROR);
}
