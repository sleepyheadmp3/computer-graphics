#include "sphere.h"
#include <iostream>
#include <cmath>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  // Construct a quad mesh of a sphere wth num_faces_u × num_faces_v faces
  // using a latitude-longitude Mercator parameterization.
  // uv sphere reference: https://danielsieger.com/blog/2021/03/27/generating-spheres.html

  double theta, phi;
  double x, y, z;
  int i0, i1, i2, i3;
  int j0, j1;
  int v_index = 0;
  int f_index = 0;

  V.resize(num_faces_u * (num_faces_v - 1) + 2, 3);
  UV.resize(num_faces_u * (num_faces_v - 1) + 2, 2);
  NV.resize(num_faces_u * (num_faces_v - 1) + 2, 3);
  F.resize(num_faces_u * num_faces_v, 4);

  // top vertex (index #1)
  V.row(v_index) << 0.0, 1.0, 0.0;
  UV.row(v_index) << 0.5, 1.0;
  NV.row(v_index) << 0.0, 1.0, 0.0;
  v_index++;

  // add vertices for every longitude * latitude
  // num_faces_v - 1 = num_faces_v + 1 - 2 poles
  for (int i = 0; i < num_faces_v - 1; i++)
  {
    phi = M_PI * double(i + 1) / double(num_faces_v);
    for (int j = 0; j < num_faces_u; j++)
    {
      theta = 2.0 * M_PI * double(j) / double(num_faces_u);
      x = std::sin(phi) * std::cos(theta);
      y = std::cos(phi);
      z = std::sin(phi) * std::sin(theta);

      V.row(v_index) << x, y, z;
      UV.row(v_index) << double(j) / num_faces_u, 1.0 - (double(i + 1) / num_faces_v);
      NV.row(v_index) << x, y, z;
      v_index++;
    }
  }

  // bottom vertex
  V.row(v_index) << 0.0, -1.0, 0.0;
  UV.row(v_index) << 0.5, 0.0;
  NV.row(v_index) << 0.0, -1.0, 0.0;


  // top and bottom triangle faces
  for (int i = 0; i < num_faces_u; ++i)
  {
    int i0 = i + 1;
    int i1 = (i + 1) % num_faces_u + 1;
    F.row(f_index++) << 0, 0, i1, i0;
    
    i0 = i + num_faces_u * (num_faces_v - 2) + 1;
    i1 = (i + 1) % num_faces_u + num_faces_u * (num_faces_v - 2) + 1;
    F.row(f_index++) << v_index, v_index, i0, i1;
  }

  // quad (faces) for every latitude * longitude
  for (int j = 0; j < num_faces_v - 2; j++)
  {
    j0 = j * num_faces_u + 1;
    j1 = (j + 1) * num_faces_u + 1;
    for (int i = 0; i < num_faces_u; i++)
    {
      i0 = j0 + i;
      i1 = j0 + (i + 1) % num_faces_u;
      i2 = j1 + (i + 1) % num_faces_u;
      i3 = j1 + i;
      F.row(f_index++) << i0, i1, i2, i3;
    }
  }

  UF = F;
  NF = F;
}
