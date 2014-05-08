#include "Model.h"
#include <iostream>

Model::Model() :
  mesh(NULL),
  position(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
  rotation(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
  scale(Eigen::Vector3f(1.0f, 1.0f, 1.0f)),
  color(Eigen::Vector3f(0.0f, 0.0f, 0.0f)),
  radius(0.0f),
  bounding_shape(NULL),
  health(1),
  is_asteroid(true) {
	trans_matrix = Eigen::Matrix4f::Identity();
}

Model::Model(Eigen::Vector3f p, Eigen::Vector3f rot, Eigen::Vector3f s,
  Eigen::Vector3f c, float r, Geometry* m) :
  mesh(m),
  position(p),
  rotation(rot),
  scale(s),
  color(c),
  radius(r),
  bounding_shape(NULL),
  health(1),
  is_asteroid(true) {
	trans_matrix = Eigen::Matrix4f::Identity();
}

bool Model::is_dead() { return dead; }

void Model::destroy_model() {
	if(dead)
		return;
	color = Eigen::Vector3f(1.f, 1.f, 1.f);
	scale = Eigen::Vector3f(1.f, 1.f, 1.f);
	rotation = Eigen::Vector3f(0.f, 0.f, 0.f);
	mesh = NULL;
	dead = true;
}

bool Model::collision(Model* other) { return false; }

void Model::draw() {
	if (!this->mesh)
		return;

	glPushMatrix();
	glTranslatef(position.x(), position.y(), position.z());
	
	glRotatef(rotation.x(), 1, 0, 0);
	glRotatef(rotation.y(), 0, 1, 0);
	glRotatef(rotation.z(), 0, 0, 1);

	glScalef(scale.x(), scale.y(), scale.z());

	float colors[] = {color.x(), color.y(), color.z(), 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, colors);
	mesh->draw();

	glPopMatrix();
}

Geometry* Model::get_mesh() {
	return mesh;
}

void Model::calculate_transform() {
	/*
	trans_matrix = Eigen::Matrix4f::Identity();
	scale_m(scale.x(), scale.y(), scale.z());
	rotate_m(rotation.x(), rotation.y(), rotation.z());
	translate_m(position.x(), position.y(), position.z());
	*/
}
	
void Model::translate_m(float x, float y, float z) {
	Eigen::Matrix4f trans = Eigen::Matrix4f::Identity();
	trans(0, 3) = x;
	trans(1, 3) = y;
	trans(2, 3) = z;
	this->trans_matrix = trans * this->trans_matrix;
}
	
void Model::scale_m(float x, float y, float z) {
	Eigen::Matrix4f sc = Eigen::Matrix4f::Identity();
	sc(0, 0) = x;
	sc(1, 1) = y;
	sc(2, 2) = z;
	sc(3, 3) = 1;
	trans_matrix = sc*trans_matrix;
	//std::cout << sc*trans_matrix << std::endl;
	//std::cout << sc << " trans matrix " << std::endl;
}
	
void Model::rotate_m(float x, float y, float z) {
	Eigen::Matrix4f rx, ry, rz;
	//degrees to radians.
	rx = rotate_x(x * PI/180.0f);
	ry = rotate_y(y * PI/180.0f);
	rz = rotate_z(z * PI/180.0f);
	this->trans_matrix = rx * ry * rz * this->trans_matrix;
}

Eigen::Matrix4f Model::rotate_x(float radians) {
	Eigen::Matrix4f rx = Eigen::Matrix4f::Zero();
	rx(0, 0) = 1;
	rx(3, 3) = 1;
	rx(1, 1) = std::cos(radians);
	rx(1, 2) = -std::sin(radians);
	rx(2, 1) = std::sin(radians);
	rx(2, 2) = std::cos(radians);
	return rx;
}

Eigen::Matrix4f Model::rotate_y(float radians) {
	Eigen::Matrix4f ry = Eigen::Matrix4f::Zero();
	ry(1, 1) = 1;
	ry(3, 3) = 1;
	ry(0, 0) = std::cos(radians);
	ry(2, 0) = -std::sin(radians);
	ry(0, 2) = std::sin(radians);
	ry(2, 2) = std::cos(radians);
	return ry;
}

Eigen::Matrix4f Model::rotate_z(float radians) {
	Eigen::Matrix4f rz = Eigen::Matrix4f::Zero();
	rz(2, 2) = 1;
	rz(3, 3) = 1;
	rz(0, 0) = std::cos(radians);
	rz(0, 1) = -std::sin(radians);
	rz(1, 0) = std::sin(radians);
	rz(1, 1) = std::cos(radians);
	return rz;
}

Eigen::Vector3f Model::get_position() {
	return position;
}

Eigen::Vector3f Model::get_rotation() {
	return rotation;
}

float Model::get_radius() const {
	return radius;
}

BoundingShape* Model::get_bounding_shape() const {
	return bounding_shape;
}