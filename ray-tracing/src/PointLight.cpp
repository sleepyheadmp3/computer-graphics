#include "PointLight.h"
#include <cmath>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
    // vector from q -> p
    d = p - q;
    max_t = sqrt((d[0] * d[0]) + (d[1] * d[1]) + (d[2] * d[2]));

    if (max_t != 0) {
      d = d / max_t;   // aka normalize
    }

}
