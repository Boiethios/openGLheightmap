#pragma once

#include <string>
#include <vector>
#include <array>
#include <list>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.class.hpp"

class HeightMap
{
	struct Coo {float x, y, z;};
	typedef std::list<Coo>	vertlst_t;

	public:
		HeightMap(std::string filename);
		~HeightMap(void);

		void
		display(void);

	private:
		inline bool
		get_line(std::ifstream & ifs, vertlst_t & lst, float y);

		std::vector<float>	_vertices;
		Shader				_shader;

		GLuint				_glbuffer_id;
		GLuint				_glminmax_id; // TODO

//		static float constexpr _Triangle_side = 1.118033989;
};
