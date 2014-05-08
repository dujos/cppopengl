#ifndef MOVABLE_MODEL_H
#define MOVABLE_MODEL_H

#ifdef _WIN32
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define NOMINMAX
#endif

#include "Model.h"

class MovableModel : public Model {

protected:
	Eigen::Vector3f velocity;
	Eigen::Vector3f accelaration;

public:
	MovableModel();
	MovableModel(Eigen::Vector3f position, Eigen::Vector3f rotation, 
		Eigen::Vector3f scale, Eigen::Vector3f color, float radius,
		Geometry* mesh, Eigen::Vector3f velocity, Eigen::Vector3f accelaration);
	~MovableModel();

	void hit_model(Model* other);
	void add_model(struct kdtree* tree);
	void update();
};

#endif
