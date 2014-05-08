#ifndef SHIP_H
#define SHIP_H

#include "BoundingShape.h"
#include "MovableModel.h"
#include "Geometry.h"

#include <Eigen\Core>

class Ship : public MovableModel {

public:
	enum RollingDirections {X, Y, Z, NONE};
	enum Direction {LEFT, RIGHT, UP, DOWN, NODIRECTION};

protected:
	int rolling;
	int roll_frames;
	int roll_revolutions;
	RollingDirections rolling_direction;
	Direction direction;
	int health;
	
public:
	Ship();
	Ship(Eigen::Vector3f position, Eigen::Vector3f rotation,
		Eigen::Vector3f scale, Eigen::Vector3f color, float radius,
		Geometry* mesh, Eigen::Vector3f velocity, Eigen::Vector3f accelaration);
	~Ship();

	int get_health() const;
	void set_health(int health);

	void calculate_movement(Eigen::Vector3f direction);
	float calculate_accelaration(float accelaration);

	void start_roll(RollingDirections direction);
	void update_roll();

	void draw();
	void update_direction(unsigned int mousex, unsigned int mousey, 
		unsigned int width, unsigned int height);
	void update();
};

#endif