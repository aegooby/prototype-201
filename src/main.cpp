
#include "__common.hpp"
#include "engine.hpp"

#include <filesystem>

int main(int argc, char** argv)
{
    p201::engine engine;
    if constexpr (p201::debug)
    {
        std::cout << p201::util::tc::bold << "IT'S PROTOTYPE 201 BITCH"
                  << p201::util::tc::reset << std::endl;
        std::cout << " * C++ version: "
                  << (P201_CPP_VER ? "C++" + std::to_string(P201_CPP_VER)
                                   : "UNKNOWN")
                  << std::endl;
        std::cout << " * Working directory: " << std::filesystem::current_path()
                  << std::endl;
        std::cout << " * PhysX foundation initializing: "
                  << (p201::engine::physx_foundation ? "success" : "failure")
                  << std::endl;
        std::cout << " * PhysX main initializing: "
                  << (p201::engine::physx_sdk ? "success" : "failure")
                  << std::endl;
        std::cout << " * PhysX cooking initializing: "
                  << (p201::engine::physx_cooking ? "success" : "failure")
                  << std::endl;
    }
    engine.start();

    return 0;
}
