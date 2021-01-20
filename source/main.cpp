
#include <__common.hpp>
#include <core.hpp>

#if defined(main)
#    undef main
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    p201::engine engine;
    if constexpr (p201::__debug__) { p201::__print_header__(); }
    engine.start();

    return 0;
}
