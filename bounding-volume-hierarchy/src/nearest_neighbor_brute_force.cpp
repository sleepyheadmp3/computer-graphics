#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{

double min_distance = std::numeric_limits<double>::infinity();
double distance;
double min_i = -1;

for (int i = 0; i < points.rows(); i++) {
  double x = points(i, 0) - query[0];
  double y = points(i, 1) - query[1];
  double z = points(i, 2) - query[2];
  distance = (x * x) + (y * y) + (z * z);
  
  if (distance < min_distance) {
    min_distance = distance;
    min_i = i;
  }
}

  I = min_i;
  sqrD = min_distance;
  
}
