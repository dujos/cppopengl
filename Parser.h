#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "Box.h"
#include "Plane.h"
#include "Level.h"
#include "ObjectGeometry.h"

class ImovableModel;

class Parser {

protected:
	enum Lines {MULTI, SINGLE};

private:
	Level* lvl;
	Lines mode;

public:
	Parser();
	~Parser() {}

	bool parse_line(std::string line);
	bool parse_box(std::string box);
	bool parse_ship(std::string ship);
	bool parse_wall(std::string wall);
	bool parse_active_model(std::string model);
	bool parse_imovable_model(std::string model);
	bool parse_object_geometry(std::string geometry);
	Geometry* parse_geometry(std::string geometry);

	void add_shapes();

	Level* parse_level(std::string level);
	std::string parse_lvl_names();

private:
	void data_log(const std::string& str);
};

#endif