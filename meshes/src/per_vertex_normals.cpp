#include "per_vertex_normals.h"
#include "triangle_area_normal.h"

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  // Compute per vertex normals for a triangle mesh by computing the area-weighted
  // average of normals at incident faces.

  N = Eigen::MatrixXd::Zero(V.rows(),3);

  // for each face, add area normal to running sum for each vertex
  for (int i = 0; i < F.rows(); i++) {
    int v0 = F(i, 0);
    int v1 = F(i, 1);
    int v2 = F(i, 2);

    Eigen::RowVector3d area = triangle_area_normal(V.row(v0), V.row(v1), V.row(v2));

    N.row(v0) += area;
    N.row(v1) += area;
    N.row(v2) += area;
  }

  // normalize to get unit normals
  for (int i = 0; i < N.rows(); i++) {
    if (N.row(i).norm() != 0) {
      N.row(i).normalize();
    }
  }
}
