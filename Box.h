#ifndef BOX_H
#define BOX_H

#include "Geometry.h"
#include <vector>
#include <string>
#include <Eigen\Core>

class Box : public Geometry {

protected:
	Eigen::Vector3f lrn;
	Eigen::Vector3f lln;
	Eigen::Vector3f urn;
	Eigen::Vector3f uln;

	Eigen::Vector3f lrf;
	Eigen::Vector3f llf;
	Eigen::Vector3f urf;
	Eigen::Vector3f ulf;

public:
	Box();
	~Box();

	void update();
	void draw();
};

#endif