
#pragma once
#include "../__common.hpp"

#include <exception>
#include <initializer_list>
#include <stdexcept>

namespace p201
{

template<typename __value_type, size_t __size>
class st_array
{
public:
    using value_type             = __value_type;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using size_type              = size_t;
    using difference_type        = std::ptrdiff_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using self_type              = st_array<value_type, __size>;
    using self_reference         = st_array<value_type, __size>&;
    using const_self_reference   = const st_array<value_type, __size>&;
    using self_rvalue_reference  = st_array<value_type, __size>&&;

    template<typename ____value_type, size_t __size__>
    friend class array;
    friend class st_array<value_type, __size>;
    template<typename ___value_type, size_t rows, size_t columns>
    friend class st_table;
    template<typename ___value_type, size_t rows, size_t columns>
    friend class table;

protected:
    value_type __data[__size > 0 ? __size : 1];

public:
    st_array() = default;
    st_array(const array<value_type, __size>& other)
    {
        memcpy(__data, other.__data,
               (__size > 0 ? __size : 1) * sizeof(value_type));
    }
    st_array(array<value_type, __size>&& other)
    {
        memcpy(__data, other.__data,
               (__size > 0 ? __size : 1) * sizeof(value_type));
    }
    self_reference operator=(const array<value_type, __size>& other)
    {
        memcpy(__data, other.__data,
               (__size > 0 ? __size : 1) * sizeof(value_type));
        return *this;
    }
    self_reference operator=(array<value_type, __size>&& other)
    {
        memcpy(__data, other.__data,
               (__size > 0 ? __size : 1) * sizeof(value_type));
        return *this;
    }
    st_array(const std::initializer_list<value_type>& list)
    {
        if (list.size() > __size)
            throw std::overflow_error(
                "p201::Array: Initializer list is larger than array");
        for (size_type offset = 0; offset < list.size(); ++offset)
        { *(iterator(__data) + offset) = *(iterator(list.begin()) + offset); }
    }
    inline __attribute__((always_inline)) self_reference
    operator=(const std::initializer_list<value_type>& list)
    {
        if (list.size() > __size)
            throw std::overflow_error(
                "p201::Array: Initializer list is larger than array");
        if (!list.size()) memset(__data, 0, data_size());
        for (size_type offset = 0; offset < list.size(); ++offset)
        { *(iterator(__data) + offset) = *(iterator(list.begin()) + offset); }
        return *this;
    }
    inline __attribute__((always_inline)) pointer data() noexcept
    {
        return __data;
    }
    inline __attribute__((always_inline)) const_pointer data() const noexcept
    {
        return __data;
    }
    inline __attribute__((always_inline)) constexpr reference
    at(size_type index)
    {
        if (index >= __size)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr const_reference
    at(size_type index) const
    {
        if (index >= __size)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr reference
    operator[](size_type index)
    {
        if (index >= __size)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr const_reference
    operator[](size_type index) const
    {
        if (index >= __size)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr reference front()
    {
        return *__data;
    }
    inline __attribute__((always_inline)) constexpr const_reference
    front() const
    {
        return *__data;
    }
    inline __attribute__((always_inline)) constexpr reference back()
    {
        return *(__data + (__size > 0 ? __size - 1 : 0));
    }
    inline __attribute__((always_inline)) constexpr const_reference back() const
    {
        return *(__data + (__size > 0 ? __size - 1 : 0));
    }

    inline __attribute__((always_inline)) constexpr iterator begin()
    {
        return iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr const_iterator begin() const
    {
        return const_iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr const_iterator
    cbegin() const
    {
        return const_iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr iterator end()
    {
        return iterator(__data + __size);
    }
    inline __attribute__((always_inline)) constexpr const_iterator end() const
    {
        return const_iterator(__data + __size);
    }
    inline __attribute__((always_inline)) constexpr const_iterator cend() const
    {
        return const_iterator(__data + __size);
    }

    inline __attribute__((always_inline)) constexpr reverse_iterator rbegin()
    {
        return reverse_iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    rbegin() const
    {
        return const_reverse_iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    crbegin() const
    {
        return const_reverse_iterator(__data);
    }
    inline __attribute__((always_inline)) constexpr reverse_iterator rend()
    {
        return reverse_iterator(__data + __size);
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    rend() const
    {
        return const_reverse_iterator(__data + __size);
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    crend() const
    {
        return const_reverse_iterator(__data + __size);
    }

    inline __attribute__((always_inline)) constexpr bool empty() const noexcept
    {
        return (!bool(__size));
    }
    inline __attribute__((always_inline)) constexpr size_type
    size() const noexcept
    {
        return __size;
    }
    inline __attribute__((always_inline)) constexpr size_type
    elem_size() const noexcept
    {
        return sizeof(value_type);
    }
    inline __attribute__((always_inline)) constexpr size_type
    data_size() const noexcept
    {
        return sizeof(value_type) * __size;
    }
    inline __attribute__((always_inline)) void fill(const_reference value)
    {
        for (auto& i : *this) i = value;
    }
};

} // namespace p201
