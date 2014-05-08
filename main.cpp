#ifdef _WIN32
#define EIGEN_DONT_VECTORIZE
#define EIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT
#define NOMINMAX
#endif

#include <Windows.h>
#include <gl\GL.h>
#include <glut.h>

#include "SOIL\SOIL.h"
#include "EIGEN\Core"

#include <iostream>
#include <vector>
#include <cmath>

#include "AbstractModel.h"
#include "Game.h"
#include "Time.h"
#include "Ball.h"
#include "Ship.h"
#include "SpaceModel.h"
#include "Planet.h"
#include "Laser.h"
#include "Missile.h"
#include "Bomb.h"

Game game;

static void gl_init(int , char** );
static void init_scene();
static void reshape(int x, int y);

static void setup_camera();
static void setup_lighting();
static void setup_shading();
static void draw();
static void draw_bar(float bar);
static void draw_score(char* score);
static void draw_test();
static void update();

static void key_pressed(unsigned char key, int x, int y);
static void key_pressed_special(int key, int x, int y);
static void mouse_clicked(int button, int state, int x, int y);
static void mouse_moved(int x, int y);

static void ortho_graphic_projection();
void static reset_perspective_projection();

GLuint load_image(char* file_name) {
	return 0;
}

int main(int argc, char** argv)	{
	gl_init(argc, argv);


	std::getchar();
	return 0;
}

static void gl_init(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(game.get_width(), game.get_height());
	//glutInitWindowSize(100, 100);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Star");

	init_scene();
	setup_lighting();
	setup_shading();

	glutDisplayFunc(draw);
	glutKeyboardFunc(key_pressed);
	glutMotionFunc(mouse_moved);
	glutPassiveMotionFunc(mouse_moved);
	glutIdleFunc(update);
	glutMouseFunc(mouse_clicked);
	glutSetCursor(GLUT_CURSOR_CYCLE);

	SpaceModel::load_image((char*) "grid.png");
	LaserMissile* missile = new LaserMissile(game.get_ship());

	Time::init_time();

	glutMainLoop();
}

static void init_scene() {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	reshape(game.get_width(), game.get_height());
	//reshape(0, 0);
}

static void reshape(int x, int y) {
	game.set_width(x);
	game.set_height(y);

	glViewport(0, 0, game.get_width(), game.get_height());
	//glViewport(0, 0, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(90.f, 100 / 100, 0.1, 100);
	gluPerspective(90.f, game.get_width() / game.get_height(), 0.1, game.get_clipping_plane());
}

static void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_COLOR_MATERIAL);

	glLoadIdentity();
	setup_camera();

	glPushMatrix();
	game.draw();
	//draw_test();
	glPopMatrix();
	glutSwapBuffers();
}

static void setup_camera() {
	Eigen::Vector3f camera_position = game.get_ship()->get_position();
	Eigen::Vector3f camera_rotation = game.get_ship()->get_rotation();
	
	//camera_position.z() += 0.3f;
	//camera_rotation.y() = (90.f - camera_rotation.y()) * 0.2f;
	glRotatef(camera_rotation.y(), 0.f, 1.f, 0.f);
	glTranslatef(0.f, 0.f, -camera_position.z());
}

static void setup_lighting() {
	GLfloat global_ambient[] = {0.3f, 0.3f, 0.0f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	
	GLfloat light[] = {1.0f, 1.0f, 1.0f, 1.0f};
	
	GLfloat light_position0[] = {1.f, 1.f, 1.f, 0.f};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light);

	GLfloat light_position1[] = {-1.f, -1.f, 1.f, 0.f};
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

static void setup_shading() {
	GLfloat material_ambient[] = {0.2f, 0.2f, 0.f, 0.f};
	GLfloat material_diffuse[] = {1.0f, 1.0f, 0.f, 0.f};
	GLfloat material_specular[] = {1.f, 1.f, 1.f, 0.f};
	GLfloat material_shininess[] = {50.f};

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

static void update() {
	Time::update_time();
	float delta_time = Time::get_time_difference();
	if(delta_time >= (1.0f/ game.get_fps())) {
		game.update();
		glutPostRedisplay();
	}
}

/*
static void draw_test() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-5,-2,-5.0);
	glVertex3f(5,0.0,-5.0);
	glVertex3f(0.0,5,-5.0);
	glEnd();
}

static void draw_text(float x, float y, void* font, const char* text, Game::Color const& color) {}

static void draw_score(char* score) {
	void* font = GLUT_BITMAP_9_BY_15;
	int score_width = glutBitmapWidth(font, score[0]) * strlen(score);
	int score_pos_x = WIDTH - score_width - 20;
	int score_pos_y = 20;

	draw_text(score_pos_x, score_pos_y, font, score, Game::Color(1.f, 1.f, 1.f));
}
*/

static void key_pressed(unsigned char key, int x, int y) {
	if(game.get_state() == Game::GameState::GAME) {
		switch(key) {
			case 'x': 
				game.get_ship()->start_roll(Ship::RollingDirections::X); break;
			case 'y': 
				game.get_ship()->start_roll(Ship::RollingDirections::Y); break;
			case 'z': 
				game.get_ship()->start_roll(Ship::RollingDirections::Z); break;
			default: break;
		}
	}
}

static void key_pressed_special(int key, int x, int y) {}

static void mouse_clicked(int button, int state, int x, int y) {
	std::cout << "mouse clicked " << std::endl;
	game.fire_missile();
	//game.fire_bomb();
	mouse_moved(x, y);
}

static void mouse_moved(int x, int y) {
	if(x < 0 || y < 0 || x >= game.get_width() || y >= game.get_height())
		return;
	game.set_mousex(x);
	game.set_mousey(y);
}

static void ortho_graphic_projection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluOrtho2D(0, game.get_width(), 0, game.get_height());
	glScalef(1, -1, 1);
	glTranslatef(0, -game.get_height(), 0);
	glMatrixMode(GL_MODELVIEW);
}

static void reset_perspective_projection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}