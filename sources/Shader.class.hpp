#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Shader
{
	public:
		Shader(std::string vertex_file, std::string fragment_file);
		~Shader(void);

		GLuint
		id(void) const;

	private:
		GLuint	_id;
};
