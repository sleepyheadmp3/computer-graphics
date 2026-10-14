#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{

  Eigen::RowVector3d AB = B - A;
  Eigen::RowVector3d AC = C - A;
  Eigen::RowVector3d n = AB.cross(AC).normalized();

  // if parallel, no interection
  double ndirection = n.dot(ray.direction);
  if (fabs(ndirection) < 1e-6)
    // return early to avoid dividing by zero
    return false; 

  double d = -n.dot(A);
  t = -(n.dot(ray.origin) + d) / ndirection;
    
  // if triangle is within bounds
  if (t < min_t || t > max_t)
    return false;
 
  // p = intersection point
  Eigen::RowVector3d P = (ray.origin + t * ray.direction).transpose();
  Eigen::RowVector3d perpendicular;
 
  // check edge AB
  Eigen::RowVector3d AP = P - A;
  perpendicular = AB.cross(AP);
  if (n.dot(perpendicular) < 0)
    return false;
 
  // check edge CB
  Eigen::RowVector3d CB = C - B;
  Eigen::RowVector3d BP = P - B;
  perpendicular = CB.cross(BP);
  if (n.dot(perpendicular) < 0)
    return false;
 
  // check edge CA
  Eigen::RowVector3d CA = A - C;
  Eigen::RowVector3d CP = P - C;
  perpendicular = CA.cross(CP);
  if (n.dot(perpendicular) < 0)
    return false;

  return true;
}

