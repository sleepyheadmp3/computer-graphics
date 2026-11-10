#include "vertex_triangle_adjacency.h"

void vertex_triangle_adjacency(
  const Eigen::MatrixXi & F,
  const int num_vertices,
  std::vector<std::vector<int> > & VF)
{
  // Compute a vertex-triangle adjacency list. For each vertex store a list of all
  // incident faces.
  
  VF.resize(num_vertices);

  // for each triangle face (indices list)
  for (int i = 0; i < F.rows(); i++) {

    // for each vertex index
    for (int j = 0; j < 3; j++) {
      VF.at(F(i, j)).push_back(i);
    }
  }
}

