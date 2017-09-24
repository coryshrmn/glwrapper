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

#ifdef GLWRAPPER_SUPPORTS_DSA
TEST(VertexArray, Create) {
    Context context;

    VertexArray vertexArray;
    ASSERT_EQ(vertexArray.exists(), false);
    vertexArray.create();
    ASSERT_EQ(vertexArray.exists(), true);
}
#endif

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
