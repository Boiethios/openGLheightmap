#pragma once

#include <vector>
#include <string>

#include "GLinstance.abstract.hpp"
#include "Shader.class.hpp"
#include "HeightMap.class.hpp"


class Main : public GLinstance
{
		std::vector<std::string>
		pack_args(int argc, char *argv[]);

	public:
		Main(int argc, char *argv[]);
		~Main(void) = default;

		Main(Main const &) = delete;
		Main & operator=(Main const &) = delete;

		int
		run(void);

		static std::string const	_Data_place;

	private:
		void
		draw(void);

		std::vector<std::string>	_args;

		HeightMap					_map;
};
