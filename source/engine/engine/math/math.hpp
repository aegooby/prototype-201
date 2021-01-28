
#pragma once
#include "../physx.hpp"

#include <__common.hpp>
#include <forge/math.hpp>

namespace p201
{

using vector_2  = forge::vector_2;
using vector_3  = forge::vector_3;
using matrix_33 = forge::matrix_33;
using matrix_32 = forge::matrix_32;

vector_3        convert(const px::vector_3&);
vector_3        convert(const px::vector_3ext&);
px::vector_3    convert(const vector_3&);
px::vector_3ext convert_ext(const vector_3&);
} // namespace p201