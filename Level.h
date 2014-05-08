#ifndef LEVEL_H
#define LEVEL_H

#include "kdtree\kdtree-0.5.6\kdtree.h"
#include "Ship.h"
#include "Missile.h"
#include "Bomb.h"
#include "Wall.h"

class Level {

protected:
	kdtree* imovable_tree;
	kdtree* movable_tree;

	typedef std::vector<Model* > Models;
	typedef std::vector<Geometry* > Geometries;
	typedef std::vector<LaserMissile* > Missiles;
	typedef std::vector<LaserBomb* > Bombs;
	typedef std::vector<Wall* > Walls;

	Models* imovable_models;
	Models* movable_models;
	Geometries* geometries;
	Missiles* missiles;
	Bombs* bombs;
	Walls* walls;
	Ship* ship;

public:
	Level();
	~Level();

	void create_tree();

	Models* get_imovable_models();
	Models* get_movable_models();
	Geometries* get_geometries();
	Walls* get_walls();

	void check_movable_models();
	void check_ship_collision();
	void check_wall_collision();

	void add_ship(Ship* ship);

	void draw();
	void draw_movable_models();
	void draw_imovable_models();

	void update();
	void update_movable_models();
	void update_movable_tree();

private:
	void clean_all_models();
	void clean_models(Models* models);
	void clean_geometries(Geometries* geometries);
	void clean(Bombs* bombs);
	void clean(Missiles* missiles);
	void clean(Walls* walls);
};

#endif