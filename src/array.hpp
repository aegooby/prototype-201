
#pragma once
#include "__common.hpp"
#include "array/array_base.hpp"
#include "array/st_array_base.hpp"
#include "array/st_table.hpp"
#include "array/table.hpp"
#include "memory.hpp"

#include <array>
#include <list>
#include <vector>

namespace p201
{

template<typename value_type, size_t __size>
array<value_type, __size>::array(const st_array<value_type, __size>& other)
{
    this->allocate(__size > 0 ? __size : 1);
    memcpy(__data, other.__data,
           (__size > 0 ? __size : 1) * sizeof(value_type));
}
template<typename value_type, size_t __size>
array<value_type, __size>::array(st_array<value_type, __size>&& other)
{
    this->allocate(__size > 0 ? __size : 1);
    memcpy(__data, other.__data,
           (__size > 0 ? __size : 1) * sizeof(value_type));
}
template<typename value_type, size_t __size>
array<value_type, __size>&
array<value_type, __size>::operator=(const st_array<value_type, __size>& other)
{
    memcpy(__data, other.__data,
           (__size > 0 ? __size : 1) * sizeof(value_type));
    return *this;
}
template<typename value_type, size_t __size>
array<value_type, __size>&
array<value_type, __size>::operator=(st_array<value_type, __size>&& other)
{
    memcpy(__data, other.__data,
           (__size > 0 ? __size : 1) * sizeof(value_type));
    return *this;
}

template<typename value_type, size_t rows, size_t columns>
table<value_type, rows, columns>::table(
    const st_table<value_type, rows, columns>& other)
{
    this->allocate(rows);
    memcpy(__data, other.__data,
           (rows) * sizeof(st_array<value_type, columns>));
}
template<typename value_type, size_t rows, size_t columns>
table<value_type, rows, columns>::table(
    st_table<value_type, rows, columns>&& other)
{
    this->allocate(rows);
    memcpy(__data, other.__data,
           (rows) * sizeof(st_array<value_type, columns>));
}
template<typename value_type, size_t rows, size_t columns>
table<value_type, rows, columns>& table<value_type, rows, columns>::operator=(
    const st_table<value_type, rows, columns>& other)
{
    memcpy(__data, other.__data,
           (rows) * sizeof(st_array<value_type, columns>));
    return *this;
}
template<typename value_type, size_t rows, size_t columns>
table<value_type, rows, columns>& table<value_type, rows, columns>::operator=(
    st_table<value_type, rows, columns>&& other)
{
    memcpy(__data, other.__data,
           (rows) * sizeof(st_array<value_type, columns>));
    return *this;
}

} // namespace p201
