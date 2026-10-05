#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  
  int hit_id;
  double t;
  Eigen::Vector3d n;

  if (first_hit(ray, min_t, objects, hit_id, t, n)) {

    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    Eigen::Vector3d km = objects[hit_id]->material->km;

    if (num_recursive_calls < 10 && !km.isZero()) {

      // reflection origin = prev hit location
      Ray reflection;
      reflection.origin = ray.origin + (t * ray.direction);
      reflection.direction = reflect(ray.direction.normalized(), n);

      Eigen::Vector3d reflection_rgb;

      if (raycolor(reflection, 1e-6, objects, lights, num_recursive_calls + 1,
        reflection_rgb)) {

          // color c = c + km * raycolor(next)
          rgb += (km.array() * reflection_rgb.array()).matrix();
        
      }
    }

    return true;
  }

  rgb = Eigen::Vector3d(0,0,0);
  return false;

}
