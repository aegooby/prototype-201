
#include "linalg.hpp"

namespace p201
{
float distance(const vector_3& __a, const vector_3& __b)
{
    return std::hypot(__a.x - __b.x, __a.y - __b.y, __a.z - __b.z);
}
vector_3 convert(const px::vector_3& vector)
{
    return vector_3(vector.x, vector.y, vector.z);
}
vector_3 convert(const px::vector_3ext& vector)
{
    return vector_3(vector.x, vector.y, vector.z);
}
px::vector_3 convert(const vector_3& vector)
{
    return px::vector_3(vector.x, vector.y, vector.z);
}
px::vector_3ext convert_ext(const vector_3& vector)
{
    return px::vector_3ext(vector.x, vector.y, vector.z);
}
vector_2 reduce(const vector_3& vector)
{
    return vector_2(vector.x, vector.y);
}
} // namespace p201
