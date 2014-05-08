#include "Plane.h"

Plane::Plane() : Geometry("plane") {
	ul = Eigen::Vector3f(-1.0f, 1.0f, 0.0f);
	ll = Eigen::Vector3f(-1.0f, -1.0f, 0.0f);
	lr = Eigen::Vector3f(1.0f, -1.0f, 0.0f);
	ur = Eigen::Vector3f(1.0f, 1.0f, 0.0f);
}

void Plane::draw() {
	glBegin(GL_POLYGON);
	glVertex3f(ul[0], ul[1], ul[2]);
	glVertex3f(ll[0], ll[1], ll[2]);
	glVertex3f(lr[0], lr[1], lr[2]);
	glVertex3f(ur[0], ur[1], ur[2]);
	glEnd();
}

void Plane::update() {
	set_bmin(ll);
	set_bmax(ur);
}