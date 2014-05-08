#ifndef ABSTRACT_MODEL_H
#define ABSTRACT_MODEL_H

#ifdef _WIN32
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define NOMINMAX
#endif

#include <Eigen\Core>
#include <Eigen\LU>
#include <glut.h>
#include <gl\GL.h>

class AbstractModel {

protected:
	Eigen::Matrix4f trans_matrix;
	
	
	//Geometry* mesh;
	//BoundingShape* bounding_shape;

	Eigen::Vector3f position;
	Eigen::Vector3f scale;
	Eigen::Vector3f rotation;
	Eigen::Vector3f color;

	/*
	float radius;
	*/

public:
	AbstractModel();
	~AbstractModel();
};

#endif