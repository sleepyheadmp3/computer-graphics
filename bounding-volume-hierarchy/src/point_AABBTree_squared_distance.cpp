#include "point_AABBTree_squared_distance.h"
#include "point_box_squared_distance.h"
#include <queue> // std::priority_queue
#include <iostream>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
  {

  // initialize a queue prioritized by minimum distance
  // d_r ← distance to root's box
  // Q.insert(d_r, root)
  // initialize minimum distance seen so far
  // d ← ∞
  // while Q not empty 
      // (d_s, subtree) ← Q.pop
      // if d_s < d
        // if subtree is a leaf
          // d ← min[ d , distance from query to leaf object ]
        // else
          // d_l ← distance to left's box
          // Q.insert(d_l ,subtree.left)
          // d_r ← distance to right's box
          // Q.insert(d_r ,subtree.right)


  bool found = false;

  // queue entries: <distance, descendant ptr>
  typedef std::pair<double, std::shared_ptr<AABBTree>> dist_pair;
  std::priority_queue<dist_pair, std::vector<dist_pair>, std::greater<dist_pair>> Q;

  double d_r = point_box_squared_distance(query, root->box);
  double d = std::numeric_limits<double>::infinity();
  double d_l;

  Q.push(dist_pair(d_r, root));

  while (!Q.empty()) {
    // d_s: distance from query to subtree's bounding box
    dist_pair curr = Q.top();
    double d_s = curr.first;
    std::shared_ptr<AABBTree> subtree = curr.second;
    Q.pop();

    if (d_s > max_sqrd || d_s > d) {
      break;
    }

    if (d_s < d) {

      // if second-to-last level (above leaves)
      if (subtree->num_leaves <= 2){
        std::shared_ptr<Object> leaf_l;
        std::shared_ptr<Object> leaf_r;
        double leaf_dist;

        if(subtree->left){

          // distance to actual object itself, not box
          if(subtree->left->point_squared_distance(query, min_sqrd, d, leaf_dist, leaf_l)){
            d = leaf_dist;
            descendant = subtree->left;
            found = true;
          }
        }
        if(subtree->right){
          if(subtree->right->point_squared_distance(query, min_sqrd, d, leaf_dist, leaf_r)){
            d = leaf_dist;
            descendant = subtree->right;
            found = true;
          }
        }
      }

      // if AABBTree object
      else {
        if (subtree->left) {
          d_l = point_box_squared_distance(query, subtree->left->box);
          Q.push(dist_pair(d_l, std::dynamic_pointer_cast<AABBTree>(subtree->left)));
        }
        if (subtree->right) {
          d_r = point_box_squared_distance(query, subtree->right->box);
          Q.push(dist_pair(d_r, std::dynamic_pointer_cast<AABBTree>(subtree->right)));
        }
      }
    }
  }

  if (found) {
    sqrd = d;
  }
  return found;

}
