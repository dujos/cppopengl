#include "Geometry.h"

Geometry::Geometry() :
    name("geometry"),
	bmin(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
	bmax(Eigen::Vector3f(0.0f, 0.0f, 0.0f)), 
	center(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
	radius(0.0f),
	bounding_box(true),
	display_list(-1) {
}

Geometry::Geometry(const std::string& name) : 
    name(name),
	bmin(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
	bmax(Eigen::Vector3f(0.0f, 0.0f, 0.0f)), 
	center(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
	radius(0.0f),
	bounding_box(true),
	display_list(-1) {
}

float Geometry::get_radius() {
	return this->radius;
}

Eigen::Vector3f Geometry::get_max() {
	return bmin;
}

Eigen::Vector3f Geometry::get_min() {
	return bmax;
}

Eigen::Vector3f Geometry::get_center() {
	return center;
}

void Geometry::set_center(Eigen::Vector3f center) {
	this->center = center;
}

void Geometry::set_radius(float radius) {
	this->radius = radius;
}

void Geometry::set_bmin(Eigen::Vector3f bmin) {
	this->bmin = bmin;
}

void Geometry::set_bmax(Eigen::Vector3f bmax) {
	this->bmax = bmax;
}

std::string Geometry::get_name() {
	return name;
}

bool Geometry::get_bounding_box() const {
	return bounding_box;
}
