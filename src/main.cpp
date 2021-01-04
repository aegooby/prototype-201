
#include "__common.hpp"
#include "engine.hpp"

#include <filesystem>

int main(int argc, char** argv)
{
    if constexpr (p201::debug)
    {
        std::cout << "IT'S PROTOTYPE 201 BITCH" << std::endl;
        std::cout << " * C++ version: ";
        if (P201_CPP_VER)
            std::cout << "C++" << P201_CPP_VER;
        else
            std::cout << "UNKOWN";
        std::cout << std::endl;
        std::cout << " * Working directory: ";
        std::cout << std::filesystem::current_path() << std::endl;
    }
    p201::engine engine;
    engine.start();

    return 0;
}
