#include "per_face_normals.h"
#include "triangle_area_normal.h"

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  // Compute per-face normals for a triangle mesh

  int a, b, c;
  N.resize(F.rows(), 3);
  
  for (int i = 0; i < F.rows(); i++) {
    a = F(i, 0);
    b = F(i, 1);
    c = F(i, 2);

    N.row(i) = triangle_area_normal(V.row(a), V.row(b), V.row(c)).normalized();
  }
}
