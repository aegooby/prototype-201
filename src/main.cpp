
#include "__common.hpp"
#include "engine.hpp"

#include <filesystem>

int main(int argc, char** argv)
{
    if constexpr (p201::debug)
    {
        std::cout << "IT'S PROTOTYPE 201 BITCH" << std::endl;
        std::cout << " * C++ version: "
                  << (P201_CPP_VER ? "C++" + std::to_string(P201_CPP_VER)
                                   : "UNKNOWN")
                  << std::endl;
        std::cout << " * Working directory: " << std::filesystem::current_path()
                  << std::endl;
    }
    p201::engine engine;
    engine.start();

    return 0;
}
