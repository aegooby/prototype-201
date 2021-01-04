
#pragma once
#include "__common.hpp"

#include <Eigen/Dense>

namespace p201
{

namespace eigen = Eigen;

template<std::size_t m, std::size_t n>
using matrix   = eigen::Matrix<float, m, n>;
using matrix_3 = matrix<3, 3>;

template<std::size_t n>
using vector   = matrix<n, 1>;
using vector_2 = vector<2>;
using vector_3 = vector<3>;

static const float sqrt_2 = std::sqrt(2.0f);
static const float sqrt_3 = std::sqrt(3.0f);
static const float sqrt_6 = std::sqrt(6.0f);

inline float distance(const vector_3& __a, const vector_3& __b)
{
    return std::hypot(__a.x() - __b.x(), __a.y() - __b.y(), __a.z() - __b.z());
}

template<int n>
inline std::string to_string(const vector<n>& vector)
{
    std::string str = "(";
    for (std::size_t i = 0; i < n - 1; ++i)
        str += std::to_string(vector[i]) + ", ";
    str += std::to_string(vector[n - 1]) + ")";
    return str;
}

} // namespace p201
