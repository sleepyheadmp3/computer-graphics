#include "first_hit.h"
#include <limits>
using namespace std;

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  // ray: origin, direction

  // Find the first (visible) hit given a ray and a collection of scene objects

  // Inputs:
  //   ray  ray along which to search
  //   min_t  minimum t value to consider (for viewing rays, this is typically at
  //     least the _parametric_ distance of the image plane to the camera)
  //   objects  list of objects (shapes) in the scene
  // Outputs:
  //   hit_id  index into objects of object with first hit
  //   t  _parametric_ distance along ray so that ray.origin+t*ray.direction is
  //     the hit location
  //   n  surface normal at hit location
  // Returns true iff a hit was found

  bool hit = false;
  double t_min = numeric_limits<double>::infinity();
  double t_1;
  Eigen::Vector3d n_1;

  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->intersect(ray, min_t, t_1, n_1) && (t_1 >= min_t)) {
      hit = true;

      // update closest object hit
      if (t_1 < t_min) {
        t_min = t_1;
        hit_id = i;
        t = t_min;
        n = n_1;
      }
    }
  }
  
  return hit;
}

