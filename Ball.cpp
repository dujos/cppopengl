#include "Ball.h"

Ball::Ball() :
	MovableModel(),
	ball_mesh(NULL) {
	scale = Eigen::Vector3f(.05f, .05f, .05f);
	calculate_transform();
	direction = Direction::NODIRECTION;

	load_mesh();
}

Ball::~Ball() {}

void Ball::move(Eigen::Vector3f direction) {}

void Ball::load_mesh() {
	ball_mesh = new ObjectGeometry("ball.obj");
	ball_mesh->calculate_bounding_sphere();
	ball_mesh->data_log();
}