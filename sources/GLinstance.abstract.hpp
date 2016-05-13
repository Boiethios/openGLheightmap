#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class GLinstance
{
	protected:
		GLinstance(void);
		~GLinstance(void);

		void
		terminate(void);

		static void
		GlfwErrorCallback(int code, char const *message);

		GLFWwindow					*_win;

		int							_width,
									_height;
		std::string					_title;

		GLuint						_vao;
};
