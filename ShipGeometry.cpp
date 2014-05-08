#include "ShipGeometry.h"
#include "Model.h"
#include "Log.h"

#include <Eigen\Geometry>

#include <fstream>
#include <sstream>
#include <iostream>

ShipGeometry::ShipGeometry() : 
  ObjectGeometry() {
	log_dump();
}

ShipGeometry::ShipGeometry(std::string path, bool bounding_box) : 
  ObjectGeometry(path) {
	log_dump();
}

void ShipGeometry::draw() {
	if(display_list != -1) {
		glCallList(display_list);
		return;
	}

	display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	
	unsigned int division_size = faces.size()/12;
	float red = 1.0f;
	float green = 1.0f;
	float blue = 1.0f;
	float mcolor[4] = {red, green, blue, 1.0f};
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

	for(unsigned int i = 0; i < faces.size(); i++) {
		if (i < division_size*10) { 
			red = ((float)(i % division_size/2))/division_size;
			green = ((float)(i % division_size/2))/division_size;
			blue = ((float)(i % division_size/2))/division_size + 0.1;
		} else {
			red = ((float) i)/division_size;
			green = ((float) i)/division_size;
			blue = ((float) i)/division_size;
		}
		mcolor[0] = red;
		mcolor[1] = green;
		mcolor[2] = blue;
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);

		glBegin(GL_POLYGON);
			Eigen::Vector3f x1 = vertices[faces[i][0]];
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
	glEndList();
}

void ShipGeometry::log_dump() {
	std::ostringstream oss;
	oss << "Type:\tShipGeometry"
		<< "\n\tPath:\t" << obj_path
		<< "\n\tFaces:\t" << faces.size() 
		<< "\n\tVerts:\t" << vertices.size() 
		<< "\n\tRadius:\t" << radius 
		<< "\n\tCenter:\t [" << center.x() << " " << center.y() << " " << center.z() << "]"
		<< "\n\tMin:\t [" << bmin.x() << " " << bmin.y() << " " << bmin.z() << "]" 
		<< "\n\tMax:\t [" << bmax.x() << " " << bmax.y() << " " << bmax.z() << "]\n";
	Log::create_log(oss, 1);
}
