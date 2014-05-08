#ifndef GAME_H
#define GAME_H

#include <Eigen\Core>
#include <glut.h>
#include <gl\GL.h>

#include "Level.h"
#include "Parser.h"

#include <vector>

#define WIDTH 800
#define HEIGHT 600
#define INIT_FPS 30
#define INIT_CLIP 20
#define WORLD_DEPTH 550

class Ship;
class Planet;

class Game {

public:
	struct Color {
		float red;
		float green;
		float blue;

		Color() {};
		Color(float r, float g, float b) {
			red = r;
			green = g;
			blue = b;
		};
	};

public:
	Ship* ship;
	Planet* planet;
	enum GameState { MENU, GAME, GAMEOVER };

private:
	typedef std::vector<Level*> Levels;

protected:
	Level* current_level;
	int current_level_index;
	Levels levels;

	GameState state;

	int fps;
	int far_clipping_plane;
	int width;
	int height;

	unsigned mousex;
	unsigned mousey;

	float game_over_screen_rotation_y;
	float game_over_screen_rotation_x;

public:
	Game();
	~Game();

	void init_game_properties();
	void load_levels();

	void load_current_level();
	Level* get_current_level();

	void set_ship(Ship& ship);
	Ship* get_ship() const;

	void set_width(int width);
	void set_height(int height);
	void set_size(int width, int height);

	int get_width();
	int get_height();

	int get_health() const;
	void set_health(int health);
	GameState get_state();

	unsigned int get_mousey() const;
	unsigned int get_mousex() const;

	void set_mousey(unsigned int my);
	void set_mousex(unsigned int mx);

	void set_up();
	void set_down();
	void set_left();
	void set_right();

	GameState get_game_state();
	int get_clipping_plane();
	int get_fps();

	void fire_missile();
	void fire_bomb();

	void draw();
	void draw_menu_screen();
	void draw_game_screen();
	void draw_game_over_screen();
	void draw_bar(float bar);
	static void draw_text(float x, float y, void* font, const char* text, 
		Game::Color const& color);

	void update();

	static void ortho_graphic_projection();
	static void reset_perspective_projection();
};

#endif