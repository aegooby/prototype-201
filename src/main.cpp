
#include "__common.hpp"
#include "engine.hpp"

int main(int argc, char** argv)
{
    try
    {
        p201::engine engine = p201::engine("test", 480, 360, false);
        engine.start();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
