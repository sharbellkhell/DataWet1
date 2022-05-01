#ifndef AVLTREE_H
#define AVLTREE_H
#include "Auxilaries.h"
#include "exceptions.h"

template<class Key, class Value>
struct AVLTree {
    Key key;
    Value value;
    AVLTree* parent;
    AVLTree* left;
    AVLTree* right;
    int height;
 ~AVLTree(){
     //delete(key);
     //delete(value);
 }

//private:
    AVLTree(const Key &key,
            const Value &value,
            AVLTree* parent = nullptr);

    //friend AVLTree* init(const Key&, const Value&, SonType, AVLTree<Key,Value>*);

};

template<class Key,class Value>
AVLTree<Key,Value>* init(const Key &key,
              const Value &value,
              SonType son_type = root,
              AVLTree<Key,Value>* parent = nullptr);

enum NodeChildren {Leaf, HasLeftSon, HasRightSon, HasTwoSons};
// Returns how many and what type of son the tree has.
template<class Key,class Value>
NodeChildren DoesNodeHaveChildren(AVLTree<Key,Value>*);

// enum SonType {isLeft, isRight, root};
// Returns if Node is a left son or a right son, or if it has no parent (root).
template<class Key,class Value>
SonType whichSonIsNode(AVLTree<Key,Value>*);

// Recursive function used to make internal calculations for UpdateHeight()
template<class Key,class Value>
int RecursiveCalcHeight(AVLTree<Key,Value>*);

// Updates Height of Tree and returns it
template<class Key,class Value>
int updateHeight(AVLTree<Key,Value>*);

/*
 * Performs Right Rotation, Returns the upmost Node after rotation
 */
template<class Key,class Value>
AVLTree<Key,Value>* rotateRight(AVLTree<Key,Value>*);

/*
 * Performs left Rotation, Returns the upmost Node after rotation
 */
template<class Key,class Value>
AVLTree<Key,Value>* rotateLeft(AVLTree<Key,Value>*);

/*
 * traverses tree and returns node with specified key
 */
template<class Key,class Value>
AVLTree<Key,Value>* findNode(AVLTree<Key,Value>*, const Key&);

// Calculates and returns Balance Factor
template<class Key, class Value>
int getBF( AVLTree<Key,Value>* );

/*
 * Inserts node into tree and performs required rotations
 */
template<class Key,class Value>
AVLTree<Key,Value>* insertNode( const Key&, const Value&, AVLTree<Key,Value>* = nullptr);

template<class Key,class Value>
AVLTree<Key,Value>* getSmallestNodeBiggerThan(AVLTree<Key,Value>*);

template<class Key, class Value>
AVLTree<Key,Value>* getRoot(AVLTree<Key,Value>* node);

template<class Key,class Value>
void swapData(AVLTree<Key,Value>*, AVLTree<Key, Value>*);

template<class Key, class Value>
AVLTree<Key,Value>* removeNode(AVLTree<Key,Value>* root, const Key& key);

/*
 * fixUpwardPath
 * Performs the necessary rotations in the upward path from "node" to tree root
 * if the function Insert; only one rotation is needed
 * if the function is Delete; Rotations are needed along all the Upward path
 * returns upmost node after fix
 */
enum Function {Delete, Insert};
template<class Key,class Value>
void fixUpwardPath(AVLTree<Key,Value>* , Function);


template<class Key,class Value>
void Quit(AVLTree<Key,Value>* root);

template<class Key, class Value>
void arrayInOrder(AVLTree<Key,Value>* starting_point, int* index,
                  AVLTree<Key,Value>** arr){
    if(starting_point == nullptr){
        return;
    }
    // Call left first
    arrayInOrder(starting_point->left, index, arr);
    // Store root
    arr[*index] = starting_point;
    // Call right last with incremented index
    (*index)++;
    arrayInOrder(starting_point->right, index, arr);
}

template<class Key,class Value>
AVLTree<Key, Value>** mergeTwoSortedArrays(AVLTree<Key, Value>** array_a,
                                           AVLTree<Key, Value>** array_b,
                                           int a_size, int b_size){

    // TODO FREE AFTER
    AVLTree<Key, Value>** merged_array = new AVLTree<Key, Value>*[a_size+b_size];
    int a_index = 0;
    int b_index = 0;
    int merged_index = 0;
    while(a_index < a_size && b_index < b_size){
        if(array_a[a_index]->key < array_b[b_index]->key){
            merged_array[merged_index++] = array_a[a_index++];
        }
        else{
            merged_array[merged_index++] = array_b[b_index++];
        }
    }
    // if there's elements left in array_a
    while(a_index < a_size){
        merged_array[merged_index++] == array_a[a_index++];
    }
    // if there's elements left in array_b
    while(b_index < b_size){
        merged_array[merged_index++] == array_b[b_index++];
    }
    return merged_array;
}

template<class Key, class Value>
AVLTree<Key, Value>* recursiveConvertArrayToAVL(AVLTree<Key, Value>** arr,
                                       int start_point,
                                       int end_point){

    // We take the middle element of the array and place it as root
    int root_index = (start_point + end_point) / 2;
    AVLTree<Key,Value>* root = init<Key,Value>(arr[root_index]->key,
                                              arr[root_index]->value);
    // Use the lower-half of the array to build the left of root
    root->left = recursiveConvertArrayToAVL(arr, start_point, root_index-1);
    root->left->parent = root;
    // Use the upper-half of the array to build the right of root
    root->right = recursiveConvertArrayToAVL(arr, root_index+1, end_point);
    root->right->parent = root;

    return root;
}




#endif //AVLTREE_H
