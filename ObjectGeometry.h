#ifndef OBJECT_GEOMETRY_H
#define OBJECT_GEOMETRY_H

#include "Geometry.h"
#include "kdtree\kdtree-0.5.6\kdtree.h"
#include <vector>
#include <string>

class ObjectGeometry : public Geometry {

protected:
	std::vector<Eigen::Vector3f> vertices;
	std::vector<std::vector<int>> vertices_faces;
	std::vector<Eigen::Vector3f> vertices_normals;
	std::vector<Eigen::Vector3f> faces;
	std::vector<Eigen::Vector3f> faces_normals;

	kdtree* vertex_tree;
	std::string obj_path;

public:
	ObjectGeometry();
	ObjectGeometry(const std::string& path, const std::string& name);
	ObjectGeometry(const std::string& path);

	~ObjectGeometry();

	void draw();
	void update();

	void load(std::string file_name);
	bool parse_line(std::string line);

	void calculate_bounding_sphere();
	void calculate_bounding_box();
	void calculate_bounding_sphere(float x, float y, float z, float r);
	void calculate_bounding_box(float x1, float y1, float z1, 
		float x2, float y2, float z2);

	Eigen::Vector3f cross_custom(Eigen::Vector3f a, Eigen::Vector3f b);

	void add_vertex(float vx, float vy, float vz);
	void add_face(int fx, int fy, int fz);

	void data_log();

	void calculate_vertex_normals();
	void calculate_vertex_tree();
};

#endif