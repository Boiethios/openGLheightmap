#include "GLinstance.abstract.hpp"

#include <stdexcept>
#include <iostream>

GLinstance::GLinstance(void) :
	_width(1024), _height(768),
	_title("My window")
{
	glfwSetErrorCallback(GLinstance::GlfwErrorCallback);

	/* glfw initialization */
	if (not glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");
//	glfwWindowHint(GLFW_SAMPLES, 4); // antialiasing
	{	// version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* glfw window creation */
	if (not (_win = glfwCreateWindow(_width, _height, _title.c_str(), NULL, NULL)))
	{
		this->terminate();
		throw std::runtime_error("Failed to open the window");
	}

	/* openGL context */
	glfwMakeContextCurrent(_win);

	/* glew initialization */
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		this->terminate();
		throw std::runtime_error("Failed to initialize GLEW");
	}

	std::cout << "OpenGL initialized: version is ["
			  << glGetString(GL_VERSION)
			  << "]\n";

	/* init VAO */
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
}

void GLinstance::terminate(void)
{
	glDeleteVertexArrays(1, &_vao);

	glfwTerminate();
}

GLinstance::~GLinstance(void)
{
	this->terminate();
}


void
GLinstance::GlfwErrorCallback(int code, const char *message)
{
	std::cerr << "GLFW: " << message << " (" << code << ")\n";
}
