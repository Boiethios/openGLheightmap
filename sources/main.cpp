#include "Main.class.hpp"

#include <iostream>

int main(int argc, char *argv[])
{
	try
	{
		return Main(argc, argv).run();
	}
	catch (std::exception const & e)
	{
		std::cout << "Exception: `" << e.what() << "`\n";
	}
	return EXIT_FAILURE;
}
