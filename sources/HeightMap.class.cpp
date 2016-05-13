#include "HeightMap.class.hpp"

#include <fstream>
#include <sstream>

#include "Main.class.hpp"

inline bool
HeightMap::get_line(std::ifstream & ifs, vertlst_t & lst, float y)
{
	float constexpr			triangle_side(1.118033989);
	std::string				line;
	if (not std::getline(ifs, line))
		return false;
	std::istringstream		iss(line);

	for (float x(static_cast<int>(y) % 2 ? 0 : triangle_side / 2), z ;
			iss >> z ; x += triangle_side)
	{
		lst.push_back(Coo{x, y, z});
	}
	return true;
}

HeightMap::HeightMap(std::string filename) :
	_shader(Main::_Data_place + "shaders/map.vert.glsl",
			Main::_Data_place + "shaders/map.frag.glsl")
{
	std::ifstream			ifs(filename);
	vertlst_t				lst_1,
							lst_2;
	bool					turn(false);

	if (not ifs.is_open())
		throw std::runtime_error(std::string("Cannot open the map `") + filename + "`");

	if (not this->get_line(ifs, lst_1, 0.))
		throw std::runtime_error(std::string("Empty map `") + filename + "`");
	for (float y(-1.) ; this->get_line(ifs, (turn ? lst_1 : lst_2), y) ; --y)
	{
		for (vertlst_t::iterator it1(lst_1.begin()), it2(lst_2.begin()), end1(lst_1.end()), end2(lst_1.end())
				; it1 != end1 and it2 != end2 ; ++it1, ++it2)
		{
			_vertices.insert(_vertices.cend(), {it1->x, it1->y, it1->z, it2->x, it2->y, it2->z});
		}
	}
	ifs.close();

	_vertices = { // test
		-10.0f, -10.0f, 0.0f,
		 10.0f, -10.0f, 0.0f,
		 0.0f,  10.0f, 0.0f,
	};
	/* init OpenGL buffers */
	glGenBuffers(1, &_glbuffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, _glbuffer_id); // this buffer is an array
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW); // give vertices to OpenGL
}

HeightMap::~HeightMap(void)
{
	glDeleteBuffers(1, &_glbuffer_id);
}


void
HeightMap::display(void)
{
	glUseProgram(_shader.id());
		glEnableVertexAttribArray(0); // enable the 0 layout
		glBindBuffer(GL_ARRAY_BUFFER, _glbuffer_id);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // (id, coo / vertex, type, normalized, offset between values, array)

//		glEnableVertexAttribArray(1);
//		glBindBuffer(GL_ARRAY_BUFFER, _color_buffer_id);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


		glDrawArrays(GL_TRIANGLE_STRIP, 0, _vertices.size() / 3);
//		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	glUseProgram(0);
}
