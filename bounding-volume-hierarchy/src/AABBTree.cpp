#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <limits>
#include <algorithm>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  int n_objects = objects.size();

  // leaf cases
  if (n_objects == 0) {
    this->left = NULL;
    this->right = NULL;
    return;
  }

  if (n_objects == 1) {
    this->left = objects[0];
    this->right = NULL;
    insert_box_into_box(objects[0]->box, this->box);
    return;
  }

  if (n_objects == 2) {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
    return;
  }

  double x_min = std::numeric_limits<double>::infinity();
  double x_max = -std::numeric_limits<double>::infinity();
  double y_min = std::numeric_limits<double>::infinity();
  double y_max = -std::numeric_limits<double>::infinity();
  double z_min = std::numeric_limits<double>::infinity();
  double z_max = -std::numeric_limits<double>::infinity();

  // find longest axis of box to determine split / midpoint
  for (int i = 0; i < n_objects; i++) {
    x_min = std::min(x_min, objects[i]->box.min_corner(0));
    x_max = std::max(x_max, objects[i]->box.max_corner(0));
    y_min = std::min(y_min, objects[i]->box.min_corner(1));
    y_max = std::max(y_max, objects[i]->box.max_corner(1));
    z_min = std::min(z_min, objects[i]->box.min_corner(2));
    z_max = std::max(z_max, objects[i]->box.max_corner(2));
  }

  double x_len = x_max - x_min;
  double y_len = y_max - y_min;
  double z_len = z_max - z_min;

  double max_len = std::max({x_len, y_len, z_len});
  int axis;

  if (max_len == x_len) {
    axis = 0;
  }
  else if (max_len == y_len) {
    axis = 1;
  }
  else {
    axis = 2;
  }

  // update box info for this tree
  this->box.min_corner = Eigen::RowVector3d(x_min, y_min, z_min);
  this->box.max_corner = Eigen::RowVector3d(x_max, y_max, z_max);

  // sort all objects into left and right of midpoint
  // store in a vector of object ptrs
  double midpoint = this->box.center()[axis];
  std::vector<std::shared_ptr<Object>> left_objs, right_objs;

  for (int i = 0; i < n_objects; i++) {
    if (objects[i]->box.center()[axis] < midpoint) {
      left_objs.push_back(objects[i]);
    }
    else {
      right_objs.push_back(objects[i]);
    }
  }

  // moves one object over to prevent infinite recursion
  if (left_objs.empty()) {
    left_objs.push_back(right_objs.back());
    right_objs.pop_back();
  }
  else if (right_objs.empty()) {
    right_objs.push_back(left_objs.back());
    left_objs.pop_back();
  }

  // recurse thru left and right subtrees
  this->left = std::make_shared<AABBTree>(left_objs, a_depth + 1);
  this->right = std::make_shared<AABBTree>(right_objs, a_depth + 1);

}
