#ifndef GLWRAPPER_ATTRIBUTE_HPP
#define GLWRAPPER_ATTRIBUTE_HPP

#include "glwrapper/glm_types.hpp"

#include <type_traits>

namespace glwrapper {

// a bit not used by any other source types
// we OR it with integral types, to represent normalized integer data
constexpr GLenum ATTRIBUTE_SOURCE_TYPE_NORMALIZATION_BIT = 0x4000;

// used as "type" param in glVertexAttribPointer()
enum class AttributeSourceType : GLenum
{
    // int or unnormalized floats of any size (1,2,3,4)
    BYTE = GL_BYTE,
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    SHORT = GL_SHORT,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    INT = GL_INT,
    UNSIGNED_INT = GL_UNSIGNED_INT,

    // normalized floats of any size (1,2,3,4)
    BYTE_NORMALIZED = 0x4000 | GL_BYTE,
    UNSIGNED_BYTE_NORMALIZED = 0x4000 | GL_UNSIGNED_BYTE,
    SHORT_NORMALIZED = 0x4000 | GL_SHORT,
    UNSIGNED_SHORT_NORMALIZED = 0x4000 | GL_UNSIGNED_SHORT,
    INT_NORMALIZED = 0x4000 | GL_INT,
    UNSIGNED_INT_NORMALIZED = 0x4000 | GL_UNSIGNED_INT,

    // floats of any size (1,2,3,4)
    HALF_FLOAT = GL_HALF_FLOAT,
    FLOAT = GL_FLOAT,
    DOUBLE = GL_DOUBLE,
    FIXED = GL_FIXED,

    // float 4
    INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,

    // float 3
    UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV
};

template <AttributeSourceType SourceType>
struct AttributeSourceTypeTraits
{
private:

    static constexpr GLenum cSourceType = static_cast<GLenum>(SourceType);

public:

    static constexpr bool normalized = (cSourceType & ATTRIBUTE_SOURCE_TYPE_NORMALIZATION_BIT) != 0;

    static constexpr bool integral =
        normalized
        || SourceType == AttributeSourceType::BYTE
        || SourceType == AttributeSourceType::UNSIGNED_BYTE
        || SourceType == AttributeSourceType::SHORT
        || SourceType == AttributeSourceType::UNSIGNED_SHORT
        || SourceType == AttributeSourceType::INT
        || SourceType == AttributeSourceType::UNSIGNED_INT;

    // 0 for any size
    static constexpr int size =
        (SourceType == AttributeSourceType::INT_2_10_10_10_REV
            || SourceType == AttributeSourceType::UNSIGNED_INT_2_10_10_10_REV) ? 4
        : SourceType == AttributeSourceType::UNSIGNED_INT_10F_11F_11F_REV ? 3
        : 0;
};

namespace detail {

// used by Attribute::pointer()
template <
    typename T,
    int Count,
    AttributeSourceType SourceType,
    typename = void,
    // prevent packed data from be used for wrong count
    typename = std::enable_if_t<
        AttributeSourceTypeTraits<SourceType>::size == 0
        || AttributeSourceTypeTraits<SourceType>::size == Count
    >
>
struct AttributePointer;

// float type
template <int Count, AttributeSourceType SourceType>
struct AttributePointer<float, Count, SourceType>
{
    void set(GLint location, GLsizei stride, const GLvoid* offset)
    {
        constexpr GLenum cSourceType = static_cast<GLenum>(SourceType);
        constexpr bool normalized = (cSourceType & ATTRIBUTE_SOURCE_TYPE_NORMALIZATION_BIT) != 0;

        glVertexAttribPointer(location, Count, cSourceType, normalized, stride, offset);
    }
};

// double type
template <int Count, AttributeSourceType SourceType>
struct AttributePointer<double, Count, SourceType>
{
    void set(GLint location, GLsizei stride, const GLvoid* offset)
    {
        constexpr GLenum cSourceType = static_cast<GLenum>(SourceType);

        if constexpr(SourceType == AttributeSourceType::DOUBLE) {
            // double with double source uses the L function
            glVertexAttribLPointer(location, Count, cSourceType, stride, offset);
        }
        else {
            // otherwise, same as float
            AttributePointer<float, Count, SourceType>{}.set(location, stride, offset);
        }
    }
};

// integral types
template <typename T, int Count, AttributeSourceType SourceType>
struct AttributePointer<
    T,
    Count,
    SourceType,
    std::enable_if_t<
        std::is_integral<T>::value
        && AttributeSourceTypeTraits<SourceType>::integral
    >
>
{
    void set(GLint location, GLsizei stride, const GLvoid* offset)
    {
        constexpr GLenum cSourceType = static_cast<GLenum>(SourceType);

        glVertexAttribIPointer(location, Count, cSourceType, stride, offset);
    }
};

} // namespace detail


template <typename T, int Count = 1>
struct Attribute
{
public:

    GLint location = -1;

    bool exists() const
    {
        return location != -1;
    }

    void enable() const
    {
        glEnableVertexAttribArray(location);
    }

    void disable() const
    {
        glDisableVertexAttribArray(location);
    }

    template <AttributeSourceType SourceType>
    void pointer(int32_t stride = 0, const void* offset = nullptr) const
    {
        detail::AttributePointer<T, Count, SourceType>{}.set(location, stride, offset);
    }
};

class AttributeEnableGuard
{
private:

    // Attribute type doesn't matter,
    // we only enable and disable it
    Attribute<float, 1> _attribute {};

public:

    AttributeEnableGuard() = default;

    AttributeEnableGuard(const AttributeEnableGuard&) = delete;

    AttributeEnableGuard(AttributeEnableGuard&& src)
        : _attribute(src._attribute)
    {
        src._attribute = {};
    }

    AttributeEnableGuard& operator=(const AttributeEnableGuard&) = delete;

    AttributeEnableGuard& operator=(AttributeEnableGuard&& src)
    {
        this->~AttributeEnableGuard();
        _attribute = src._attribute;
        src._attribute = {};
        return *this;
    }

    template <typename T, int Count>
    AttributeEnableGuard(Attribute<T, Count> attribute)
        : _attribute{ attribute.location }
    {
        _attribute.enable();
    }

    ~AttributeEnableGuard()
    {
        if(_attribute.exists()) {
            _attribute.disable();
            _attribute = {};
        }
    }
};

} // namespace glwrapper

#endif // GLWRAPPER_ATTRIBUTE_HPP
