#include "ray_intersect_box.h"
#include <iostream>
#include <algorithm>
#include <limits>


bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  double t_xmin = -std::numeric_limits<double>::infinity();
  double t_xmax = std::numeric_limits<double>::infinity();
  double t_ymin = -std::numeric_limits<double>::infinity();
  double t_ymax = std::numeric_limits<double>::infinity();
  double t_zmin = -std::numeric_limits<double>::infinity();
  double t_zmax = std::numeric_limits<double>::infinity();


  // t_imin = (i_min - i_e) / i_d, from slides

  if (ray.direction(0) != 0) {
    t_xmin = (box.min_corner(0) - ray.origin(0)) / ray.direction(0);
    t_xmax = (box.max_corner(0) - ray.origin(0)) / ray.direction(0);
    if (t_xmax < t_xmin) {
      std::swap(t_xmin, t_xmax);
    }
  }
  // check if origin lies inside box when direction is 0
  else if (ray.origin(0) < box.min_corner(0) || ray.origin(0) > box.max_corner(0)) {
    return false;
  }

  if (ray.direction(1) != 0) {
    t_ymin = (box.min_corner(1) - ray.origin(1)) / ray.direction(1);
    t_ymax = (box.max_corner(1) - ray.origin(1)) / ray.direction(1);
    if (t_ymax < t_ymin) {
      std::swap(t_ymin, t_ymax);
    }
  }
  else if (ray.origin(1) < box.min_corner(1) || ray.origin(1) > box.max_corner(1)) {
    return false;
  }

  if (ray.direction(2) != 0) {
    t_zmin = (box.min_corner(2) - ray.origin(2)) / ray.direction(2);
    t_zmax = (box.max_corner(2) - ray.origin(2)) / ray.direction(2);
    if (t_zmax < t_zmin) {
      std::swap(t_zmin, t_zmax);
    }
  }
  else if (ray.origin(2) < box.min_corner(2) || ray.origin(2) > box.max_corner(2)) {
    return false;
  }

  // find intersection of intervals
  double t_max = std::max({t_xmin, t_ymin, t_zmin});
  double t_min = std::min({t_xmax, t_ymax, t_zmax});

  if (t_max <= t_min && t_min >= min_t && t_max <= max_t) {
    return true;
  }

  return false;
}
