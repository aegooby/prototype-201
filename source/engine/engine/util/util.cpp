
#include "util.hpp"

#include <sstream>

namespace p201
{
namespace util
{
void sleep(std::size_t ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
std::string to_string(const px::vector_3& vector)
{
    std::string str = "(" + std::to_string(vector.x);
    str += ", " + std::to_string(vector.y);
    str += ", " + std::to_string(vector.z) + ")";
    return str;
}
std::string to_string(const px::vector_3ext& vector)
{
    std::string str = "(" + std::to_string(vector.x);
    str += ", " + std::to_string(vector.y);
    str += ", " + std::to_string(vector.z) + ")";
    return str;
}
std::string to_string(std::thread::id id)
{
    std::stringstream str;
    str << termcolor::colorize << termcolor::bold << termcolor::cyan
        << "<thread " << id << ">" << termcolor::reset;
    return str.str();
}
std::string to_string(const vector_2& vector)
{
    std::string str = "(" + std::to_string(vector.x);
    str += ", " + std::to_string(vector.y) + ")";
    return str;
}
std::string to_string(const vector_3& vector)
{
    std::string str = "(" + std::to_string(vector.x);
    str += ", " + std::to_string(vector.y);
    str += ", " + std::to_string(vector.z) + ")";
    return str;
}
} // namespace util
} // namespace p201
