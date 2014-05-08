#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "BoundingShape.h"
#include "BoundingSphere.h"
#include "Model.h"
#include <Eigen\Core>

class BoundingBox : public BoundingShape {

private:
	Eigen::Vector3f vertcises[8];

public:
	BoundingBox();
	BoundingBox(Model* model);
	BoundingBox(Model* model, Eigen::Vector3f center, float radius);

    void add_model(struct kdtree* tree);

	void data_log();

	bool intersect(BoundingSphere* sphere);
	void transform(Eigen::Matrix4f& m, float radius);
	void transform_from_vector(Eigen::Matrix4f& m, Eigen::Vector3f* v);
	void update(Geometry* geometry);
	void update();

private:
	void load_vertices();
	void load_vertices(Eigen::Vector3f& bbox_max, Eigen::Vector3f& bbox_min);
	float distance_to_plane(Eigen::Vector3f p, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c);
};

#endif