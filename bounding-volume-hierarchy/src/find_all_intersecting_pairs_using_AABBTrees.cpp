#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
#include <typeinfo> 


void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)

{
  /*
  initialize list of candidate leaf pairs
  leaf_pairs ← {}
  if root_A.box intersects root_B.box
    Q.insert( root_A, root_B )
  while Q not empty
    {nodeA,nodeB} ← Q.pop
    if nodeA and nodeB are leaves
      leaf_pairs.insert( node_A, node_B )
    else if node_A is a leaf
      if node_A.box intersects node_B.left.box
        Q.insert( node_A, node_B.left )
      if node_A.box intersects node_B.right.box
        Q.insert( node_A, node_B.right )
    else if node_B is a leaf
      if node_A.left.box intersects node_B.box
        Q.insert( node_A.left, node_B)
      if node_A.right.box intersects node_B.box
        Q.insert( node_A.right, node_B)
    else
      if node_A.left.box intersects node_B.left.box
        Q.insert( node_A.left, node_B.left )
      if node_A.left.box intersects node_B.right.box
        Q.insert( node_A.left, node_B.right )
      if node_A.right.box intersects node_B.right.box
        Q.insert( node_A.right, node_B.right )
      if node_A.right.box intersects node_B.left.box
        Q.insert( node_A.right, node_B.left )
  */ 

  std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object>>> Q;

  if (box_box_intersect(rootA->box, rootB->box)) {
    Q.push_back(std::make_pair(rootA, rootB));
  }

  while (!Q.empty()) {
    std::shared_ptr<Object> node_A = Q.front().first;
    std::shared_ptr<Object> node_B = Q.front().second;
    Q.pop_front();

    // both leaves
    // reference: https://www.geeksforgeeks.org/cpp/how-to-find-the-type-of-an-object-in-cpp/
    if (typeid(*node_A) != typeid(AABBTree) && typeid(*node_B) != typeid(AABBTree)) {
      leaf_pairs.push_back(std::make_pair(node_A, node_B));
    }

    // node_A is leaf
    else if (typeid(*node_A) != typeid(AABBTree)) {
      std::shared_ptr<AABBTree> B = std::dynamic_pointer_cast<AABBTree>(node_B);

      if (B->left && box_box_intersect(node_A->box, B->left->box)) {
        Q.push_back(std::make_pair(node_A, B->left));
      }
      if (B->right && box_box_intersect(node_A->box, B->right->box)) {
        Q.push_back(std::make_pair(node_A, B->right));
      }
    }

    // node_B is leaf
    else if (typeid(*node_B) != typeid(AABBTree)) {
      std::shared_ptr<AABBTree> A = std::dynamic_pointer_cast<AABBTree>(node_A);

      if (A->left && box_box_intersect(A->left->box, node_B->box)) {
        Q.push_back(std::make_pair(A->left, node_B));
      }
      if (A->right && box_box_intersect(A->right->box, node_B->box)) {
        Q.push_back(std::make_pair(A->right, node_B));
      }
    }

    // both AABBTrees
    else {
      std::shared_ptr<AABBTree> A = std::dynamic_pointer_cast<AABBTree>(node_A);
      std::shared_ptr<AABBTree> B = std::dynamic_pointer_cast<AABBTree>(node_B);

      if (A->left && B->left && box_box_intersect(A->left->box, B->left->box)) {
        Q.push_back(std::make_pair(A->left, B->left));
      }
      if (A->left && B->right && box_box_intersect(A->left->box, B->right->box)) {
        Q.push_back(std::make_pair(A->left, B->right));
      }
      if (A->right && B->left && box_box_intersect(A->right->box, B->left->box)) {
        Q.push_back(std::make_pair(A->right, B->left));
      }
      if (A->right && B->right && box_box_intersect(A->right->box, B->right->box)) {
        Q.push_back(std::make_pair(A->right, B->right));
      }
    }
  }


}


