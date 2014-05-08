#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "BoundingShape.h"
#include "Model.h"
#include <vector>
#include <Eigen\LU>
#include <Eigen\Geometry>
#include <Eigen\Core>

class BoundingSphere : public BoundingShape {

public:
	BoundingSphere();
	BoundingSphere(Model* model);
	BoundingSphere(Model* model, Eigen::Vector3f center, float radius);

	~BoundingSphere();

	bool intersect(BoundingSphere* sphere);
	void add_model(struct kdtree* tree);
	void transform(Eigen::Matrix4f& matrix, float scale);

	void update(Geometry* mesh);
	void update();

private:
	void data_log();
};

#endif