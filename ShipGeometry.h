#ifndef SHIP_GEOMETRY_H
#define SHIP_GEOMETRY_H

#include "ObjectGeometry.h"

#include <vector>
#include <string>
#include <Eigen\Core>

class ShipGeometry : public ObjectGeometry {

public:
	ShipGeometry();
	ShipGeometry(std::string path, bool bounding_box);

	void log_dump();
	void draw();
};

#endif