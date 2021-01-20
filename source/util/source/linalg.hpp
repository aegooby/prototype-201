
#pragma once
#include <__common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <physx.hpp>

namespace p201
{

using matrix_33 = glm::fmat3x3;
using matrix_32 = glm::fmat3x2;

using vector_2 = glm::fvec2;
using vector_3 = glm::fvec3;

static const float sqrt_2 = std::sqrt(2.0f);
static const float sqrt_3 = std::sqrt(3.0f);
static const float sqrt_6 = std::sqrt(6.0f);

float distance(const vector_3& __a, const vector_3& __b);

vector_3        convert(const px::vector_3&);
vector_3        convert(const px::vector_3ext&);
px::vector_3    convert(const vector_3&);
px::vector_3ext convert_ext(const vector_3&);

vector_2 reduce(const vector_3&);
} // namespace p201
