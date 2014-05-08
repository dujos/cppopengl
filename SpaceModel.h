#ifndef SPACE_MODEL_H
#define SPACE_MODEL_H

#include "ImovableModel.h"

#include <string>
#include <gl\GL.h>
#include <glut.h>

class SpaceModel : public ImovableModel {

public:
	SpaceModel();
	SpaceModel(Eigen::Vector3f position);
	SpaceModel(Eigen::Vector3f position, Eigen::Vector3f rotation, Eigen::Vector3f scale,
		Eigen::Vector3f color, float radius, Geometry* mesh);

	static GLuint load_image(char* file_name);
	void draw();

private:
	static GLuint texture_id;

};

#endif