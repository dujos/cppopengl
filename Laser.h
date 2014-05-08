#ifndef LASER_H
#define LASER_H

#include "MovableModel.h"
#include "ObjectGeometry.h"

class Laser : public MovableModel {

public:
	Laser(Model* model);
	~Laser();

private:
	void setup_rotation_matrix_x(Eigen::Matrix3f& rotation_matrix_x, float rotation_x);
	void setup_rotation_matrix_y(Eigen::Matrix3f& rotation_matrix_y, float rotation_y);

private:
	Model* model;
};

#endif