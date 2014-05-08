#include "Laser.h"
#include "Math.h"

Laser::Laser(Model* m) : MovableModel() {
	model = m;

	Eigen::Vector3f center = model->get_position();
	float offset = model->get_radius();
	float rotation_x = Math::degrees_to_radians(-model->get_rotation().x());
	float rotation_y = Math::degrees_to_radians(model->get_rotation().y());

	Eigen::Vector3f projection_position = center;
	Eigen::Vector3f unit_position = Eigen::Vector3f(1.f, 0.f, 0.f);
	
	Eigen::Matrix3f rotation_matrix_y;
	Eigen::Matrix3f rotation_matrix_x;

	setup_rotation_matrix_x(rotation_matrix_x, rotation_x);
	setup_rotation_matrix_y(rotation_matrix_y, rotation_y);

	unit_position = rotation_matrix_x * rotation_matrix_y * unit_position;
	offset *= offset;
	projection_position += unit_position;

	Eigen::Vector3f bomb_velocity = projection_position - center;

	velocity = bomb_velocity;
	position = projection_position;
	rotation = model->get_rotation();
}

Laser::~Laser() {
	if(bounding_shape)
		delete bounding_shape;
}

void Laser::setup_rotation_matrix_y(Eigen::Matrix3f& rotation_matrix_y, float rotation_y) {
	rotation_matrix_y(0, 0) = std::cos(rotation_y);
	rotation_matrix_y(0, 1) = 0;
	rotation_matrix_y(0, 2) = -std::sin(rotation_y);

	rotation_matrix_y(1, 0) = 0;
	rotation_matrix_y(1, 1) = 1;
	rotation_matrix_y(1, 2) = 0;

	rotation_matrix_y(2, 0) = std::sin(rotation_y);
	rotation_matrix_y(2, 1) = 0;
	rotation_matrix_y(2, 2) = std::cos(rotation_y);
}

void Laser::setup_rotation_matrix_x(Eigen::Matrix3f& rotation_matrix_x, float rotation_x) {
	rotation_matrix_x(0, 0) = 1;
	rotation_matrix_x(0, 0) = 0;
	rotation_matrix_x(0, 0) = 0;

	rotation_matrix_x(0, 0) = 0;
	rotation_matrix_x(0, 0) = std::cos(rotation_x);
	rotation_matrix_x(0, 0) = std::sin(rotation_x);

	rotation_matrix_x(0, 0) = 0;
	rotation_matrix_x(0, 0) = -std::sin(rotation_x);
	rotation_matrix_x(0, 0) = std::cos(rotation_x);
}