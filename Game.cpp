#include "Planet.h"
#include "Game.h"
#include "Parser.h"
#include "Ship.h"
#include "Missile.h"
#include "Bomb.h"

#include <string>

Game::Game() : 
  current_level(NULL),
  current_level_index(0),
  state(GameState::MENU),
  ship(NULL),
  planet(NULL),
  game_over_screen_rotation_y(0),
  game_over_screen_rotation_x(0) {
	init_game_properties();

	levels = Levels();
	load_levels();
	load_current_level();

	ship = new Ship();
	planet = new Planet;
	current_level->get_movable_models()->push_back(ship);
	current_level->add_ship(ship);
	current_level->get_movable_models()->push_back(planet);
}

Game::~Game() {}

void Game::init_game_properties() {
	height = HEIGHT;
	width = WIDTH;
	fps = INIT_FPS;
	far_clipping_plane = INIT_CLIP;

	mousex = width/2;
	mousey = height/2;
}

void Game::load_levels() {
	Parser parser;

	std::string lvls = parser.parse_lvl_names();

	std::stringstream ss(std::stringstream::in);
	ss.str(lvls);
	std::string token;
	while(!ss.eof()) {
		ss >> token;
		Level* level = parser.parse_level(token);
		this->levels.push_back(level);
	}
}

void Game::load_current_level() {
	current_level = levels.at(current_level_index);
	state = GameState::GAME;
}

Level* Game::get_current_level() {
	return current_level;
}

void Game::set_ship(Ship& s) {
	ship = &s;
}

Ship* Game::get_ship() const {
	return ship;
}

void Game::set_width(int width) {
	set_size(width, height);
}

void Game::set_height(int height) {
	set_size(width, height);
}

Game::GameState Game::get_state() {
	return state;
}

void Game::set_size(int width, int height) {
	width = width;
	height = height;
}

int Game::get_width() {
	return width;
}

int Game::get_height() {
	return height;
}

unsigned int Game::get_mousey() const {
	return mousey;
}

unsigned int Game::get_mousex() const {
	return mousex;
}

void Game::set_mousey(unsigned int my) {
	mousey = my;
}

void Game::set_mousex(unsigned int mx) {
	mousex = mx;
}

void Game::set_up() {
	std::cout << "Menu up";
}

void Game::set_down() {
	std::cout << "Menu down";
}

void Game::set_left() {}

void Game::set_right() {}

Game::GameState Game::get_game_state() {
	return state;
}

int Game::get_clipping_plane() {
	return far_clipping_plane;
}

int Game::get_fps() {
	return this->fps;
}

void Game::fire_missile() {
	LaserMissile* missile = new LaserMissile(ship);
	get_current_level()->get_movable_models()->push_back(missile);
}

void Game::fire_bomb() {
	LaserBomb* bomb = new LaserBomb(ship);
	get_current_level()->get_movable_models()->push_back(bomb);
}

void Game::draw() {
	switch(state) {
		case GameState::MENU: draw_menu_screen(); break;
		case GameState::GAME: draw_game_screen(); break;
		case GameState::GAMEOVER: draw_game_over_screen(); break;
		default: break;
	}
}

void Game::update() {
	if(state == GameState::GAME) {
		ship->update_direction(mousex, mousey, width, height);
		ship->update();
		current_level->update();

		if(ship->get_health() <= 0) {
			state = Game::GameState::GAMEOVER;
		} else if((-ship->get_position().z()) > WORLD_DEPTH) {
			state = Game::GameState::GAMEOVER;
		}
	}
}

void Game::draw_menu_screen() {
	void *font = GLUT_BITMAP_9_BY_15;
	char *line1 = (char *) "START MENU";
	char *line2 = (char *) "START MENU";
	char *line3 = (char *) "START MENU";

	int text_width = glutBitmapWidth(font, '_') * strlen(line1);
	draw_text(width/2 - text_width/2 - 30,  30, font, line1, Color(1.0,1.0,1.0));
	draw_text(width/2 - text_width/2 - 30,  45, font, line2, Color(1.0,1.0,1.0));
	draw_text(width/2 - text_width/2 - 30,  60, font, line3, Color(1.0,1.0,1.0));

	glPushMatrix();
	float rotation = 60;
	
	glTranslatef(-0.18, 0.12, -0.1);
    glRotatef(rotation, 0, 1, 0);
	ship->get_mesh()->draw();
    glPopMatrix();

	//renderControlsInfo();
}

void Game::draw_game_over_screen() {
	std::cout << " draw game over screen " << std::endl;
	void* font = GLUT_BITMAP_9_BY_15;
	int text_width;
	
	char* line1 = (char *) "GAME OVER";
	char* line2 = (char *) "GAME OVER";
	char* line3 = (char *) "GAME OVER";
	char* line4 = (char *) "GAME OVER";

	text_width = glutBitmapWidth(font, '_') * strlen(line1);
	draw_text(width/2 - text_width/2 - 30,  50, font, line1, Game::Color(1.0,1.0,1.0));
	draw_text(width/2 - text_width/2 - 30,  65, font, line2, Game::Color(1.0,1.0,1.0));
	draw_text(width/2 - text_width/2 - 30,  80, font, line3, Game::Color(1.0,1.0,1.0));
	draw_text(width/2 - text_width/2 - 30,  95, font, line4, Game::Color(1.0,1.0,1.0));

	// draw score
	font = GLUT_BITMAP_HELVETICA_18;
	std::string score_text = std::string("Final Score: ");
	char finalScore[10];
	score_text.append(finalScore);
	text_width = glutBitmapWidth(font, 's') * score_text.length();
	draw_text(width/2 - text_width/2, height - 100, font, score_text.c_str(), Game::Color(1.f, 1.f, 1.f));
	
	glPushMatrix();
	game_over_screen_rotation_y += 5;
	game_over_screen_rotation_x += 5;
	if(game_over_screen_rotation_y == 360 &&
	   game_over_screen_rotation_x == 360) {
		game_over_screen_rotation_y = 0;
		game_over_screen_rotation_x = 0;
	}
	
	glTranslatef(0, 0, ship->get_position().z());
    glRotatef(game_over_screen_rotation_x, game_over_screen_rotation_y, 1, 0);
	ship->get_mesh()->draw();
    glPopMatrix();

	text_width = glutBitmapWidth(font, 's') * strlen("Retry (r)");
	draw_text(width/4 - text_width/2, height - 30, font, "Retry (r)", Game::Color(1, 1, 1));

	text_width = glutBitmapWidth(font, 's') * strlen("Main Menu (m)");
	draw_text(width -  width/4 - text_width/2, height - 30, font, "Main Menu (m)", Game::Color(1, 1, 1));
}

void Game::draw_game_screen() {
	ship->draw();
	current_level->draw();
	draw_bar(ship->get_health());
}

void Game::ortho_graphic_projection() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glScalef(1, -1, 1);
	glTranslatef(0, -HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::reset_perspective_projection() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void Game::draw_text(float x, float y, void* font, 
  const char* text, Game::Color const& color) {	
	ortho_graphic_projection();
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glColor4f(color.red, color.green, color.blue, 0.8);

	int x1 = x;
	for(const char *c = text; *c != '\0'; c++) {
		glRasterPos2f(x1, y);
		glutBitmapCharacter(font, *c);
		x1 += glutBitmapWidth(font, *c) + 1;
	}
	
	glEnable(GL_LIGHTING);

	glPopMatrix();
	reset_perspective_projection();
}

void Game::draw_bar(float health) {
	ortho_graphic_projection();
	glPushMatrix();
	glLoadIdentity();
	
	glDisable(GL_LIGHTING);
	
	//background
	glColor4f(0.5, 0.5, 0.5, 0.8);
    glBegin(GL_POLYGON);
	glVertex3f(10.f, 10.f, 0.f); //top left
	glVertex3f(110.f, 10.f, 0.f); //top right
	glVertex3f(110.f, 20.f, 0.f); //bottom right
	glVertex3f(10.f, 20.f, 0.f); //bottom left
	glEnd();

	//health
	if(health > 60) {
		glColor4f(0.0, 1.0, 0.0, 0.8); // green
	} else if(health > 30) {
		glColor4f(1.0, 1.0, 0.0, 0.8); // yellow
	} else {
		glColor4f(1.0, 0.0, 0.0, 0.8); // red
	}
	
	glBegin(GL_POLYGON);
	glVertex3f(10.f, 10.f, 1.f); //top left
	glVertex3f(10.f + health, 10.f, 1.f); //top right
	glVertex3f(10.f + health, 20.f, 1.f); //bottom right
	glVertex3f(10.f, 20.f, 1.f); //bottom left
	glEnd();
    
	glEnable(GL_LIGHTING);
    
	glPopMatrix();
	reset_perspective_projection();
}