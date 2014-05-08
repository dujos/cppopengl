#include <iostream>
#include <Eigen\Core>

#include "BoundingSphere.h"

BoundingSphere::BoundingSphere() :
  BoundingShape() {
}

BoundingSphere::BoundingSphere(Model* model) :
  BoundingShape(model) {
}

BoundingSphere::BoundingSphere(Model* m, Eigen::Vector3f center, float radius) : 
  BoundingShape(m, center, radius) {
}

BoundingSphere::~BoundingSphere() {}

bool BoundingSphere::intersect(BoundingSphere* other) {
	Eigen::Vector3f other_center = other->center;
	float other_radius = other->radius;
	return (center - other_center).norm() <= (radius + other_radius);
}

void BoundingSphere::add_model(struct kdtree* tree) {
	kd_insert3f(tree, center.x(), center.y(), center.z(), this);
}

void BoundingSphere::transform(Eigen::Matrix4f& t, float scale) {
	Geometry* geometry = model->get_mesh();
	radius = radius * scale;
	Eigen::Matrix4f temp = Eigen::Matrix4f::Identity();
	Eigen::Vector4f ncenter(center.x(), center.y(), center.z(), 1);
	ncenter = temp * ncenter;
	center = Eigen::Vector3f(ncenter.x(), ncenter.y(), ncenter.z());
}

void BoundingSphere::update(Geometry* geometry) {
	radius = geometry->get_radius();
	center = geometry->get_center();
}

void BoundingSphere::update() {
	Geometry* geometry = model->get_mesh();
	radius = geometry->get_radius();
	center = geometry->get_center();
}

void BoundingSphere::data_log() {
	std::ostringstream oss;
	oss << "\t\tBoundingShape:\t Sphere";
	Log::log(oss);
	BoundingShape::data_log();
}