#ifndef LASER_MISSILE_H
#define LASER_MISSILE_H

#include "Laser.h"

class LaserMissile : public Laser {

private:
	ObjectGeometry* missile_mesh;

public:
	LaserMissile(Model* model);
	~LaserMissile();

	void explode_missile();
	void load_meshes();

private:
	void init_missile();
};

#endif