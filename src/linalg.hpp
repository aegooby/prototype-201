
#pragma once
#include "__common.hpp"

#include <Eigen/Dense>
// #include <boost/numeric/ublas/io.hpp>
// #include <boost/numeric/ublas/matrix.hpp>
// #include <boost/numeric/ublas/matrix_proxy.hpp>
// #include <boost/numeric/ublas/vector.hpp>

namespace p201
{

namespace eigen = Eigen;

template<size_t m, size_t n>
using matrix   = eigen::Matrix<float, m, n>;
using matrix_3 = matrix<3, 3>;

template<size_t n>
using vector   = matrix<n, 1>;
using vector_2 = vector<2>;
using vector_3 = vector<3>;

static const float sqrt_2 = std::sqrt(2.0f);
static const float sqrt_3 = std::sqrt(3.0f);
static const float sqrt_6 = std::sqrt(6.0f);

} // namespace p201
