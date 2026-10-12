#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  // inserts A into B

  for (int i = 0; i < 3; i++) {
    if (A.min_corner(0) < B.min_corner(0)) {
      B.min_corner(0) = A.min_corner(0);
    }
    if (A.max_corner(0) > B.max_corner(0)) {
      B.max_corner(0) = A.max_corner(0);
    }
  }
}

