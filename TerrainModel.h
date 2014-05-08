#ifndef TERRAIN_MODEL_H
#define TERRAIN_MODEL_H

#include "SOIL\SOIL.h"
#include "ImovableModel.h"

class TerrainModel : public ImovableModel {

protected:
	static GLuint texture_id;

public:
	TerrainModel();

	//static GLuint load_texture(char* file_name);
	void draw();
};

#endif