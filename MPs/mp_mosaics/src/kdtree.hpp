/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if (curDim < 0 || curDim >= Dim) {
      return false;
     } 
     if (first[curDim] == second[curDim]) {
      return first < second;
     }
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double curr_best_dist = 0;
     double potential_dist = 0;
     for (int j = 0; j < Dim; ++j) {
      curr_best_dist += pow((target[j] - currentBest[j]), 2);
      potential_dist += pow((target[j] - potential[j]), 2);
     }

     if (potential_dist == curr_best_dist) {
      return potential < currentBest;
     }
     return (potential_dist < curr_best_dist);
}


template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> & list, unsigned left, unsigned right, unsigned pivotIndex, int depth){
	Point<Dim> pivotValue = list.at(pivotIndex);
	Point<Dim> temp = list.at(pivotIndex);
	list.at(pivotIndex) = list.at(right);
	list.at(right) = temp;  
	unsigned storeIndex = left;
	for (unsigned i=left; i<right; i++) {
		if (smallerDimVal(list.at(i), pivotValue, depth)) {
			temp = list.at(storeIndex);
			list.at(storeIndex) = list.at(i);
			list.at(i) = temp; 
			storeIndex++;
		}
	}
	temp = list.at(storeIndex);
	list.at(storeIndex) = list.at(right);
	list.at(right) = temp; 
	return storeIndex;
}

template<int Dim>
Point<Dim>& KDTree<Dim>::select(vector<Point<Dim>> & newPoints, unsigned left, unsigned right, unsigned k, int depth){
	if (left==right) {
    return newPoints.at(left);
  }
	unsigned pivotIndex = k;  
	pivotIndex = partition(newPoints, left, right, pivotIndex, depth);
	if (k == pivotIndex) {
    return newPoints.at(k);
  } else if (k < pivotIndex) {
    return select(newPoints, left, pivotIndex-1, k, depth);
  }
	else {
    return select(newPoints, pivotIndex+1, right, k, depth);
  }
}


template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::insert_kdtree_helper(vector<Point<Dim>>& newPoints, unsigned left, unsigned right, int depth)
{
  if (left > right || newPoints.empty() || left < 0 || right < 0 || left >= newPoints.size() || right >= newPoints.size()) {
    return NULL;
  }
  // KDTreeNode * newNode = new KDTreeNode();
  unsigned median = (left + right)/ 2;
  KDTreeNode * newNode = new KDTreeNode(select(newPoints, left, right, median, depth%Dim));
  size++;
  depth++;
  //newNode->point  = newPoints.at(median);
  newNode->left = insert_kdtree_helper(newPoints, left, median-1, depth);
  newNode->right = insert_kdtree_helper(newPoints, median+1, right, depth);
  return newNode;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.empty()) {
      root = new KDTreeNode();
      size = 0;
    } else {
      vector<Point<Dim>> point_vec;
      for (unsigned i = 0; i < newPoints.size(); ++i) {
        point_vec.push_back(newPoints.at(i));
      }
      //vector<Point<Dim>> point_vec = newPoints;
      size = point_vec.size();
      root = insert_kdtree_helper(point_vec, 0, (point_vec.size() - 1),  0);
    }
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * other) {
	subroot = new KDTreeNode();
	subroot->point = other->point;
	copy (subroot->left, other->left);
	copy (subroot->right, other->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
   copy(this->root, other.root);
   size = other.size();
}

template <int Dim>
void KDTree<Dim>::clear(KDTree<Dim>::KDTreeNode* subroot) {
  if (subroot == NULL) {
    return;
  }
  clear(subroot->left);
  clear(subroot->right);
  delete subroot;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
   if (this != &rhs) {
    clear(root);
    }
    copy(this->root, rhs.root);
    size = rhs.size();
	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   clear(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     return findNearestNeighborHelper(query, 0, root );
    // return Point<Dim>();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, int dimension, KDTreeNode* subroot) const
{
  Point<Dim> currentBest = subroot->point;
  if (subroot->left == NULL && subroot->right == NULL) {
    return subroot->point;
  }
  
  bool traverseLeft = false;
  if (smallerDimVal(query, subroot->point, dimension)) { // determines if should traverse left
    if (subroot->left == NULL) {
      currentBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->right);
    } else {
      currentBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->left);
    }
    traverseLeft = true;
  } else { // determines if should traverse right
    if (subroot->right == NULL) {
      currentBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->left);
    } else {
      currentBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->right);
    }
    traverseLeft = false;
  }
  if (shouldReplace(query, currentBest, subroot->point)) {
    currentBest = subroot->point;
  }
  double radius = 0;
  for (int i = 0; i < Dim; ++i) {
    radius += pow((query[i] - currentBest[i]), 2);
  }
  double splitting_distance = pow((subroot->point[dimension] - query[dimension]), 2);

  if (splitting_distance <= radius) { // instance where subtree can have better nearest neighbor
    if (traverseLeft && subroot->right != NULL) {
        Point<Dim> possibleNewBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->right);
        if (shouldReplace(query, currentBest, possibleNewBest)) {
          currentBest = possibleNewBest;
        }
    } else if (!traverseLeft && subroot->left != NULL) {
        Point<Dim> possibleNewBest = findNearestNeighborHelper(query, (dimension+1)%Dim, subroot->left);
        if (shouldReplace(query, currentBest, possibleNewBest)) {
          currentBest = possibleNewBest;
        }
    }
  }
  return currentBest;
}

