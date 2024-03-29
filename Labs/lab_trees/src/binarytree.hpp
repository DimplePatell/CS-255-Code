/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <stack>
#include <math.h>

using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    traverseTree(root);
}

    template <typename T>
    void BinaryTree<T>::traverseTree(Node * subRoot)
{
    //your code here
    if (subRoot == NULL) {
        return;
    }
    traverseTree(subRoot->left);
    traverseTree(subRoot->right);
    Node *temp = subRoot->left;
    subRoot->left = subRoot->right;
    subRoot->right = temp;

}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    if (root == NULL) {
        return true;
    }
    stack <Node *> s;
    Node * prev = NULL;
    Node * curr = root;
    while (!s.empty() || curr != NULL) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr ->left;
        }
        curr = s.top();
        s.pop();
        if (prev != NULL && curr->elem < prev->elem) {
            return false;
        }
        prev = curr;
        curr = curr->right;
    }
    return true;
}


template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::LeftVal(typename BinaryTree<T>::Node *subRoot) const{
    if (subRoot == NULL){
        return NULL;
    }
    if (subRoot->left == NULL){
        return subRoot;
    }
    return LeftVal(subRoot->left);
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::RightVal(typename BinaryTree<T>::Node *subRoot) const{
    if (subRoot == NULL){
        return NULL;
    }
    if (subRoot->right == NULL){
        return subRoot;
    }
    return RightVal(subRoot->right);
}


template <typename T>
bool BinaryTree<T>::isOrderedHelper(const Node* subRoot) const {
    if (subRoot == NULL) {  
        return true;
    }
    if (subRoot->left != NULL){
        if (RightVal(subRoot->left)->elem > subRoot->elem){
            return false;
        }
    }
    if (subRoot->right != NULL){
        if (LeftVal(subRoot->right)->elem < subRoot->elem){
            return false;
        }
    }
    if (!isOrderedHelper(subRoot->left) || !isOrderedHelper(subRoot->right)){
        return false;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    // your code here
    return isOrderedHelper(root);
}

