#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  // Construct a viewing ray given a camera and subscripts to a pixel
  ray.origin = camera.e;

  // image center
  Eigen::Vector3d a = camera.e - (camera.d * camera.w);

  // top left corner
  Eigen::Vector3d b = a + ((camera.height / 2) * camera.v) - ((camera.width / 2) * camera.u);

  Eigen::Vector3d s = b + 
    (camera.u * camera.width * (j + 0.5) / width) -
    (camera.v * camera.height * (i + 0.5) / height);
  
  ray.direction = s - camera.e;
}
