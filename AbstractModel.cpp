#include "AbstractModel.h"

AbstractModel::AbstractModel() {
	trans_matrix = Eigen::Matrix4f::Identity();
}

AbstractModel::~AbstractModel() {}