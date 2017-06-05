#ifndef GLWRAPPER_STRING_VIEW_HPP
#define GLWRAPPER_STRING_VIEW_HPP

// auto detects standard or experimental string view.
// define GLWRAPPER_BOOST_STRING_VIEW to use boost string view

#if __cplusplus >= 201703L
    #include <string_view>
    namespace glwrapper {
    using std::string_view;
    }
#elif defined(__cpp_lib_experimental_string_view)
    #include <experimental/string_view>
    namespace glwrapper {
    using std::experimental::string_view;
    }
#elif defined(GLWRAPPER_BOOST_STRING_VIEW)
    #include <boost/utility/string_view.hpp>
    namespace glwrapper {
    using boost::string_view;
    }
#else
    #define GLWRAPPER_NO_STRING_VIEW
#endif

#endif // #ifndef GLWRAPPER_STRING_VIEW_HPP
