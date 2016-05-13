#include "Shader.class.hpp"

#include <vector>
#include <stdexcept>
#include <fstream>
#include <iostream>

static inline void
check_result_shader(GLuint id)
{
	GLint					result(GL_TRUE); glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLint				infoLogLength; glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char>	vertexShaderErrorMessage(infoLogLength);

		glGetShaderInfoLog(id, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		throw std::runtime_error(std::string(&vertexShaderErrorMessage[0]));
	}
}
static inline void
check_result_prgm(GLuint id)
{
	GLint					result(GL_TRUE); glGetProgramiv(id, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		GLint				infoLogLength; glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char>	vertexShaderErrorMessage(infoLogLength);

		glGetProgramInfoLog(id, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		throw std::runtime_error(std::string(&vertexShaderErrorMessage[0]));
	}
}

static inline std::string
get_shader_code(std::string const & path)
{
	std::string		shaderCode;
	std::ifstream	shaderStream(path, std::ios::in);

	if(not shaderStream.is_open())
		throw std::runtime_error(std::string("Impossible to open ") + path);
	std::getline(shaderStream, shaderCode, '\0');
	shaderStream.close();
	return shaderCode;
}

Shader::Shader(std::string vertex_file_path, std::string fragment_file_path)
{
	/* Create the shaders */
	GLuint			vertexShaderID(glCreateShader(GL_VERTEX_SHADER));
	GLuint			fragmentShaderID(glCreateShader(GL_FRAGMENT_SHADER));

	/* Read the vertices code from files */
	std::string		vertexShaderCode(get_shader_code(vertex_file_path));
	std::string		fragmentShaderCode(get_shader_code(fragment_file_path));
	char const		*vertexSourcePointer(vertexShaderCode.c_str());
	char const		*fragmentSourcePointer(fragmentShaderCode.c_str());

	std::cout << "Compiling shader : " << vertex_file_path << "\n";
	/* Compile Vertex Shader */
	glShaderSource(vertexShaderID, 1ul, &vertexSourcePointer , NULL);
	glCompileShader(vertexShaderID);
	check_result_shader(vertexShaderID);

	std::cout << "                 : " << fragment_file_path << "\n";
	/* Compile Fragment Shader */
	glShaderSource(fragmentShaderID, 1ul, &fragmentSourcePointer , NULL);
	glCompileShader(fragmentShaderID);
	check_result_shader(fragmentShaderID);

	std::cout << "                 : linking program\n";
	/* Link the program */
	GLuint programID(glCreateProgram());
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	check_result_prgm(programID);

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	_id = programID;
}

Shader::~Shader(void)
{
	glDeleteProgram(_id);
}

GLuint
Shader::id(void) const
{
	return _id;
}
