#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  double dist;
  double total_dist = 0;

  for (int i = 0; i < 3; i++) {
    dist = 0;

    // query point is closer than box
    if (query(i) < box.min_corner(i)) {
      dist = box.min_corner(i) - query(i);
    }
    // query is further than box
    else if (query(i) > box.max_corner(i)) {
      dist = query(i) - box.max_corner(i);
    }

    total_dist += dist * dist; 
  }

  return total_dist;
}
