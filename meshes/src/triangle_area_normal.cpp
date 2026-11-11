#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
  // Compute the normal vector of a 3D triangle given its corner locations. The
  // output vector should have length equal to the area of the triangle.

  Eigen::RowVector3d e1 = b - a;
  Eigen::RowVector3d e2 = c - a;

  // length of parallelogram
  Eigen::RowVector3d n = e1.cross(e2);

  return n * 0.5;
}
