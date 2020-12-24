
#pragma once
#include "__common.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

namespace p201
{

template<size_t m, size_t n>
using matrix     = boost::numeric::ublas::bounded_matrix<float, m, n>;
using matrix_3_3 = matrix<3, 3>;

template<size_t n>
using vector   = boost::numeric::ublas::bounded_vector<float, n>;
using vector_2 = vector<2>;
using vector_3 = vector<3>;

} // namespace p201
