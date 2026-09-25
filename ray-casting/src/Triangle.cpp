// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle//ray-triangle-intersection-geometric-solution.html
#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
using namespace std;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
    // Intersect a triangle with ray.
    bool intersection = false;

    // compute the plane's normal 
    Eigen::Vector3d v0 = get<0>(corners);
    Eigen::Vector3d v1 = get<1>(corners);
    Eigen::Vector3d v2 = get<2>(corners);

    Eigen::Vector3d v0v1 = v1 - v0;
    Eigen::Vector3d v0v2 = v2 - v0;
    n = v0v1.cross(v0v2).normalized();
 

    // if parallel, no interection
    double ndirection = n.dot(ray.direction);
    if (fabs(ndirection) < 1e-6)
        return intersection; 

    double d = -n.dot(v0);
    t = -(n.dot(ray.origin) + d) / ndirection;
    
    // if triangle is behind ray
    if (t < min_t)
      return intersection;
 
    // p = intersection point
    Eigen::Vector3d P = ray.origin + t * ray.direction;
    Eigen::Vector3d perpendicular;
 
    // edge v0v1
    Eigen::Vector3d v0p = P - v0;
    perpendicular = v0v1.cross(v0p);
    if (n.dot(perpendicular) < 0)
      return intersection;
 
    // edge v2v1
    Eigen::Vector3d v2v1 = v2 - v1;
    Eigen::Vector3d v1p = P - v1;
    perpendicular = v2v1.cross(v1p);
    if (n.dot(perpendicular) < 0)
      return intersection;
 
    // edge v2v0
    Eigen::Vector3d v2v0 = v0 - v2;
    Eigen::Vector3d v2p = P - v2;
    perpendicular = v2v0.cross(v2p);
    if (n.dot(perpendicular) < 0)
      return intersection;

    intersection = true;
    return intersection;
}


