#ifndef EXPLOSION
#define EXPLOSION

#include "Geometry.h"

class Explosion : public Geometry {

public:
	Explosion();
	~Explosion();

	void draw();
	void update();
};


#endif