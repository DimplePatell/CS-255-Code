/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
 #include <vector>
 using namespace std;

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    if(root == NULL) {
        return V();
    }
    return find(root, key)->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if (subtree == NULL || subtree->key == key) {
        return subtree;
    }
    if (subtree->key < key) {
        return find(subtree->right, key);
    } else {
        return find(subtree->left, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    if (root == NULL) {
        root = new Node(key, value);
    } 
    // else if(find(root, key) == NULL) {
    //     insert(root, key, value);
    // }    
    insert(root, key, value);

}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
    }
    if (value < subtree->value) {
        insert(subtree->left, key, value);
        // if (subtree->left) {
        //     insert(subtree->left, key, value);
        // } else {
        //     subtree->left = new Node(key, value);
        // }
    }
    else if (value > subtree->value) {
        insert(subtree->right, key, value);
        // if (subtree->right) {
        //     insert(subtree->right, key, value);
        // } else {
        //     subtree->right = new Node(key, value);
        // }
    }

    // if (subtree == NULL) {
    //     subtree = new Node{key, value};
    // } else if (value > subtree->value) {
    //     insert(subtree->right, key, value);
    // } else {
    //     insert(subtree->left, key, value);
    // }
    
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    Node* val1 = find(first, first->key);
    Node* val2 = find(second, second->key);
    Node* temp = val1;
    val1->key = val2->key;
    val1->value = val2->value;
    val2->key = temp->key;
    val2->value = temp->value;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    if (root->key == key) {
        root = NULL;
    }
    if (find(root, key) != NULL) {
        remove(root, key);
    }
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    (void) subtree;
    (void) key;
    // your code here
    // vector<k> inOrderKeys = getInorderTraversal();
    // K preVal = NULL;
    // for (unsigned i = 0; i < inOrderKeys.size(); ++i) {
    //     if (inOrderKeys.at(i) == key) {
    //         preVal = inOrderKeys.at(i - 1);
    //         inOrderKeys.erase(i -1); // remove iop?
    //     }
    // }
    // Node* nodeChange = find(preVal);
    // delete nodeChange;



    // vector<std::pair<K, V>> list;
    // for (unsigned j = 0; j < inOrderKeys.size(); ++j) {
    //     list.push_back((make_pair(inOrderKeys.at(i), find(inOrderKeys.at(i)))));
    // }

    // Node* parentNode = NULL;
    // Node *curr = subtree;
    // Node* temp = find(root, key);

    // if (curr == NULL) {
    //     return;
    // }
    // if (curr->left == NULL && curr->right == NULL) {
    //     if (curr != subtree) {
    //         if (parentNode->left == curr) {
    //             parentNode->left = NULL;
    //         } else {
    //             parentNode->right = NULL;
    //         }
    //     } else {
    //         subtree = NULL;
    //     }
    // } else if (curr->left != NULL && curr->right != NULL) {
    //     Node* preVal = (curr->right)->getInorderTraversal();
    //     remove(subtree, preVal->key);
    //     curr->value = preVal->value;
    // } else {
    //     Node *temp = NULL;
    //     if (curr->left !=NULL) {
    //         temp = curr->left;
    //     } else if (curr->right != NULL) {
    //         temp = curr->right;
    //     }
    //     if (curr != subtree) {
    //         if (curr == parentNode->left) {
    //             parentNode->left = temp;
    //         } else {
    //             parentNode->right = temp;
    //         }
    //     } else {
    //         subtree = temp;
    //     }
    // }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> temp = listBuild(inList);
    for (unsigned i = 0; i < inList.size(); ++i) {
        insert(inList.at(i).first, inList.at(i).second);
    }
    return temp;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> v1;
    v1.push_back(1);
    (void) inList;
    return v1;
}