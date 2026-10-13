#include "AABBTree.h"
#include "ray_intersect_box.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  // test intersection of whole AABB
  if (!ray_intersect_box(ray, this->box, min_t, max_t)) {
    return false;
  }

  bool hit = false;
  double t_temp = max_t;
  double t_min = max_t;
  std::shared_ptr<Object> dscd_temp;

  // if hit on left
  if (this->left && left->ray_intersect(ray, min_t, t_min, t_temp, dscd_temp)) {
    t_min = std::min(t_min, t_temp);
    descendant = dscd_temp;
    t = t_min;
    hit = true;
  }

  // if hit on right
  if (this->right && right->ray_intersect(ray, min_t, t_min, t_temp, dscd_temp)) {
    t_min = std::min(t_min, t_temp);
    descendant = dscd_temp;
    t = t_min;
    hit = true;
  }
  
  return hit;
}

