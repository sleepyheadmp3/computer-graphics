#include "Sphere.h"
#include "Ray.h"
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{

  // vector3d center, double radius
  // Intersect sphere with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
  
  bool intersect = false;

  // this formula might be wrong
  Eigen::Vector3d e_c = ray.origin - center;
  double a = ray.direction.dot(ray.direction);
  double b = ray.direction.dot(e_c);
  double c = e_c.dot(e_c) - (radius * radius);

  double discriminant = (b * b) - (a * c);
  if (discriminant < 0) {
    return intersect;
  }

  double t_1 = (-b + sqrt(discriminant)) / a;
  double t_2 = (-b - sqrt(discriminant)) / a;

  if (t_1 >= 0 && t_2 >= 0) {
    if (t_1 < t_2) {
      t = t_1;
    }
    else {
      t = t_2;
    }
    intersect = true;
    Eigen::Vector3d p = ray.origin + (t * ray.direction);
    n = (p - center) / radius;
  } 

  return intersect;
}

