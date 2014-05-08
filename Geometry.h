#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <string>
#include <vector>
#include <Eigen\Core>

class Geometry {

protected:
	Eigen::Vector3f bmin;
	Eigen::Vector3f bmax;
	Eigen::Vector3f center;
	float radius;
	std::string name;
	bool bounding_box;
	int display_list;

public:
	Geometry();
	Geometry(const std::string& name);
	~Geometry() {}

	float get_radius();
	Eigen::Vector3f get_max();
	Eigen::Vector3f get_min();
	Eigen::Vector3f get_center();

	void set_center(Eigen::Vector3f center);
	void set_radius(float radius);

	void set_bmin(Eigen::Vector3f bmin);
	void set_bmax(Eigen::Vector3f bmax);

	std::string get_name();
	bool get_bounding_box() const;

	virtual void draw() = 0;
	virtual void update() = 0;
};

#endif