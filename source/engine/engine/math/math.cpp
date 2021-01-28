
#include "math.hpp"

namespace p201
{
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
}