#include "ImovableModel.h"
#include "BoundingBox.h"
#include "Log.h"

ImovableModel::ImovableModel() : Model() {}

ImovableModel::ImovableModel(Eigen::Vector3f position) : Model() {
  position = position;
}

ImovableModel::ImovableModel(Eigen::Vector3f position, Eigen::Vector3f rotation,
  Eigen::Vector3f scale, Eigen::Vector3f color, float radius, Geometry* mesh) :
    Model(position, rotation, scale, color, radius, mesh) {
}

void ImovableModel::hit_model(Model* other) {
	destroy_model();
}

void ImovableModel::add_model(struct kdtree* tree) {
	calculate_transform();
	if(mesh->get_bounding_box()) {
		bounding_shape = new BoundingBox(this);
	} else {
		bounding_shape = new BoundingSphere(this);
	}
	bounding_shape->update(mesh);
	bounding_shape->transform(trans_matrix, scale[0]);
	bounding_shape->add_model(tree);
}

void ImovableModel::update() {}

void ImovableModel::data_log() {
	std::ostringstream oss;
	oss << "Type:\tImovableModel"
		<< "\n\tName:\t" << mesh->get_name()
		<< "\n\tPosition:\t" << position.x() << ", " << position.y()<< ", " << position.z()
		<< "\n\tRotation:\t" << rotation[0] << ", " << rotation[1] << ", " << rotation[2]
		<< "\n\t\tScale:\t" << scale[0] << ", " << scale[1] << ", " << scale[2];
	Log::create_log(oss, 1);

	bounding_shape->data_log();
}
