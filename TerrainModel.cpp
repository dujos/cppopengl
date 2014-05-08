#include "TerrainModel.h"
#include "ImovableModel.h"

GLuint TerrainModel::texture_id;

TerrainModel::TerrainModel() : 
  ImovableModel() {

}

/*
GLuint TerrainModel::load_texture(char* file_name) {
	TerrainModel::texture_id = SOIL_load_OGL_texture(file_name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	return texture_id;
	return 0;
}
*/

void TerrainModel::draw() {
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TerrainModel::texture_id);
	glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(position.x(), position.y(), position.z());
	glRotatef(rotation.x(), 1, 0, 0);
	glRotatef(rotation.y(), 0, 1, 0);
	glRotatef(rotation.z(), 0, 0, 1);
	glScalef(scale.x(), scale.y(), scale.z());

	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 1.f);
	glVertex3f(0.f, 0.f, 12.071f);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(5.f, 0.f, 12.071f);
	glTexCoord2f(1.f, 0.f);
	glVertex3f(5.f, 0.f, -12.071f);
	glTexCoord2f(1.f, 1.f);
	glVertex3f(0.f, 0.f, -12.071f);
	glEnd();

	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}