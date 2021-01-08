
#include "__common.hpp"
#include "engine.hpp"
#include "termcolor.hpp"

#include <filesystem>

int main(int argc, char** argv)
{
    p201::engine engine;
    if constexpr (p201::debug)
    {
        std::cout << termcolor::bold << "IT'S PROTOTYPE 201 BITCH"
                  << termcolor::reset << std::endl;
        std::cout << " * C++ version: "
                  << (P201_CPP_VER ? "C++" + std::to_string(P201_CPP_VER)
                                   : "UNKNOWN")
                  << std::endl;
        std::cout << " * Working directory: " << std::filesystem::current_path()
                  << std::endl;
    }
    engine.start();

    return 0;
}
