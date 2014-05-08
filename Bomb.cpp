#include "Bomb.h"
#include "BoundingSphere.h"

LaserBomb::LaserBomb(Model* model) : Laser(model) {
	init_bomb();
}

LaserBomb::~LaserBomb() {}

void LaserBomb::init_bomb() {
	mesh = bomb_mesh;
	radius = 0.05f;
	velocity += 2 * velocity;
	
	scale = Eigen::Vector3f(.5f, .5f, .5f);
	color = Eigen::Vector3f(1.f, 0.f, 0.f);

	calculate_transform();
	
	bounding_shape = new BoundingSphere(this);
	bounding_shape->update(mesh);
	bounding_shape->set_radius(radius);
	bounding_shape->transform(trans_matrix, scale[0]);
}

void LaserBomb::load_bomb_meshes() {
	bomb_mesh = new ObjectGeometry("ball.obj");
}

void LaserBomb::hit(Model* model) {}

void LaserBomb::explode_bomb() {}
