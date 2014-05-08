#include "Planet.h"
#include "BoundingSphere.h"

Planet::Planet() : 
  Ball(),
  num_meshes(10) {
	asteroid_meshes = std::vector<ObjectGeometry*>(num_meshes);
	load_mesh();

	mesh = new ObjectGeometry("asteroid1.obj");
	ball_mesh = (ObjectGeometry* ) mesh;
	ball_mesh->calculate_bounding_sphere();

	bounding_shape = new BoundingSphere(this);
	bounding_shape->update(ball_mesh);
	color = Eigen::Vector3f(.4f, 0.4f, .4f);
	is_asteroid = true;
}

Planet::Planet(int num_meshes) : 
  Ball(),
  num_meshes(num_meshes) {
	asteroid_meshes = std::vector<ObjectGeometry*>(num_meshes);
	load_mesh();

	mesh = asteroid_meshes.front();
	ball_mesh = (ObjectGeometry* ) mesh;
	ball_mesh->calculate_bounding_sphere();
	
	bounding_shape = new BoundingSphere(this);
	bounding_shape->update(ball_mesh);
	color = Eigen::Vector3f(.7f, 0.2f, .5f);
	is_asteroid = true;
}

Planet::Planet(const Planet& Planet) : Ball() {
	asteroid_meshes = Planet.asteroid_meshes;

	mesh = Planet.mesh;
	ball_mesh = (ObjectGeometry* ) mesh;
	ball_mesh->calculate_bounding_sphere();
	
	bounding_shape = Planet.bounding_shape;
	bounding_shape->update(ball_mesh);
	color = Planet.color;
	is_asteroid = Planet.is_asteroid;

	load_mesh();
}

Planet::~Planet() {}

void Planet::load_mesh() {
	char file_name[50];
	for(size_t i = 0; i < num_meshes; i++) {
		std::sprintf(file_name, "Planet%lu.obj", i+1);
		asteroid_meshes[i] = new ObjectGeometry(file_name);
	}
}

void Planet::update() {}