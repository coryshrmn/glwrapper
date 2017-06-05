#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/error.hpp"

TEST(Error, NoError) {
    Context context;
    EXPECT_EQ(glwrapper::getErrorCode(), glwrapper::ErrorCode::NO_ERROR);
}
