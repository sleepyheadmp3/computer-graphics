#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  // V: {{x, y, z}, {...}} = vertex coordinates
  // F: {{v1, v2, v3}, {...}} = vertices of triangle (V indices)

  double t_min = max_t;
  bool hit = false;
  double temp_t;
  hit_t = 0;
  hit_f = 0;

  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d A = V.row(F(i, 0));
    Eigen::RowVector3d B = V.row(F(i, 1));
    Eigen::RowVector3d C = V.row(F(i, 2));

    if (ray_intersect_triangle(ray, A, B, C, min_t, t_min, temp_t)) {
      if (temp_t < t_min) {
        hit_f = i;
        t_min = temp_t;
        hit = true;
      }
    }
  }

  hit_t = t_min;
  return hit;
}
