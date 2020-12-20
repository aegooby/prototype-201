
#pragma once
#include "../__common.hpp"

#include <exception>
#include <initializer_list>
#include <stdexcept>

namespace p201
{

template<typename __value_type, size_t rows, size_t columns>
class st_table
{
public:
    using value_type             = __value_type;
    using reference              = value_type&;
    using const_reference        = const value_type&;
    using array_reference        = st_array<value_type, columns>&;
    using const_array_reference  = const st_array<value_type, columns>&;
    using iterator               = value_type*;
    using const_iterator         = const value_type*;
    using pointer                = value_type*;
    using const_pointer          = const value_type*;
    using array_pointer          = st_array<value_type, columns>*;
    using const_array_pointer    = const st_array<value_type, columns>*;
    using size_type              = size_t;
    using difference_type        = std::ptrdiff_t;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using self_type              = st_table<value_type, rows, columns>;
    using self_reference         = st_table<value_type, rows, columns>&;
    using const_self_reference   = const st_table<value_type, rows, columns>&;
    using self_rvalue_reference  = st_table<value_type, rows, columns>&&;

    template<typename ___value_type, size_t __rows, size_t __cols>
    friend class table;
    friend class st_table<value_type, rows, columns>;
    friend class st_array<value_type, columns>;

protected:
    st_array<value_type, columns> __data[rows];

public:
    st_table() = default;
    st_table(const table<value_type, rows, columns>& other)
    {
        memcpy(__data, other.__data,
               (rows) * sizeof(st_array<value_type, columns>));
    }
    st_table(table<value_type, rows, columns>&& other)
    {
        memcpy(__data, other.__data,
               (rows) * sizeof(st_array<value_type, columns>));
    }
    self_reference operator=(const table<value_type, rows, columns>& other)
    {
        memcpy(__data, other.__data,
               (rows) * sizeof(st_array<value_type, columns>));
        return *this;
    }
    self_reference operator=(table<value_type, rows, columns>&& other)
    {
        memcpy(__data, other.__data,
               (rows) * sizeof(st_array<value_type, columns>));
        return *this;
    }
    st_table(const std::initializer_list<value_type>& list)
    {
        if (list.size() > columns * rows)
            throw std::overflow_error(
                "p201::Array: Initializer list is larger than array");
        if (!list.size()) memset(__data, 0, data_size());
        for (size_type offset = 0; offset < list.size(); ++offset)
        { *(iterator(__data) + offset) = *(iterator(list.begin()) + offset); }
    }
    inline __attribute__((always_inline)) self_reference
    operator=(const std::initializer_list<value_type>& list)
    {
        if (list.size() > columns * rows)
            throw std::overflow_error(
                "p201::Array: Initializer list is larger than array");
        if (!list.size()) memset(__data, 0, data_size());
        for (size_type offset = 0; offset < list.size(); ++offset)
        { *(iterator(__data) + offset) = *(iterator(list.begin()) + offset); }
        return *this;
    }
    inline __attribute__((always_inline)) pointer data() noexcept
    {
        return __data->data();
    }
    inline __attribute__((always_inline)) const_pointer data() const noexcept
    {
        return __data->data();
    }
    inline __attribute__((always_inline)) constexpr reference
    at(size_type column, size_type row)
    {
        if (column >= rows || row >= columns)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[column][row];
    }
    inline __attribute__((always_inline)) constexpr const_reference
    at(size_type column, size_type row) const
    {
        if (column >= rows || row >= columns)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[column][row];
    }
    inline __attribute__((always_inline)) constexpr array_reference
    at(size_type index)
    {
        if (index >= rows)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr const_array_reference
    at(size_type index) const
    {
        if (index >= rows)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr array_reference
    operator[](size_type index)
    {
        if (index >= rows)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }
    inline __attribute__((always_inline)) constexpr const_array_reference
    operator[](size_type index) const
    {
        if (index >= rows)
            throw std::out_of_range("p201::Array::at: Element is out of range");
        return __data[index];
    }

    inline __attribute__((always_inline)) constexpr reference front()
    {
        return *(pointer(__data));
    }
    inline __attribute__((always_inline)) constexpr const_reference
    front() const
    {
        return *(const_pointer(__data));
    }
    inline __attribute__((always_inline)) constexpr reference back()
    {
        return *(pointer(__data) +
                 ((rows * columns) > 0 ? (rows * columns) - 1 : 0));
    }
    inline __attribute__((always_inline)) constexpr const_reference back() const
    {
        return *(const_pointer(__data) +
                 ((rows * columns) > 0 ? (rows * columns) - 1 : 0));
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
        return iterator(__data) + rows * columns;
    }
    inline __attribute__((always_inline)) constexpr const_iterator end() const
    {
        return const_iterator(__data) + rows * columns;
    }
    inline __attribute__((always_inline)) constexpr const_iterator cend() const
    {
        return const_iterator(__data) + rows * columns;
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
        return reverse_iterator(__data) + rows * columns;
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    rend() const
    {
        return const_reverse_iterator(__data) + rows * columns;
    }
    inline __attribute__((always_inline)) constexpr const_reverse_iterator
    crend() const
    {
        return const_reverse_iterator(__data) + rows * columns;
    }

    inline __attribute__((always_inline)) constexpr bool empty() const noexcept
    {
        return (!bool(rows * columns));
    }
    inline __attribute__((always_inline)) constexpr size_type
    size() const noexcept
    {
        return rows * columns;
    }
    inline __attribute__((always_inline)) constexpr size_type
    elem_size() const noexcept
    {
        return sizeof(value_type);
    }
    inline __attribute__((always_inline)) constexpr size_type
    data_size() const noexcept
    {
        return sizeof(value_type) * rows * columns;
    }
    inline __attribute__((always_inline)) void fill(const_reference value)
    {
        for (auto& i : *this) i = value;
    }
};

} // namespace p201
