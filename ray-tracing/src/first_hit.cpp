#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  bool hit = false;
  double t_min = std::numeric_limits<double>::infinity();
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
