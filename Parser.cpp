#include "Parser.h"
#include "ImovableModel.h"
#include "SpaceModel.h"
#include "Log.h"
#include "Wall.h"

#include <algorithm>
#include <Eigen\Core>

Parser::Parser() :
  mode(Lines::SINGLE) {
}

Level* Parser::parse_level(std::string level) {
	lvl = new Level();
	add_shapes();

	std::ifstream infile(level.c_str(), std::ifstream::in);
	std::ostringstream oss;
	/*
	oss << "Parser \t Parsing " << level << "\n";
	Log::create_log(oss, 1);
	if(!infile) {
		oss << 	"Parser \t Failed to open " << level << "\n";
		Log::create_log(oss, 1);
		std::exit(1);
	}
	*/

	char cline[1024];
	bool result;
	while(infile.good()) {
		infile.getline(cline, 1023);
		std::string mline = "";
		if(mode == Lines::MULTI) {
			mline = std::string(cline);
			while(infile.good()) {
				infile.getline(cline, 1023);
				std::string line = std::string(cline);
				if(line.empty() || !std::strcmp(line.c_str(), "}"))
					break;
				mline = mline + line; 
			}
			result = parse_line(mline);
			mode = Lines::SINGLE;
		} else {
			result = parse_line(std::string(cline));
		}
		if(!result) {
			oss << 	"Parser \t failed on line " << cline << "\n";
			Log::create_log(oss, 1);
		}
	}

	infile.close();
	oss << 	"Parser \t Finnished with file: " << level << "\n";
	Log::create_log(oss, 1);
	return lvl;
}

bool Parser::parse_line(std::string line) {
	if(line.empty())
		return true;

	std::stringstream ss(std::stringstream::in);
	ss.str(line);
	std::string token;
	ss >> token;

	if(token.compare("{") == 0) {
		mode = Lines::MULTI;
	} else if(token.compare("objgeometry") == 0) {
		parse_object_geometry(line);
	} else if(token.compare("imovablemodel") == 0 || token.compare("spacemodel") == 0) {
		parse_imovable_model(line);
	} else if(token.compare("ship") == 0) {
		parse_ship(line);
	} else if(token.compare("wall") == 0) {
		parse_wall(line);
	}

	if(ss.fail()) 
		return false;
	return true;
}

bool Parser::parse_object_geometry(std::string geometry) {

	std::stringstream ss(std::stringstream::in);
	ss.str(geometry);

	std::string token;
	ss >> token;

	std::string name;
	std::string file_name;
	bool box = true;
	bool set_bounds = false;
	float x, y, z, i, j, k;
	float radius;

	while(ss.good()) {
		ss >> token;
		if(token.compare("name") == 0) {
			ss >> name;
		} else if(token.compare("path") == 0) {
			ss >> file_name;
		} else if(token.compare("boundingsphere") == 0) {
			set_bounds = true;
			ss >> x >> y >> z >> radius;
		} else if(token.compare("boundingbox") == 0) {
			set_bounds = true;
			ss >> x >> y >> z >> i >> j >> k;
		} else if(token.compare("bs") == 0) {
			box = false;
		}
	}

	ObjectGeometry* objg = new ObjectGeometry(file_name, name);

	if(set_bounds && !box)
		objg->calculate_bounding_sphere(x, y, z, radius);
	else if(set_bounds && box)
		objg->calculate_bounding_box(x, y, z, i, j, k);
	objg->data_log();

	lvl->get_geometries()->push_back(objg);
	return true;
}

bool Parser::parse_imovable_model(std::string model_type) {
	std::stringstream ss(std::stringstream::in);
	std::string token;
	std::string imovable_model_type;
	
	ss.str(model_type);
	ss >> imovable_model_type;

	std::ostringstream oss;
	oss << "Parser \t Parsing line " << imovable_model_type;
	Log::create_log(oss, 1);

	float x_position, y_position, z_position;
	float x_rotate, y_rotate, z_rotate;
	float x_scale, y_scale, z_scale;
	float x_color, y_color, z_color;

	ImovableModel* imovable_model = NULL;
	Geometry* mesh = NULL;

	while(!ss.eof()) {
		ss >> token;
		if(token.compare("geometry") == 0) {
			std::string name;
			ss >> name;
			for(size_t i = 0; i < lvl->get_geometries()->size(); i++) {
				if(name.compare(lvl->get_geometries()->at(i)->get_name()) == 0) {
					mesh = lvl->get_geometries()->at(i);
					break;
				} else {
					mesh = parse_geometry(token);
				}
			}
		} else if(token.compare("translate") == 0) {
			ss >> x_position >> y_position >> z_position;
		} else if(token.compare("rotate") == 0) {
			ss >> x_rotate >> y_rotate >> z_rotate;
		} else if(token.compare("scale") == 0) {
			ss >> x_scale >> y_scale >> z_scale;
		} else if(token.compare("color") == 0) {
			ss >> x_color >> y_color >> z_color;
		}
	}

	if(!mesh)
		data_log("geometry");

    if (imovable_model_type.compare("spacemodel") == 0) {
        imovable_model = new SpaceModel(Eigen::Vector3f(x_position, y_position, z_position),
			Eigen::Vector3f(x_rotate, y_rotate, z_rotate),
			Eigen::Vector3f(x_scale, y_scale, z_scale),
			Eigen::Vector3f(x_color, y_color, z_color), 0, mesh);
    } else {
        imovable_model = new ImovableModel(Eigen::Vector3f(x_position, y_position, z_position),
			Eigen::Vector3f(x_rotate, y_rotate, z_rotate),
			Eigen::Vector3f(x_scale, y_scale, z_scale),
			Eigen::Vector3f(x_color, y_color, z_color), 0, mesh);
    }

	imovable_model->calculate_transform();
	lvl->get_imovable_models()->push_back(imovable_model);
	return true;
}

bool Parser::parse_ship(std::string line) {
	std::cout << "Parse ship" << std::endl;

	std::stringstream ss(std::stringstream::in);
	ss.str(line);
	std::string token;
	ss >> token;

	data_log(line);

	float x_position, y_position, z_position;
	float x_rotate, y_rotate, z_rotate;
	float x_scale, y_scale, z_scale;
	float x_color, y_color, z_color;
	float x_velocity, y_velocity, z_velocity;
	float x_accelaration, y_accelaration, z_accelaration;
	float radius;

	Geometry* mesh = NULL;
	std::string geometry;

	while(!ss.eof()) {
		ss >> token;
		if(token.compare("translate") == 0) {
			ss >> x_position >> y_position >> z_position;
		} else if(token.compare("rotate") == 0) {
			ss >> x_rotate >> y_rotate >> z_rotate;
		} else if(token.compare("scale") == 0) {
			ss >> x_scale >> y_scale >> z_scale;
		} else if(token.compare("color") == 0) {
			ss >> x_color >> y_color >> z_color;
		} else if(token.compare("radius") == 0) {
			ss >> radius;
		} else if(token.compare("velocity") == 0) {
			ss >> x_velocity >> y_velocity >> z_velocity;
		} else if(token.compare("accelaration") == 0) {
			ss >> x_accelaration >> y_accelaration >> z_accelaration;
		} else if(token.compare("geometry") == 0) {
			ss >> geometry;
			mesh = parse_geometry(geometry);
		}
	}

	if(!mesh)
		data_log(geometry);

	Ship* ship = new Ship(Eigen::Vector3f(x_position, y_position, z_position),
		 Eigen::Vector3f(x_rotate, y_rotate, z_rotate),
		 Eigen::Vector3f(x_scale, y_scale, z_scale),
		 Eigen::Vector3f(x_color, y_color, z_color), 
		 radius, mesh, 
		 Eigen::Vector3f(x_velocity, y_velocity, z_velocity), 
		 Eigen::Vector3f(x_accelaration, y_accelaration, z_accelaration));
	
	ship->calculate_transform();
	lvl->get_movable_models()->push_back(ship);
	return true;
}

bool Parser::parse_wall(std::string wall) {
	/*
	std::stringstream ss(std::stringstream::in | std::stringstream::out); 
    ss.str(wall);
    
	std::string token;
    ss >> token;

    Wall *wall = NULL;
    while (ss >> token) {
        if(token.compare("type") == 0) {
            std::string name;
            ss >> name;
            if(!name.compare("front")) {
                wall = new FrontWall();
            } else if(!name.compare("top")) {
                wall = new TopWall();
            } else if(!name.compare("left")) {
                wall = new LeftWall();
            } else if(!name.compare("bottom")) {
                wall = new BottomWall();
            } else if(!name.compare("right")) {
                wall = new RightWall();
            } else if(!name.compare("back")) {
                wall = new BackWall();
            }
        } else if(token.compare("move") == 0) {
            float distance;
            ss >> distance;
            wall->distance = d; 
        } 
    }
	lvl->get_walls()->push_back(wall);
	*/
    return true;
}

Geometry* Parser::parse_geometry(std::string geometry) {
	std::vector<Geometry*>::iterator iter = lvl->get_geometries()->begin();
	for(iter; iter != lvl->get_geometries()->end(); iter++) {
		if(geometry.compare((*iter)->get_name()) == 0) {
			return *iter;
		}
	}
	return NULL;
}

void Parser::add_shapes() {
	Box* box = new Box();
	lvl->get_geometries()->push_back(box);

	Plane* plane = new Plane();
	lvl->get_geometries()->push_back(plane);
}

std::string Parser::parse_lvl_names() {
	std::string file_name = "lvlnames.txt";
	std::ifstream infile(file_name.c_str(), std::ifstream::in);

	std::string lvl_names;
	char line[1024];

	while(!infile.eof()) {
		infile.getline(line, 1023);
		lvl_names.append(" ");
		lvl_names += std::string(line);
	}
	infile.close();
	return lvl_names;
}

void Parser::data_log(const std::string& str) {
	std::ostringstream oss;
	oss << "Parser \t Failed to find geometry line " << str;
	Log::create_log(oss, 1);
}