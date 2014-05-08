#include "BoundingBox.h"

BoundingBox::BoundingBox() :
  BoundingShape() {
	load_vertices();
}

BoundingBox::BoundingBox(Model* model) :
  BoundingShape(model) {
    load_vertices();
}

BoundingBox::BoundingBox(Model* model, Eigen::Vector3f center, float radius) :
  BoundingShape(model, center, radius) {
	load_vertices();
}

void BoundingBox::add_model(struct kdtree* tree) {
	kd_insert3f(tree, center.x(), center.y(), center.z(), this);
}

float BoundingBox::distance_to_plane(Eigen::Vector3f p, Eigen::Vector3f a, 
  Eigen::Vector3f b, Eigen::Vector3f c) {
	Eigen::Vector3f vector = (b-a).cross(c-a);
	vector.normalize();
	return (-vector.dot(p-a));
}

bool BoundingBox::intersect(BoundingSphere* other) {
	Eigen::Vector3f other_center = other->get_center();
	float other_radius = other->get_radius();

	float positive_z = distance_to_plane(other_center, vertcises[6], vertcises[7], vertcises[4]);
    float negative_z = distance_to_plane(other_center, vertcises[2], vertcises[0], vertcises[3]);
    
	float positive_y = distance_to_plane(other_center, vertcises[7], vertcises[3], vertcises[0]);
    float negative_y = distance_to_plane(other_center, vertcises[6], vertcises[1], vertcises[2]);
    
	float positive_x = distance_to_plane(other_center, vertcises[2], vertcises[3], vertcises[7]);
	float negative_x = distance_to_plane(other_center, vertcises[5], vertcises[0], vertcises[1]);

	if((positive_z <= 0 && negative_x <= 0) &&
	   (positive_x <= 0 && negative_x <= 0) &&
	   (positive_y <= 0 && negative_y <= 0)) {
		return true;
	}

	if((positive_z - radius > 0 || negative_z - radius > 0) &&
	   (positive_x - radius > 0 || negative_x - radius > 0) &&
	   (positive_y - radius > 0 || negative_y - radius > 0)) {
		return false;
	}

	float dx = -1;
	float dy = -1;
	float dz = -1;

	float dx2 = -1;
	float dy2 = -1;
	float dz2 = -1;

	int c = 0;
	int r = radius * radius;

	if(positive_x > 0 || negative_x > 0) {
		c++;
		if(positive_x > 0)
			dx = positive_x;
		else
			dx = negative_x;
	}

	if(positive_y > 0 || negative_y > 0) {
		c++;
		if(positive_y > 0)
			dy = positive_y;
		else
			dy = negative_y;
	}

	if(positive_z > 0 || negative_z > 0) {
		c++;
		if(positive_z > 0)
			dz = positive_z;
		else
			dz = negative_z;
	}

	if(c == 1)
		return true;

	dx2 = dx*dx;
	dy2 = dy*dy;
	dz2 = dz*dz;

    if(dx > 0 && dy > 0 && dz > 0)
        return (dx2 + dy2 + dz2) < r;
    if(dx > 0 && dy > 0)
        return (dx2 + dy2) < r;
    if(dz > 0 && dy > 0)
        return (dy2 + dz2) < r;
    if(dx > 0 && dz > 0)
        return (dx2 + dz2) < r;
	return false;
}

void BoundingBox::transform(Eigen::Matrix4f& matrix, float radius) {
	this->radius *= radius;
	for(int i = 0; i < 8; i++)
		transform_from_vector(matrix, &this->vertcises[i]);
	transform_from_vector(matrix, &center);
}

void BoundingBox::transform_from_vector(Eigen::Matrix4f& tm, Eigen::Vector3f* v) {
	Eigen::Matrix4f tranm = tm;
	Eigen::Vector4f new_vector(v->x(), v->y(), v->z(), 1.f);
	new_vector =  tranm * new_vector;
	*v = Eigen::Vector3f(new_vector.x(), new_vector.y(), new_vector.z());
}

void BoundingBox::update(Geometry* geometry) {
	Eigen::Vector3f bbox_max = geometry->get_max();
	Eigen::Vector3f bbox_min = geometry->get_min();
	radius = geometry->get_radius();
	center = geometry->get_center();

	load_vertices(bbox_max, bbox_min);
}

void BoundingBox::update() {
	Eigen::Vector3f bbox_max = model->get_mesh()->get_max();
	Eigen::Vector3f bbox_min = model->get_mesh()->get_min();
	radius = model->get_mesh()->get_radius();
	center = model->get_mesh()->get_center();

	load_vertices(bbox_max, bbox_min);
}

void BoundingBox::load_vertices(Eigen::Vector3f& bbox_max, Eigen::Vector3f& bbox_min) {
	/*
	uln, lln, lrn, urn, ulf, llf, lrf, urf
	uln[2], lln[2], lrn[2], urn[2]
    ulf[2], llf[2], lrf[2], urf[2]
    uln[0], lln[0], ulf[0], llf[0]
    urn[0], lrn[0], urf[0], lrf[0]
    uln[1], ulf[1], urf[1], urn[1]
    lln[1], llf[1], lrf[1], lrn[1]
	*/

	vertcises[0][2] = bbox_max[2];
	vertcises[1][2] = bbox_max[2];
	vertcises[2][2] = bbox_max[2];
	vertcises[3][2] = bbox_max[2];

	vertcises[4][2] = bbox_min[2];
	vertcises[5][2] = bbox_min[2];
	vertcises[6][2] = bbox_min[2];
	vertcises[7][2] = bbox_min[2];

	vertcises[0][0] = bbox_min[0];
	vertcises[1][0] = bbox_min[0];
	vertcises[4][0] = bbox_min[0];
	vertcises[5][0] = bbox_min[0];

	vertcises[3][0] = bbox_max[0];
	vertcises[2][0] = bbox_max[0];
	vertcises[7][0] = bbox_max[0];
	vertcises[6][0] = bbox_max[0];

	vertcises[0][1] = bbox_max[1];
	vertcises[4][1] = bbox_max[1];
	vertcises[7][1] = bbox_max[1];
	vertcises[3][1] = bbox_max[1];

	vertcises[1][1] = bbox_min[1];
	vertcises[5][1] = bbox_min[1];
	vertcises[6][1] = bbox_min[1];
	vertcises[2][1] = bbox_min[1];
}

void BoundingBox::load_vertices() {
	// uln, lln, lrn, urn, ulf, llf, lrf, urf
	vertcises[0] = Eigen::Vector3f(-1.f, 1.f, -1.f);
	vertcises[1] = Eigen::Vector3f(-1.f, -1.f, -1.f);
	vertcises[2] = Eigen::Vector3f(1.f, -1.f, -1.f);
	vertcises[3] = Eigen::Vector3f(1.f, 1.f, -1.f);
	vertcises[4] = Eigen::Vector3f(-1.f, 1.f, 1.f);
	vertcises[5] = Eigen::Vector3f(-1.f, -1.f, 1.f);
	vertcises[6] = Eigen::Vector3f(1.f, -1.f, 1.f);
	vertcises[7] = Eigen::Vector3f(1.f, 1.f, 1.f);
}

void BoundingBox::data_log() {
	/*
	std::ostringstream oss;
	oss << "\t\tBoundingShape:\t Box"
		<< "\t\tLower Left Far:\t" << llf.x() << ", " << llf.y()<< ", " << llf.z()
		<< "\t\tUpper Right Near:\t" << urn.x() << ", " << urn.y()<< ", " << urn.z();
	Log::log(oss);
	BoundingShape::data_log();
	*/
}