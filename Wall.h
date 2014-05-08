#ifndef WALL_H
#define WALL_H

#include <Eigen/Core>

class Wall {

public:
    float distance;

public:
    Wall();
	Wall(float i) { distance = i; };
    virtual ~Wall() {}

    virtual bool collide(Eigen::Vector3f, Eigen::Vector3f) = 0;
};

class BackWall : public Wall {

public:
    BackWall();
    BackWall(float);
    
	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

class TopWall : public Wall {

public:
    TopWall();
    TopWall(float);
    
	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

class LeftWall : public Wall {

public:
    LeftWall();
    LeftWall(float);
    
	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

class BottomWall : public Wall {

public:
    BottomWall();
    BottomWall(float);

	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

class RightWall : public Wall {

public:
    RightWall();
    RightWall(float);
    
	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

class FrontWall : public Wall {

public:
    FrontWall();
    FrontWall(float);
    
	bool collide(Eigen::Vector3f, Eigen::Vector3f);
};

#endif