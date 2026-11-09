#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  // Write a triangle or quad mesh to a .obj file
  // reference: https://en.wikipedia.org/wiki/Wavefront_.obj_file

  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");

  std::ofstream obj_file;
  obj_file.open(filename);

  if (!obj_file) {
    return false;
  }

  // V: #V by 3 list of vertex positions
  for (int i = 0; i < V.rows(); i++) {
    obj_file << "v " << V(i, 0) << " " << V(i, 1) << " " << V(i, 2) << "\n";
  }

  // UV: #UV by 2 list of UV positions, 2D parametrization positions
  for (int i = 0; i < UV.rows(); i++) {
    obj_file << "vt " << UV(i, 0) << " " << UV(i, 1) << "\n";
  }

  // NV: #NV by 3 list of normal vectors
  for (int i = 0; i < NV.rows(); i++) {
    obj_file << "vn " << NV(i, 0) << " " << NV(i, 1) << " " << NV(i, 2) << "\n";
  }

  bool vt_same = F.rows() == UF.rows() && F.cols() == UF.cols();
  bool vn_same = F.rows() == NF.rows() && F.cols() == NF.cols();

  // F: #F by poly=(3 or 4) list of mesh face indices into V
  // face elements format: vertex_index/texture_index/normal_index = v/vt/vn
  for (int i = 0; i < F.rows(); i++) {
    obj_file << "f";

    if (vt_same && vn_same) {
      for (int j = 0; j < F.cols(); j++) {   // 3 or 4 max
        obj_file << " " << F(i, j) + 1 << "/" << UF(i, j) + 1 << "/" << NF(i, j) + 1;
      }
    }
    else if (vt_same) {
      for (int j = 0; j < F.cols(); j++) {
        obj_file << " " << F(i, j) + 1 << "/" << UF(i, j) + 1;
      }
    }
    else if (vn_same) {
      for (int j = 0; j < F.cols(); j++) {   // 3 or 4 max
        obj_file << " " << F(i, j) + 1 << "//" << NF(i, j) + 1;
      }
    }
    else {
      for (int j = 0; j < F.cols(); j++) {   // 3 or 4 max
        obj_file << " " << F(i, j) + 1;
      }
    }

    obj_file << "\n";
  }


  obj_file.close();
  
  if (!obj_file) {
    return false;
  }
  return true;
}
