#include "cube.h"

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  V.resize(8,3);
  V <<
    0.0, 0.0, 0.0,     // face 1
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 1.0,
    0.0, 0.0, 1.0,     // face 2
    1.0, 0.0, 1.0,
    1.0, 1.0, 1.0     // face 3
  ;

  F.resize(6,4);
  F << 
    0, 1, 2, 3,
    0, 3, 4, 5,
    4, 5, 6, 7,
    6, 7, 2, 1,
    3, 4, 7, 2,    // top
    0, 5, 6, 1     // bottom
  ;

  UV.resize(14,2);
  UV << 
    0.0, 0.25,    // face 1
    0.0, 0.5,
    0.25, 0.5,
    0.25, 0.25,
    0.25, 0.75,    // face 2
    0.5, 0.75,
    0.5, 0.5,
    0.75, 0.5,    // face 3
    0.75, 0.25,
    0.5, 0.25,
    1.0, 0.5,    // face 4
    1.0, 0.25,
    0.5, 0.0,    // face 5
    0.25, 0.0
  ;

  UF.resize(6,4);
  UF <<
    0, 1, 2, 3,     // red
    3, 2, 6, 9,      // middle square (green)
    6, 7, 8, 9,     // blue
    7, 8, 11, 10,   // orange
    2, 4, 5, 6,     // yellow
    9, 12, 13, 3   // white
  ;

  NV.resize(6,3);
  NV <<
    0.0, 0.0, -1.0,
    -1.0, 0.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, -1.0, 0.0
  ;

  // all corners of planar face share a normal in a faceted surface
  NF.resize(6,4);
  NF <<
    0, 0, 0, 0,
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4,
    5, 5, 5, 5
  ;
}
