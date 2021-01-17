
#pragma once
#include <__common.hpp>
#include <physx.hpp>

#if defined(Success)
#    undef Success
#endif
#include <Eigen/Dense>

namespace p201
{

namespace eigen = Eigen;

template<std::size_t m, std::size_t n>
using matrix    = eigen::Matrix<float, m, n>;
using matrix_33 = matrix<3, 3>;
using matrix_23 = matrix<2, 3>;

template<std::size_t n>
using vector   = matrix<n, 1>;
using vector_2 = vector<2>;
using vector_3 = vector<3>;

static const float sqrt_2 = std::sqrt(2.0f);
static const float sqrt_3 = std::sqrt(3.0f);
static const float sqrt_6 = std::sqrt(6.0f);

float distance(const vector_3& __a, const vector_3& __b);

vector_3     convert(const px::vector_3& vector);
vector_3     convert(const px::vector_3ext& vector);
px::vector_3 convert(const vector_3& vector);

vector_2 reduce(const vector_3& vector);
} // namespace p201