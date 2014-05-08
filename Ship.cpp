#include <iostream>

#include "BoundingSphere.h"
#include "Math.h"
#include "ShipGeometry.h"
#include "Ship.h"

Ship::Ship() : MovableModel() {
	rotation = Eigen::Vector3f(0.f, 90.f, 0.f);
	mesh = new ShipGeometry("ship.obj", false);
	bounding_shape = new BoundingSphere(this, position, 0.084f);
	radius = 0.084f;
	rolling = -1;
	roll_frames = 30;
	roll_revolutions = 1;
	rolling_direction = RollingDirections::NONE;
	direction = Direction::NODIRECTION;
	health = 100;
}
	
Ship::Ship(Eigen::Vector3f position, Eigen::Vector3f rotation,
  Eigen::Vector3f scale, Eigen::Vector3f color, float radius,
  Geometry* m, Eigen::Vector3f velocity, Eigen::Vector3f accelaration) :
  MovableModel(position, rotation, scale, color,
  radius, m, velocity, accelaration),
  rolling(-1),
  roll_frames(30),
  roll_revolutions(1),
  rolling_direction(RollingDirections::NONE),
  direction(Direction::NODIRECTION),
  health(100) {
	this->bounding_shape = new BoundingSphere(this, position, 0.084f);
}

Ship::~Ship() {}

int Ship::get_health() const {
	return health;
}

void Ship::set_health(int health) {
	health = health;
}
 
void Ship::draw() {
	glPushMatrix();

	glTranslatef(position.x(), position.y(), position.z());
	glRotatef(rotation.x(), 1, 0, 0);
	glRotatef(rotation.y(), 0, 1, 0);
	glRotatef(rotation.z(), 0, 0, 1);
	glScalef(scale.x(), scale.y(), scale.z());

	mesh->draw();

	glPopMatrix();
}

void Ship::update() {
	if(direction != Direction::NODIRECTION) {
		unsigned int v = (direction == LEFT || direction == RIGHT) ? 0 : 1;
		float acceleration = this->calculate_accelaration(velocity[v]);
        if (direction == RIGHT || direction == UP) 
            acceleration = -acceleration;
        velocity[v] += acceleration;

		if(std::fabs(velocity[v]-0.0f) < 0.000001)
			direction = Direction::NODIRECTION;
	}
	update_roll();

	velocity.z() = -0.25f;
	position += velocity;
	bounding_shape->set_center(position);
}

void Ship::update_direction(unsigned int mousex, unsigned int mousey, 
	unsigned int width, unsigned int height) {
	float mouse_space_z = ((float)position.z() - radius - 0.5f);
	float mouse_space_x = ((float) mousex/width - 0.5f);
	float mouse_space_y = ((float) mousey/height - 0.5f);

	Eigen::Vector3f mouse_position = 
		Eigen::Vector3f(mouse_space_x, mouse_space_y, mouse_space_z);
	float rotate_y = Math::radians_to_degrees(std::atan((mouse_space_x-position.x())/(mouse_space_z-position.z()))) + 90.f;
	float rotate_x = -Math::radians_to_degrees(std::atan((mouse_space_y-position.y())/(mouse_space_z-position.z())));

	rotation.x() = rotate_x;
	rotation.y() = rotate_y;

	Eigen::Vector3f direction = mouse_position - position;
	calculate_movement(direction);
}

void Ship::calculate_movement(Eigen::Vector3f direction) {
	velocity.normalize();
	velocity = direction/20;
	velocity.z() -= 0.1f;
}

float Ship::calculate_accelaration(float accelaration) {
	accelaration = std::fabs(accelaration);
	if(accelaration > 0.005f)
		return 0.002f;
	return accelaration;
}

void Ship::start_roll(RollingDirections direction) {
	if(rolling >= 0) {
		return;
	} else {
		rolling = 0;
		rolling_direction = direction;
	}
}

void Ship::update_roll() {
	if(rolling < 0) {
		return;
	} else if(rolling >= roll_frames) {
		rolling = -1;
		rolling_direction = RollingDirections::NONE;
		return;
	}

	switch(rolling_direction) {
		case RollingDirections::X:
			rotation.x() += 360*roll_revolutions/roll_frames;
			break;
		case RollingDirections::Y:
			rotation.y() += 360*roll_revolutions/roll_frames;
			break;
		case RollingDirections::Z:
			rotation.z() += 360*roll_revolutions/roll_frames;
			break;
		default:
			break;
	}
	rolling +=1;
}