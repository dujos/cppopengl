#ifndef BOUNDING_SPHERES
#define BOUNDING_SPHERES

#include <vector>
#include <Eigen\Core>

class BoundingSpheres {

protected:
	std::vector<float> radiuses;
	std::vector<Eigen::Vector3f> centers;

public:
	BoundingSpheres();
	~BoundingSpheres();

	void add(Eigen::Vector3f center, float radius);
};

#endif