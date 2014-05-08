#ifndef BALL_H
#define BALL_H

#include "ObjectGeometry.h"
#include "MovableModel.h"

class Ball : public MovableModel {

public:
	enum Direction {LEFT, RIGHT, UP, DOWN, NODIRECTION};

protected:
	ObjectGeometry* ball_mesh;
	Direction direction;

public:
	Ball();
	~Ball();
	
	void move(Eigen::Vector3f direction);

private:
	void load_mesh();
};

#endif