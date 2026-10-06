#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
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

  if (t_2 >= min_t) {
    t = t_2;
  }
  else if (t_1 >= min_t) {
    t = t_1;
  }
  else {
    return intersect;
  }

  intersect = true;
  Eigen::Vector3d p = ray.origin + (t * ray.direction);
  n = (p - center) / radius;

  return intersect;
}

