
#include "__common.hpp"
#include "engine.hpp"

#include <cstdlib>
#include <filesystem>

int main(int argc, char** argv)
{
    debug(std::cout << "Working directory (cmake): ");
    debug(std::cout << (std::getenv("CMAKE_SOURCE_DIR") ?: "not found"));
    debug(std::cout << std::endl);
    p201::engine engine = p201::engine("prototype 201");
    engine.start();

    return 0;
}
