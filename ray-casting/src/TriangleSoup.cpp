#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  bool hit = false;
  int hit_id;

  hit = first_hit(ray, min_t, triangles, hit_id, t, n);

  return hit;
}