#include "Missile.h"
#include "BoundingSphere.h"

LaserMissile::LaserMissile(Model* model) : Laser(model) {
	load_meshes();
	init_missile();
}

LaserMissile::~LaserMissile() {}

void LaserMissile::load_meshes() {
	missile_mesh = new ObjectGeometry("laser.obj");
}

void LaserMissile::explode_missile() {
	mesh = NULL;
}

void LaserMissile::init_missile() {
	mesh = missile_mesh;
	radius = 0.05f;
	velocity *= 2.5f;
	scale = Eigen::Vector3f(3.f, 3.f, 2.f);
	color = Eigen::Vector3f(0.f, 1.f, 0.f);

	calculate_transform();
	
	bounding_shape = new BoundingSphere(this);
	bounding_shape->update(mesh);
	bounding_shape->transform(trans_matrix, scale[0]);
}
