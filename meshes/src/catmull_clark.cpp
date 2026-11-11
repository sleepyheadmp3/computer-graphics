#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  // Conduct num_iters iterations of Catmull-Clark subdivision on a **pure quad**
  // mesh (V,F).
  //
  // Inputs:
  //   V  #V by 3 list of vertex positions
  //   F  #F by 4 list of quad mesh indices into V
  //   num_iters  number of iterations
  // Outputs:
  //   SV  #SV by 3 list of vertex positions
  //   SF  #SF by 4 list of quad mesh indices into SV
  // 

  int v_count = V.rows();
  int f_count = F.rows();

  SV.resize(V.rows(), 3);
  SF.resize(F.rows(), 4);


  for (int iter = 0; iter < num_iters; iter++) {

    // 1) set face points to be avg of vertices
    Eigen::MatrixXd FP(V.rows(), 3);

    for (int i = 0; i < f_count; i++) {
      FP.row(i) = (V.row(F(i, 0)) + V.row(F(i, 1)) + V.row(F(i, 2)) + V.row(F(i, 3))) / 4.0;
    }

    // 2) add edge points (avg of 2 neighboring face points + end edge points)
    std::vector<std::vector<int> > EF;      // faces adjacent to edge
    std::unordered_map<int, int> edge_ids;
    std::vector<std::pair<int, int> > E;    // edge endpoint indices
    Eigen::MatrixXi FE(f_count, 4);     

    for (int i = 0; i < f_count; i++) {

      for (int j = 0; j < 4; j++) {
        int a = F(i, j);
        int b = F(i, (j + 1) % 4);
        int key = (int)std::min(a, b) * v_count + std::max(a, b);

        // new edge, map to new id
        if (edge_ids.find(key) == edge_ids.end()) {
          edge_ids[key] = E.size();
          E.push_back(std::make_pair(std::min(a, b), std::max(a, b)));
          EF.push_back(std::vector<int>());
        }

        int id = edge_ids[key];
        FE(i, j) = id;
        EF[id].push_back(i);
      }
    }


    // write face points after vertices
    SV.resize(v_count + f_count + E.size(), 3);
    for (int i = 0; i < f_count; i++) {
      SV.row(v_count + i) = FP.row(i);
    }

    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(v_count, 3);
    std::vector<bool> on_boundary(v_count, false);

    for (int e = 0; e < E.size(); e++) {
      int a = E[e].first;
      int b = E[e].second;
      Eigen::RowVector3d mid = (V.row(a) + V.row(b)) / 2.0;

      Eigen::RowVector3d edge_point;
      
      if (EF[e].size() == 2) {
        edge_point = (V.row(a) + V.row(b) + FP.row(EF[e][0]) + FP.row(EF[e][1])) / 4.0;
      } 
      else {
        // boundary edge - use midpoint since only one neighboring face
        edge_point = mid;
        on_boundary[a] = true;
        on_boundary[b] = true;
      }

      SV.row(v_count + f_count + e) = edge_point;
      R.row(a) += mid;
      R.row(b) += mid;
    }

    // 3) add edges btwn face and edge points
    // one quad -> 4 new quads, one per corner
    SF.resize(f_count * 4, 4);

    for (int i = 0; i < f_count; i++) {
      int face_pt = v_count + i;

      for (int j = 0; j < 4; j++) {
        int next_e = v_count + f_count + FE(i, j);
        int prev_e = v_count + f_count + FE(i, (j + 3) % 4);

        SF.row(i * 4 + j) = Eigen::RowVector4i(F(i, j), next_e, face_pt, prev_e);
      }
    }

    // 4) move each original vertex to new posiiton:
    //    (F + 2R + (n - 3)P) / n
    Eigen::MatrixXd Fsum = Eigen::MatrixXd::Zero(v_count, 3);
    std::vector<int> n(v_count, 0);

    for (int i = 0; i < f_count; i++) {
      for (int j = 0; j < 4; j++) {
        Fsum.row(F(i, j)) += FP.row(i);
        n[F(i, j)]++;
      }
    }

    for (int v = 0; v < v_count; v++) {

      // F_avg: avg of all n created face points adjacent to P
      // R_avg: avg of all original edge midpoints touching P
      Eigen::RowVector3d F_avg = Fsum.row(v) / (double)n[v];
      Eigen::RowVector3d R_avg = R.row(v) / (double)n[v];

      SV.row(v) = (F_avg + 2.0 * R_avg + (n[v] - 3.0) * V.row(v)) / double(n[v]);
    }
  }
}

