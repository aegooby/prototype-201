
#include "__common.hpp"

#include "termcolor.hpp"

#include <filesystem>
#include <iostream>

namespace p201
{
void __print_header__()
{
    std::cout << termcolor::bold << "IT'S PROTOTYPE 201 BITCH"
              << termcolor::reset << std::endl;
    std::cout << " * C++ version: C++" << std::to_string(P201_CPP_VER)
              << std::endl;
    std::cout << " * Working directory: " << std::filesystem::current_path()
              << std::endl;
}
} // namespace p201
