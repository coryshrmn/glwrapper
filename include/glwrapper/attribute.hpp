//#ifndef GLWRAPPER_ATTRIBUTE_HPP
//#define GLWRAPPER_ATTRIBUTE_HPP
//
//#include "glwrapper/glm_types.hpp"
//
//#include <type_traits>
//
//namespace glwrapper {
//
//// used as "type" param in glVertexAttribPointer()
//enum class AttributeDataType : GLenum
//{
//    // int or floats of any size (1,2,3,4)
//    // floats are optionally normalized
//    BYTE = GL_BYTE,
//    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
//    SHORT = GL_SHORT,
//    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
//    INT = GL_INT,
//    UNSIGNED_INT = GL_UNSIGNED_INT,
//
//    // float
//    HALF_FLOAT = GL_HALF_FLOAT,
//    FLOAT = GL_FLOAT,
//    DOUBLE = GL_DOUBLE,
//    FIXED = GL_FIXED,
//
//    // float 4
//    INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
//    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
//
//    // float 3
//    UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
//};
//
//template <typename T>
//struct Attribute
//{
//public:
//
//    GLint location = -1;
//
//    bool exists() const
//    {
//        return location != -1;
//    }
//
//    void enable() const
//    {
//        glEnableVertexAttribArray(location);
//    }
//
//    void disable() const
//    {
//        glDisableVertexAttribArray(location);
//    }
//
//
//    // TODO template glVertexAttribPointer()
//    // needs different signatures, for float with int data (normalized bool)
//
//    template <AttributeDataType T2, typename =
//    //void
//};
//
//template <typename T>
//class AttributeEnableGuard
//{
//private:
//
//    Attribute _attribute {};
//
//public:
//
//    AttributeEnableGuard() = default;
//
//    AttributeEnableGuard(Attribute attribute)
//        : _attribute(attribute)
//    {
//        _attribute.enable();
//    }
//
//    ~AttributeEnableGuard()
//    {
//        if(_attribute.exists()) {
//            _attribute.disable();
//            _attribute = {};
//        }
//    }
//};
//
//} // namespace glwrapper
//
//#endif // GLWRAPPER_ATTRIBUTE_HPP
