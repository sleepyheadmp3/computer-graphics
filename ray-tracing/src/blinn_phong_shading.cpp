#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{

  Eigen::Vector3d hit_point = ray.origin + (t * ray.direction);
  auto mat = objects[hit_id]->material;
  int n_lights = lights.size();

  // L = ambient + lambertian + specular
  // ambient light: ka * ia (0.1)
  Eigen::Vector3d L = mat->ka * 0.1;


  for (int i = 0; i < n_lights; i++) {

    Eigen::Vector3d d;
    double max_t;
    lights[i]->direction(hit_point, d, max_t);

    Ray toward_light;
    toward_light.origin = hit_point;
    toward_light.direction = d;

    int x_id;
    double x_t;
    Eigen::Vector3d x_n;
    
    
    // only compute if light is unobstructed || hit beyond light
    if (!first_hit(toward_light, 1e-6, objects, x_id, x_t, x_n) ||
      x_t >= max_t) {
      
      Eigen::Vector3d I = lights[i]->I;

      // lambertian shading: kd * intensity * max(0, n.dot(l))
      L += (mat->kd.array() * I.array()).matrix() * std::max(0.0, n.dot(d));

      // specular shading: ks * intensity * max(0, cos(n, h))^p
      // h = halfway vector btwn point -> light and point -> viewer
      Eigen::Vector3d h = (toward_light.direction +
        -ray.direction.normalized()).normalized();

      L += (mat->ks.array() * I.array()).matrix() *
        std::pow(std::max(0.0, n.dot(h)), mat->phong_exponent);
    }
    
  }

  return L;
}
