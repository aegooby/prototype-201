
#include "util.hpp"

#include "linalg.hpp"

namespace p201
{
namespace util
{
vector_2 center(const SDL_FRect& rect)
{
    return vector_2(rect.x + rect.w / 2.0f, rect.y + rect.h / 2.0f);
}
SDL_FRect rect(const vector_2& center, float width, float height)
{
    SDL_FRect rect = { .w = width, .h = height };

    rect.x = center.x() - width / 2.0f;
    rect.y = center.y() - height / 2.0f;
    return rect;
}
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
} // namespace util
} // namespace p201
