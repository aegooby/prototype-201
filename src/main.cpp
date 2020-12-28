
#include "__common.hpp"
#include "engine.hpp"

#include <filesystem>

int main(int argc, char** argv)
{
    debug(std::cout << "Working directory: ");
    debug(std::cout << std::filesystem::current_path() << std::endl);
    p201::engine engine = p201::engine("prototype 201");
    engine.start();

    return 0;
}
