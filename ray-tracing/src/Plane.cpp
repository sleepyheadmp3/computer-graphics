#include "Plane.h"
#include "Ray.h"
#include <iostream>
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  // intersect plane with ray

  bool hit = false;
  double denom = ray.direction.dot(normal);


  // demon == 0, aka ray is parallel
  if (denom < 1e-6 && denom > -1e-6) {
    return hit;
  }

  t = (point.dot(normal) - ray.origin.dot(normal)) / denom;
  n = normal.normalized();

  if (t >= min_t) {
    hit = true;
  }

  return hit;
}

