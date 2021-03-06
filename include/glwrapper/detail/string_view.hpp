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
#ifndef GLWRAPPER_STRING_VIEW_HPP
#define GLWRAPPER_STRING_VIEW_HPP

/*
string_view is new in C++17, but GLWrapper only requires C++11.
GLWrapper supports string_view if it is available, and provides stx/string_view.hpp as a shim.

You can define GLWRAPPER_BOOST_STRING_VIEW to use boost's implementation.

If available, GLWrapper will load <string_view>, or <experimental/string_view>.

As a fallback, "stx/string_view.hpp" is shipped with GLWrapper, from https://github.com/tcbrindle/cpp17_headers
*/

#if defined(GLWRAPPER_BOOST_STRING_VIEW)
    #include <boost/utility/string_view.hpp>
    namespace glwrapper {
    namespace detail {
    using boost::string_view;
    }
    }
#elif __cplusplus >= 201703L
    #include <string_view>
    namespace glwrapper {
    namespace detail {
    using std::string_view;
    }
    }
// It seems no platforms define __cpp_lib_experimental_string_view 
// stx has better code to check if it's available
#elif defined(__cpp_lib_experimental_string_view)
    #include <experimental/string_view>
    namespace glwrapper {
    namespace detail {
    using std::experimental::string_view;
    }
    }
#else
    #include "stx/string_view.hpp"
    namespace glwrapper {
    namespace detail {
    using stx::string_view;
    }
    }
#endif

#endif // #ifndef GLWRAPPER_STRING_VIEW_HPP
