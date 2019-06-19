
#include	"__common.hpp"
#include	"core_engine.hpp"

int	main(int argc, char** argv)
{
	try
	{
		td::core_engine	core_engine = td::core_engine("test", 1280, 720);
		core_engine.add_object(std::make_unique<td::character>());
		core_engine.start();
	}
	catch (std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return 1;
	}
	
	return 0;
}
