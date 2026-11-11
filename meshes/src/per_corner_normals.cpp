#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N = Eigen::MatrixXd::Zero(F.rows()*3,3);
// Compute per corner normals for a triangle mesh by computing the area-weighted
// average of normals at incident faces whose normals deviate less than the
// provided threshold.
//
// Inputs:
//   V  #V by 3 list of vertex positions
//   F  #F by 3 list of mesh triangle indices into V
//   corner_threshold  threshold in degrees on sharp angles
// Outputs:
//   N  #F*3 by 3 list of mesh vertex 3D normals, where the normal
//     for corner F(i,j) is at N.row(i*3+j)

  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  // for each face
  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d n = triangle_area_normal(V.row(F(i, 0)), V.row(F(i, 1)), V.row(F(i, 2)));

    // for each corner
    for (int j = 0; j < 3; j++) {
      Eigen::RowVector3d avg = Eigen::RowVector3d::Zero();

      // compute avg of normals at incident faces if similar
      for (int k = 0; k < VF[F(i, j)].size(); k++) {

        // f=VF[i][j] means that face f is the jth face among those incident on vertex i
        int f = VF[F(i, j)][k];
        Eigen::RowVector3d n_x = triangle_area_normal(V.row(F(f, 0)), V.row(F(f, 1)), V.row(F(f, 2)));

        if (n_x.normalized().dot(n.normalized()) > cos(corner_threshold / 180.0 * M_PI)) {
          avg += n_x;
        }
      }

      N.row(i*3+j) = avg.normalized();
    }
  }
}
