#ifndef BOUNDING_SHAPE_H
#define BOUNDING_SHAPE_H

#include "Geometry.h"
#include "Eigen\Core"
#include "kdtree\kdtree-0.5.6\kdtree.h"
#include <iostream>
#include "Log.h"

class Model;
class BoundingSphere;

class BoundingShape {

protected:
	Model* model;
	Eigen::Vector3f center;
	float radius;

public:
	BoundingShape() : model(NULL), center(Eigen::Vector3f(0.f, 0.f, 0.f)), radius(0.f) {}
	BoundingShape(Model* model) : model(model) {}
	BoundingShape(Model* m, Eigen::Vector3f c, float r) : model(m), center(c), radius(r) {}
	~BoundingShape() {}

	void data_log() {
		std::ostringstream oss;
		oss << "\t\tCenter:\t" << center.x() << ", " << center.y() << ", " << center.z()
			<< "\t\tRadius:\t" << radius;
		Log::log(oss);
	}
	
	virtual bool intersect(BoundingSphere* ) = 0;
	virtual void add_model(struct kdtree* tree) = 0;
	virtual void transform(Eigen::Matrix4f& matrix, float k) = 0;

	Model* get_model() const { return model; }
	void set_center(Eigen::Vector3f& c) { center = c; }
	Eigen::Vector3f get_center() const { return center; }
	float get_radius() const { return radius; }
	void set_radius(float radius) { radius = radius; }

	virtual void update(Geometry* geometry) = 0;
	virtual void update() = 0;
};

#endif