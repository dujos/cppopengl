#include "BoundingSpheres.h"

BoundingSpheres::BoundingSpheres() {

}

BoundingSpheres::~BoundingSpheres() {
	this->centers.clear();
	this->radiuses.clear();
}

void BoundingSpheres::add(Eigen::Vector3f center, float radius) {
	this->centers.push_back(center);
	this->radiuses.push_back(radius);
}