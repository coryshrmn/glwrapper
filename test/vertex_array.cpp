#include "gtest/gtest.h"

#include "context.hpp"

#include "glwrapper/profile.hpp"

#include "glwrapper/vertex_array.hpp"

#include <iostream>
#include <string>
#include <utility>

using glwrapper::VertexArray;

TEST(VertexArray, Generate) {
    Context context;

    VertexArray vertexArray;
    ASSERT_EQ(vertexArray.exists(), false);
    vertexArray.generate();
    ASSERT_EQ(vertexArray.exists(), true);
}

TEST(VertexArray, Create) {
    Context context;

    VertexArray vertexArray;
    ASSERT_EQ(vertexArray.exists(), false);
    vertexArray.create();
    ASSERT_EQ(vertexArray.exists(), true);
}

TEST(VertexArray, Delete) {
    Context context;

    VertexArray vertexArray;
    ASSERT_EQ(vertexArray.exists(), false);
    vertexArray.generate();
    ASSERT_EQ(vertexArray.exists(), true);
    {
        VertexArray innerVertexArray {std::move(vertexArray)};
        ASSERT_EQ(innerVertexArray.exists(), true);
        ASSERT_EQ(vertexArray.exists(), false);
    }
    ASSERT_EQ(vertexArray.exists(), false);
}
