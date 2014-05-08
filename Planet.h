#include <iostream>

#include "Ball.h"

class Planet : public Ball {

private:
	std::vector<ObjectGeometry* > asteroid_meshes;
	bool is_asteroid;
	int num_meshes;

public:
	Planet();
	Planet(int num_meshes);
	Planet(const Planet& Planet);
	~Planet();

	void update();

private:
	void load_mesh();
};