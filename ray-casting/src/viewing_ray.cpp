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

  // direction: (u, v, w)
  double u = (camera.width / width) * j + 0.5;
  double v = (camera.height / height) * i + 0.5;
  double w = camera.d * (-1);

  ray.direction << u, v, w;
}

