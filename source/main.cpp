
#include <__common.hpp>
#include <game.hpp>

#if defined(main)
#    undef main
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    if constexpr (p201::__debug__) { p201::__print_header__(); }
    p201::game game;

    return 0;
}
