#include "Wall.h"
#include "Log.h"
#include <cmath>

BackWall::BackWall() : Wall(0) {}
BackWall::BackWall(float i) : Wall(i) {}

bool BackWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float z = vec.z();
    return z < (distance + ship.z());
}

FrontWall::FrontWall() : Wall(0) {}
FrontWall::FrontWall(float i) : Wall(i) {}

bool FrontWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float z = vec.z();
    return z > distance;
}

BottomWall::BottomWall() : Wall(0) {}
BottomWall::BottomWall(float i) : Wall(i) {}

bool BottomWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float y = vec.y();
    return y < distance;
}

TopWall::TopWall() : Wall(0) {}
TopWall::TopWall(float i) : Wall(i) {}

bool TopWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float y = vec.y();
    return y > distance;
}

RightWall::RightWall() : Wall(0) {}
RightWall::RightWall(float i) : Wall(i) {}

bool RightWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float x = vec.x();
    return distance < x;
}

LeftWall::LeftWall() : Wall(0) {}
LeftWall::LeftWall(float i) : Wall(i) {}

bool LeftWall::collide(Eigen::Vector3f vec, Eigen::Vector3f ship){
    float x = vec.x();
    return x < distance;
}