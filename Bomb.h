#ifndef LASER_BOMB_H
#define LASER_BOMB_H

#include "Laser.h"

class LaserBomb : public Laser {

private:
	ObjectGeometry* bomb_mesh;

public:
	LaserBomb(Model* model);
	LaserBomb(Eigen::Vector3f position, Eigen::Vector3f velocity);
	~LaserBomb();

	void explode_bomb();
	void hit(Model* model);

private:
	void init_bomb();
	void load_bomb_meshes();
};

#endif