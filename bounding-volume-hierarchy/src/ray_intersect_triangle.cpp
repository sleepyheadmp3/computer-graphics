#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{

  Eigen::Vector3d AB = B - A;
  Eigen::Vector3d AC = C - A;
  Eigen::Vector3d n = AB.cross(AC).normalized();

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
  Eigen::Vector3d P = ray.origin + t * ray.direction;
  Eigen::Vector3d perpendicular;
 
  // check edge AB
  Eigen::Vector3d AP = P - A;
  perpendicular = AB.cross(AP);
  if (n.dot(perpendicular) < 0)
    return false;
 
  // check edge CB
  Eigen::Vector3d CB = C - B;
  Eigen::Vector3d BP = P - B;
  perpendicular = CB.cross(BP);
  if (n.dot(perpendicular) < 0)
    return false;
 
  // check edge CA
  Eigen::Vector3d CA = A - C;
  Eigen::Vector3d CP = P - C;
  perpendicular = CA.cross(CP);
  if (n.dot(perpendicular) < 0)
    return false;

  return true;
}

