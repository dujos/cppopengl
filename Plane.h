#ifndef PLANE_H
#define PLANE_H

#include "Geometry.h"
#include <vector>
#include <string>
#include <Eigen\Core>

#include <glut.h>
#include <gl\GL.h>

class Plane : public Geometry {

protected:
	Eigen::Vector3f ul;
	Eigen::Vector3f ur;
	Eigen::Vector3f ll;
	Eigen::Vector3f lr;

public:
	Plane();
	~Plane();

	void draw();
	void update();
};


#endif