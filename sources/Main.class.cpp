#include "Main.class.hpp"

#include <stdexcept>
#include <iostream>
#include <ctime>

std::string const Main::_Data_place("../data/");

std::vector<std::string>
Main::pack_args(int argc, char *argv[])
{
	std::vector<std::string>	args(static_cast<std::size_t>(argc));

	for (std::size_t i(0), len(static_cast<std::size_t>(argc)) ; i < len ; ++i)
		args[i] = argv[i];
	return args;
}

Main::Main(int argc, char *argv[]) :
	_args(pack_args(argc, argv)),
	_map("lili.map")
{
}



int
Main::run(void)
{
	int				key;
	timespec const	t{0, 16666667l};

	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
	glfwSetInputMode(_win, GLFW_STICKY_KEYS, GL_TRUE);

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->draw();
		glfwSwapBuffers(_win);
		glfwPollEvents();
		::nanosleep(&t, nullptr);
		key = glfwGetKey(_win, GLFW_KEY_ESCAPE);
	} while (key != GLFW_PRESS and not glfwWindowShouldClose(_win));
	return EXIT_SUCCESS;
}

void
Main::draw(void)
{
	_map.display();
}
