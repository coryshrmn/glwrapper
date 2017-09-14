#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/profile.hpp"

#include "glwrapper/buffer.hpp"

using glwrapper::Buffer;
using glwrapper::BufferBindingTarget;
using glwrapper::BufferUsage;

TEST(Buffer, Create) {
    Context context;

    Buffer b;
    b.create();
    b.bind(BufferBindingTarget::ARRAY);
}
