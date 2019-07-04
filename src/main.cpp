
#include	"__common.hpp"
#include	"core_engine.hpp"
#include	"filesystem.hpp"

int	main(int argc, char** argv)
{
	try
	{
		td::core_engine	core_engine = td::core_engine("test", 480, 360, false);
		core_engine.start();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	
	return 0;
}
