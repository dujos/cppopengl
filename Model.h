#ifndef MODEL_H
#define MODEL_H

#ifdef _WIN32
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define NOMINMAX
#endif

#include "Geometry.h"
#include "BoundingShape.h"
#include "kdtree\kdtree-0.5.6\kdtree.h"

#include <glut.h>
#include <gl\GL.h>
#include <Eigen\Core>

#define PI 4*std::atan(1.0)

class Model {

protected:
	Eigen::Matrix4f trans_matrix;
	
	Geometry* mesh;
	BoundingShape* bounding_shape;
	
	Eigen::Vector3f position;
	Eigen::Vector3f scale;
	Eigen::Vector3f rotation;
	Eigen::Vector3f color;
	float radius;
	
public:
	bool dead;
	int health;

public:
	bool is_asteroid;

public:
	Model();
	Model(Eigen::Vector3f position, Eigen::Vector3f rotation, Eigen::Vector3f scale,
		Eigen::Vector3f color, float radius, Geometry* mesh);
	virtual ~Model() {}

	Geometry* get_mesh();

	void calculate_transform();
	void translate_m(float x, float y, float z);
	void scale_m(float x, float y, float z);
	void rotate_m(float x, float y, float z);

	Eigen::Matrix4f rotate_x(float radians);
	Eigen::Matrix4f rotate_y(float radians);
	Eigen::Matrix4f rotate_z(float radians);

	Eigen::Vector3f get_position();
	Eigen::Vector3f get_rotation();
	float get_radius() const;
	BoundingShape* get_bounding_shape() const;

	bool is_dead();

	virtual void hit_model(Model* other) = 0;
	virtual void destroy_model();
	virtual bool collision(Model* other);
	virtual void add_model(struct kdtree* tree) = 0;
	virtual void draw();
	virtual void update() = 0;
};

#endif