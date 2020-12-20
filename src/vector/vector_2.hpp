
#pragma once
#include "../__common.hpp"
#include "../array.hpp"
#include "../math_base.hpp"
#include "vector_base.hpp"

#include <exception>
#include <initializer_list>
#include <stdexcept>

namespace p201
{

template<typename value_type>
class vector<value_type, 2>
{
    static_assert(std::is_literal_type_v<value_type>);
    static_assert(std::is_arithmetic_v<value_type>);
    static_assert(std::is_floating_point_v<value_type>);
    static_assert(std::is_signed_v<value_type>);

    public:
    value_type x = value_type(), y = value_type();

    public:
    using self_reference       = vector<value_type, 2>&;
    using const_self_reference = const vector<value_type, 2>&;
    using self_type            = vector<value_type, 2>;
    using size_type            = size_t;
    using reference            = value_type&;
    using const_reference      = const value_type&;
    vector()                   = default;
    vector(value_type x, value_type y) : x(x), y(y) { }
    vector(const std::initializer_list<value_type>& list)
    {
        if (list.size() > 2)
            throw std::overflow_error(
                "p201::vector: Initializer list is larger than vector size");
        x = *(list.begin());
        y = *(list.begin() + 1);
    }
    inline __attribute__((always_inline)) self_reference
    operator=(const std::initializer_list<value_type>& list)
    {
        if (list.size() > 2)
            throw std::overflow_error(
                "p201::vector: Initializer list is larger than vector size");
        x = *(list.begin());
        y = *(list.begin() + 1);
        return *this;
    }
    inline __attribute__((always_inline)) self_reference
    operator=(const_self_reference other)
    {
        x = other.x;
        y = other.y;
        return *this;
    }
    inline __attribute__((always_inline)) constexpr reference
    at(size_type index)
    {
        switch (index)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                throw std::out_of_range(
                    "p201::vector::at: Element is out of range");
                break;
        }
    }
    inline __attribute__((always_inline)) constexpr const_reference
    at(size_type index) const
    {
        switch (index)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                throw std::out_of_range(
                    "p201::vector::at: Element is out of range");
                break;
        }
    }
    inline __attribute__((always_inline)) constexpr reference
    operator[](size_type index)
    {
        switch (index)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                throw std::out_of_range(
                    "p201::vector::at: Element is out of range");
                break;
        }
    }
    inline __attribute__((always_inline)) constexpr const_reference
    operator[](size_type index) const
    {
        switch (index)
        {
            case 0:
                return x;
                break;
            case 1:
                return y;
                break;
            default:
                throw std::out_of_range(
                    "p201::vector::at: Element is out of range");
                break;
        }
    }
    inline __attribute__((always_inline)) value_type norm() const
    {
        return std::sqrt(x * x + y * y);
    }
    inline __attribute__((always_inline)) self_type normalized() const
    {
        if (!*this) throw divide_by_zero("Cannot normalize zero vector");
        return (*this / norm());
    }
    inline __attribute__((always_inline)) void normalize()
    {
        *this /= norm();
    }
    inline __attribute__((always_inline)) void
    project(const_self_reference normal)
    {
        if (!*this) throw divide_by_zero("Cannot project zero vector");
        *this = projection(*this, normal);
    }
    inline __attribute__((always_inline)) self_type
    projected(const_self_reference normal) const
    {
        if (!*this) throw divide_by_zero("Cannot project zero vector");
        return projection(*this, normal);
    }
    inline __attribute__((always_inline)) void
    reflect(const_self_reference normal)
    {
        if (!*this) throw divide_by_zero("Cannot reflect zero vector");
        *this = reflection(*this, normal);
    }
    inline __attribute__((always_inline)) self_type
    reflected(const_self_reference normal) const
    {
        if (!*this) throw divide_by_zero("Cannot reflect zero vector");
        return reflection(*this, normal);
    }
    inline __attribute__((always_inline)) self_reference
    operator+=(const_self_reference other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    inline __attribute__((always_inline)) self_reference
    operator-=(const_self_reference other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    inline __attribute__((always_inline)) self_reference
    operator*=(value_type scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    inline __attribute__((always_inline)) self_reference
    operator/=(value_type scalar)
    {
        if (!bool(scalar)) throw divide_by_zero("Cannot divide by 0");
        x /= scalar;
        y /= scalar;
        return *this;
    }
    inline __attribute__((always_inline)) self_reference operator-()
    {
        *this *= -1;
        return *this;
    }
    inline __attribute__((always_inline)) self_reference operator+()
    {
        return *this;
    }
    inline __attribute__((always_inline)) constexpr static self_type zero()
    {
        return vector();
    }
    inline __attribute__((always_inline)) explicit operator bool() const
    {
        return (*this != this->zero());
    }
    inline __attribute__((always_inline)) bool operator!() const
    {
        return !(bool(this));
    }
};

//	2D vector rotation uses a 2x2 rotational matrix multiplied by the vector
//(expanded here)

template<typename value_type>
vector<value_type, 2> rotation(const vector<value_type, 2>& vec,
                               value_type                   angle)
{
    value_type            cast_angle = static_cast<value_type>(angle);
    vector<value_type, 2> result;
    value_type            cos_angle = cos(cast_angle);
    value_type            sin_angle = sin(cast_angle);
    result.at(0) = vec.at(0) * cos_angle - vec.at(1) * sin_angle;
    result.at(1) = vec.at(1) * cos_angle + vec.at(0) * sin_angle;
    return result;
}

template<typename value_type>
inline __attribute__((always_inline)) bool
operator==(const vector<value_type, 2>& one, const vector<value_type, 2>& two)
{

    return (one.x == two.x && one.y == two.y);
}

} // namespace p201
