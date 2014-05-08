#include <sstream>
#include <fstream>
#include <iostream>
#include "ObjectGeometry.h"
#include "Model.h"
#include "Log.h"

ObjectGeometry::ObjectGeometry(const std::string& path) : 
  Geometry("objmodel"),
  obj_path(path) {
	vertex_tree = kd_create(3);

	load(path);
	update();
}

ObjectGeometry::ObjectGeometry(const std::string& path, const std::string& name) :
  Geometry(name),
  obj_path(path) {
	vertex_tree = kd_create(3);

	load(path);
	update();
}

ObjectGeometry::ObjectGeometry() : Geometry("objmodel") {
	vertex_tree = kd_create(3);
}

ObjectGeometry::~ObjectGeometry() {
	free(vertex_tree);
}

void ObjectGeometry::load(std::string file_name) {
	std::ifstream infile(file_name.c_str(), std::ifstream::in);
	if(!infile) {
		//std::ostringstream oss;
		//oss << "ObjGeometry \t Failed to open geometry file: " << file_name << "\n";
		//Log::create_log(oss, 1);
	}
	char line[1024];
	while(infile.good()) {
		infile.getline(line, 1023);
		if(!parse_line(std::string(line))) {
			std::ostringstream oss;
			oss << "ObjGeometry \t Failed on line " << line << "\n";
			Log::create_log(oss, 1);
		}
	}
	infile.close();
	calculate_vertex_normals();
}

bool ObjectGeometry::parse_line(std::string line) {
	std::string token;
	if(line.empty())
		return true;

	std::stringstream ss(std::stringstream::in);
	ss.str(line);
	ss >> token;
	if(token[0] == '#') {
		return true;
	} else if(token.compare("v") == 0) {
		float x, y, z;
		ss >> x >> y >> z;
		add_vertex(x, y, z);
	} else if(token.compare("f") == 0) {
		int i, j, k, l;
		ss >> i >> j >> k;
		add_face(i-1, j-1, k-1); //first triangle
		ss >> l;
		if(ss.fail()) {		//only one triangle
			return true;
		} else {
			add_face(i-1, k-1, l-1);
			return true;
		}
	}
	if(ss.fail())
		return false;
	return true;
}

void ObjectGeometry::calculate_bounding_box() {
	for(int i = 0; i < vertices.size(); i++) {
		bmin[0] = std::min(vertices[i][0], bmin[0]);
		bmin[1] = std::min(vertices[i][1], bmin[1]);
		bmin[2] = std::min(vertices[i][2], bmin[2]);

		bmax[0] = std::max(vertices[i][0], bmax[0]);
		bmax[1] = std::max(vertices[i][1], bmax[1]);
		bmax[2] = std::max(vertices[i][2], bmax[2]);
	}
	this->set_center((bmin + bmax)/2);
	Eigen::Vector3f r = bmax - center;
	this->set_radius(r.norm());
}

void ObjectGeometry::calculate_bounding_box(float x1, float y1, float z1, float x2, float y2, float z2) {
	this->set_bmax(Eigen::Vector3f(x1, y1, z1));
	this->set_bmin(Eigen::Vector3f(x2, y2, z2));
	this->set_center((bmin + bmax)/2);
	Eigen::Vector3f r = bmax - center;
	this->set_radius(r.norm());
}

void ObjectGeometry::calculate_bounding_sphere() {
	for(int i = 0; i < vertices.size(); i++) {
		bmin[0] = std::min(vertices[i][0], bmin[0]);
		bmin[1] = std::min(vertices[i][1], bmin[1]);
		bmin[2] = std::min(vertices[i][2], bmin[2]);

		bmax[0] = std::max(vertices[i][0], bmax[0]);
		bmax[1] = std::max(vertices[i][1], bmax[1]);
		bmax[2] = std::max(vertices[i][2], bmax[2]);
	}
	this->set_center((bmin + bmax)/2);
	Eigen::Vector3f r = bmax - center;
	this->set_radius(r.norm());
}

void ObjectGeometry::calculate_bounding_sphere(float x, float y, float z, float r) {
	this->set_bmax(Eigen::Vector3f(r, r, r));
	this->set_bmin(Eigen::Vector3f(-r, -r, -r));
	this->set_center(Eigen::Vector3f(x, y, z));
	this->set_radius(radius);
}

Eigen::Vector3f ObjectGeometry::cross_custom(Eigen::Vector3f a, Eigen::Vector3f b) {
	return Eigen::Vector3f(a.y()*b.z() - a.z()*b.y(), 
						   a.z()*b.x() - a.x()*b.z(),
						   a.x()*b.y() - a.y()*b.x());
}

void ObjectGeometry::add_vertex(float vx, float vy, float vz) {
	std::vector<int> m;
	Eigen::Vector3f vertex(vx, vy, vz);
	vertices.push_back(vertex);
	vertices_faces.push_back(m);
}

void ObjectGeometry::add_face(int v1, int v2, int v3) {
	Eigen::Vector3f x1 = vertices[v1];
    Eigen::Vector3f x2 = vertices[v2];
    Eigen::Vector3f x3 = vertices[v3];
	
	Eigen::Vector3f a = (x1 - x2);
	Eigen::Vector3f b = (x1 - x3);
	Eigen::Vector3f n = cross_custom(a, b).normalized();
	
	int j = faces.size();
	faces_normals.push_back(n);
	vertices_faces[v1].push_back(j);
	vertices_faces[v2].push_back(j);
	vertices_faces[v3].push_back(j);
	faces.push_back(Eigen::Vector3f(v1, v2, v3));
}

void ObjectGeometry::calculate_vertex_normals() {
	for(int i = 0; i < vertices.size(); i++) {
		Eigen::Vector3f normal(0.f, 0.f, 0.f);
		for(int j = 0; j < vertices_faces[i].size(); j++) {
			normal += this->faces_normals[this->vertices_faces[i][j]];
		}
		normal.normalize();
		this->vertices_normals.push_back(normal);
	}
	this->vertices_faces.clear();
}

void ObjectGeometry::calculate_vertex_tree() {
}

void ObjectGeometry::draw() {
	for(int i = 0; i < faces.size(); i++) {
		glBegin(GL_POLYGON);

		Eigen::Vector3f x1 = this->vertices[this->faces[i][0]];
		Eigen::Vector3f x2 = this->vertices[this->faces[i][1]];
		Eigen::Vector3f x3 = this->vertices[this->faces[i][2]];

		Eigen::Vector3f n1 = this->vertices_normals[this->faces[i][0]];
		Eigen::Vector3f n2 = this->vertices_normals[this->faces[i][1]];
		Eigen::Vector3f n3 = this->vertices_normals[this->faces[i][2]];

		glNormal3f(n1[0], n1[1], n1[2]);
		glVertex3f(x1[0], x1[1], x1[2]);
		glNormal3f(n2[0], n2[1], n2[2]);
		glVertex3f(x2[0], x2[1], x2[2]);
		glNormal3f(n3[0], n3[1], n3[2]);
		glVertex3f(x3[0], x3[1], x3[2]);

		glEnd();
	}
}

void ObjectGeometry::update() {}

void ObjectGeometry::data_log() {
	std::ostringstream oss;
	oss << "Type:\tObjGeometry"
		<< "\n\tPath:\t" << obj_path 
		<< "\n\tName:\t" << name 
		<< "\n\tFaces:\t" << faces.size() 
		<< "\n\tVerts:\t" << vertices.size() 
		<< "\n\tRadius:\t" << radius 
		<< "\n\tCenter:\t [" << center.x() << " " << center.y() << " " << center.z() << "]"
		<< "\n\tMin:\t [" << bmin.x() << " " << bmin.y() << " " << bmin.z() << "]" 
		<< "\n\tMax:\t [" << bmax.x() << " " << bmax.y() << " " << bmax.z() << "]\n";
	Log::create_log(oss, 1);
}