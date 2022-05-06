#include "AVLTree.h"
#include <assert.h>
#include <iostream> //TODO delete after debug


/* --------------------------------------------------------------------------------------------------------------------
 *                                             Constructing the AVL Tree
  --------------------------------------------------------------------------------------------------------------------*/

/*
 * Constructor
 */
template<class Key, class Value>
AVLTree<Key,Value>::AVLTree(const Key &key, const Value &value, AVLTree* parent)
 : key(key) , value(value) , parent(parent) , left(nullptr) , right(nullptr), height(0) {}


 /*
  * Function that fully initializes a Node, and links it with the rest of the Tree
  */
template<class Key, class Value>
AVLTree<Key,Value>* init(const Key &key, const Value &value,
              SonType son_type, AVLTree<Key,Value>* parent){

    AVLTree<Key,Value>* n1 = new AVLTree<Key,Value>(key, value, parent);
    switch (son_type) {
        case isRight:
            parent->right = n1;
            break;
        case isLeft:
            parent->left = n1;
            break;
        case root:
            break;
    }
    return n1;
    
}

/* --------------------------------------------------------------------------------------------------------------------
 *                                   Functions to query a Node's Specifications
  --------------------------------------------------------------------------------------------------------------------*/


/*
 * Returns How many and what children a node has.
 */
template<class Key, class Value>
NodeChildren DoesNodeHaveChildren(AVLTree<Key,Value>* tree){
    if(tree->right == nullptr && tree->left == nullptr){
        return Leaf;
    }
    if(tree->right != nullptr && tree->left == nullptr){
        return HasRightSon;
    }
    if(tree->right == nullptr && tree->left != nullptr){
        return HasLeftSon;
    }
    return HasTwoSons;
}

/*
 * Returns if Node is a Right, left son or a root.
 */
template<class Key,class Value>
SonType whichSonIsNode(AVLTree<Key,Value>* node){
    if(node->parent == nullptr){
        return root;
    }
    else if ((node->parent->right != nullptr) && (node->parent->right == node)){
        return isRight;
    } else{
        return isLeft;
    }
}

template<class T>
T max(T a, T b){
    return (a>b ? a : b);
}

/*
 * internal function that recursively calculates height
 */
template<class Key, class Value>
int RecursiveCalcHeight(AVLTree<Key,Value>* node) {
    if(node == nullptr){
        return -1;
    }
    int rightHeight = RecursiveCalcHeight(node->right);
    int leftHeight = RecursiveCalcHeight(node->left);
    return (max<int>(rightHeight, leftHeight) + 1);
}

/*
 * Updates and returns node height
 */
template<class Key, class Value>
int updateHeight(AVLTree<Key,Value>* node){
    if(node == nullptr) return -1;
    node->height = RecursiveCalcHeight(node);
    return (node->height);
}

/*
 * Calculates and returns Balance Factor
 */
template<class Key, class Value>
int getBF( AVLTree<Key,Value>* node){
    if(node == nullptr){
        return 0;
    }
    return(updateHeight(node->left) - updateHeight(node->right) );

}

/*
 * Returns root of a tree
 */
template<class Key, class Value>
AVLTree<Key,Value>* getRoot(AVLTree<Key,Value>* node){
    if(node->parent == nullptr){
        return node;
    }
    return (getRoot(node->parent));
}


/* --------------------------------------------------------------------------------------------------------------------
 *                                                ROTATIONS
  --------------------------------------------------------------------------------------------------------------------*/

template<class Key,class Value>
AVLTree<Key,Value>* rotateLeft(AVLTree<Key,Value>* A){
    //The following two defs are needed to link nodes with outside tree after rotation
    AVLTree<Key,Value>* absolute_parent = A->parent;
    SonType absolute_son_type = whichSonIsNode(A);
    AVLTree<Key,Value>* B = A->right;
    assert(B); // if reached assert, we are performing illegal rotation
    AVLTree<Key,Value>* Bl = B->left;
    B->left = A;
    A->right = Bl;
    A->parent = B;
    if(Bl != nullptr) {
        Bl->parent = A;
    }
    //relink with outside tree
    B->parent = absolute_parent;
    switch(absolute_son_type){
        case isLeft:{
            absolute_parent->left = B;
            break;
        }
        case isRight:{
            absolute_parent->right = B;
            break;
        }
        case root:{
            break;
        }
    }
    return B;
}


template<class Key,class Value>
AVLTree<Key,Value>* rotateRight(AVLTree<Key,Value>* B){
    AVLTree<Key,Value>* absolute_parent = B->parent;
    SonType absolute_son_type = whichSonIsNode(B);

    AVLTree<Key,Value>* A = B->left;
    assert(A); // if reached assert, we are performing illegal rotation
    AVLTree<Key,Value>* Ar = A->right;
    //Ar = (A != nullptr ? A->right : nullptr);
    A->right = B;
    B->left = Ar;
    B->parent = A;
    if(Ar != nullptr){
        Ar->parent = B;
    }
    A->parent = absolute_parent;
    switch(absolute_son_type){
        case isLeft:{
            absolute_parent->left = A;
            break;
        }
        case isRight:{
            absolute_parent->right = A;
            break;
        }
        case root: {break;
        }
    }
    return A;
}

/* --------------------------------------------------------------------------------------------------------------------
 *                                                Tree Traversal
  --------------------------------------------------------------------------------------------------------------------*/


template<class Key,class Value>
AVLTree<Key,Value>* findNode(AVLTree<Key,Value>* root , const Key& key){
    AVLTree<Key,Value>* iterator_node = root;
    while(iterator_node != nullptr && iterator_node->key != key){
        if(iterator_node->key < key ){
            iterator_node = iterator_node->right;
        } else {
            iterator_node = iterator_node->left;
        }
    }
    return iterator_node;
}

template<class Key,class Value>
void highest_to_lowest(AVLTree<Key,Value*>* root, Key** keys,int* total_keys)
{
    if(root == nullptr)
        return;
    highest_to_lowest(root->right,keys,total_keys);
    (*keys)[*total_keys]=(root->key);
    *total_keys=*total_keys+1;
    highest_to_lowest(root->left,keys,total_keys);
}

template<class Key,class Value>
void lowest_to_highest(AVLTree<Key,Value*>* root, Key** keys,int* total_keys)
{
    if(root==nullptr)
        return;
    lowest_to_highest(root->left,keys,total_keys);
    (*keys)[*total_keys]=(root->key);
    *total_keys=*total_keys+1;
    lowest_to_highest(root->right,keys,total_keys);
}

/* --------------------------------------------------------------------------------------------------------------------
 *                                                Insert Node
  --------------------------------------------------------------------------------------------------------------------*/

/*
 * fixUpwardPath
 * Performs the necessary rotations in the upward path from "node" to tree root
 * if the function Insert; only one rotation is needed
 * if the function is Delete; Rotations are needed along all the Upward path
 * returns upmost node after fix
 */
template<class Key, class Value>
void fixUpwardPath(AVLTree<Key,Value>* node, Function function) {
    while( node != nullptr ) {
        int root_bf = getBF(node);
        if (root_bf == 2) {
            if (getBF(node->left) >= 0) {
                // ROTATE LL
                node = rotateRight(node);
                if(function == Insert) { break; }
            } else if (getBF(node->left) == -1) {
                // ROTATE LR
                rotateLeft(node->left);
                node = rotateRight(node);
                if(function == Insert) { break; }
            }
        } else if (root_bf == -2) {
            if (getBF(node->right) == 1) {
                // ROTATE RL
                rotateRight(node->right);
                node = rotateLeft(node);
                if(function == Insert) { break; }
            } else if (getBF(node->right) <= 0) {
                // ROTATE RR
                node = rotateLeft(node);
                if(function == Insert) { break; }
            }
        }
        node = node->parent;
    }
}


template<class Key,class Value>
AVLTree<Key,Value>* insertNode(const Key& key, const Value& value, AVLTree<Key,Value>* root){
    if(root == nullptr){
        return init(key, value);
    }
    if(key <= 0){
        throw InvalidInput();
    }

//    if(value == nullptr){ //TODO UNCOMMENT
//        throw InvalidInput();
//    }

    if(findNode(root, key) != nullptr){
        throw NodeAlreadyExists();
    }
    AVLTree<Key,Value>* placement_pointer = root;
    AVLTree<Key,Value>* parent = root->parent;
    SonType son_type = SonType::root;
    while(placement_pointer != nullptr && placement_pointer->key != key){
        parent = placement_pointer;
        if(placement_pointer->key < key ){
            son_type = isRight;
            placement_pointer = placement_pointer->right;
        } else {
            son_type = isLeft;
            placement_pointer = placement_pointer->left;
        }
    }
    AVLTree<Key,Value>* n1 = init(key, value, son_type, parent);
    fixUpwardPath(n1, Insert);
    return getRoot(n1);
}


/* --------------------------------------------------------------------------------------------------------------------
 *                                                Remove Node
  --------------------------------------------------------------------------------------------------------------------*/

template<class Key,class Value>
void swapData(AVLTree<Key,Value>* A, AVLTree<Key, Value>* B){
    Key temp_key = A->key;
    Value temp_value = A->value;
    A->key = B->key;
    A->value = B->value;
    B->key = temp_key;
    B->value = temp_value;
}

template<class Key,class Value>
AVLTree<Key,Value>* getSmallestNodeBiggerThan(AVLTree<Key,Value>* node){
    AVLTree<Key,Value>* temp = node->right;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}

template<class Key, class Value>
AVLTree<Key,Value>* removeNode(AVLTree<Key,Value>* root, const Key& key){
    if(key <= 0 || root == nullptr){
        throw InvalidInput();
    }
    AVLTree<Key,Value>* to_remove = findNode(root,key);
    if(to_remove == nullptr){
        throw NodeDoesntExist();
    }
    // These nodes will store the node we will swap to_remove with,
    // and it's parent
    AVLTree<Key,Value>* new_parent = to_remove->parent;
    AVLTree<Key,Value>* swap_with = to_remove;
    AVLTree<Key,Value>* new_root;
    switch(DoesNodeHaveChildren(to_remove)){
        case HasTwoSons:{
            swap_with = getSmallestNodeBiggerThan(to_remove);
            swapData(to_remove, swap_with);
            removeNode(swap_with,swap_with->key);
            new_root = getRoot(to_remove);
            break;
        }
        case HasRightSon: {
            swap_with = to_remove->right;
            swapData(to_remove, swap_with);
            removeNode(swap_with,swap_with->key);
            new_root = getRoot(to_remove);
            break;
        }
        case HasLeftSon: {
            swap_with = to_remove->left;
            swapData(to_remove, swap_with);
            removeNode(swap_with,swap_with->key);
            new_root = getRoot(to_remove);
            break;
        }
        case Leaf:
            if (whichSonIsNode(to_remove) == isRight){
                new_parent->right = nullptr;
            } else if (whichSonIsNode(to_remove) == isLeft){
                new_parent->left = nullptr;
            }
            fixUpwardPath(to_remove, Delete);
            new_root = getRoot(to_remove);
            if(new_root==to_remove)
                new_root=nullptr;
            delete(to_remove);
            break; //TODO memory isn't being freed
    }
    return new_root;
}



/* --------------------------------------------------------------------------------------------------------------------
 *                                                Merge Trees
  --------------------------------------------------------------------------------------------------------------------*/



/*
 * Converts AVL tree to a sorted array
 * Assumes array is allocated
 */
template<class Key, class Value>
void arrayInOrder(AVLTree<Key,Value>* starting_point, int* index,
                  AVLTree<Key,Value>** arr, int arr_size){
    if(starting_point == nullptr || *index >= arr_size){
        return;
    }
    // Call left first
    arrayInOrder(starting_point->left, index, arr, arr_size);
    // Store root
    arr[*index] = starting_point;
    // Call right last with incremented index
    (*index)++;
    arrayInOrder(starting_point->right, index, arr, arr_size);
}

/*
 * Merges two sorted array into one
 * allocates it's own memory for the merged_array
 */
template<class Key,class Value>
AVLTree<Key, Value>** mergeTwoSortedArrays(AVLTree<Key, Value>** array_a,
                                           AVLTree<Key, Value>** array_b,
                                           int a_size, int b_size){

    AVLTree<Key, Value>** merged_array = new AVLTree<Key, Value>*[a_size+b_size];
    int a_index = 0;
    int b_index = 0;
    int merged_index = 0;
    while(a_index < a_size && b_index < b_size){
        if(array_a[a_index]->key < array_b[b_index]->key){
            merged_array[merged_index] = array_a[a_index];
            a_index++;
        }
        else{
            merged_array[merged_index] = array_b[b_index];
            b_index++;
        }
        merged_index++;
    }
    // if there's elements left in array_a
    while(a_index < a_size){
        merged_array[merged_index] = array_a[a_index];
        merged_index++;
        a_index++;
    }
    // if there's elements left in array_b
    while(b_index < b_size){
        merged_array[merged_index] = array_b[b_index];
        merged_index++;
        b_index++;
    }
    return merged_array;
}

/*
 * Converts a sorted array to an AVL tree
 * Allocates it's own memory for the tree
 */
template<class Key, class Value>
AVLTree<Key, Value>* convertArrayToAVL(AVLTree<Key, Value>** arr,
                                       int start_point,
                                       int end_point){
    // We take the middle element of the array and place it as root
    int root_index = (start_point + end_point) / 2;
    if (start_point > end_point || !arr[root_index]) {
        return nullptr;
    }
    AVLTree<Key,Value>* root = init<Key,Value>(arr[root_index]->key,
                                               arr[root_index]->value);
    // Use the lower-half of the array to build the left of root
    root->left = convertArrayToAVL(arr, start_point, root_index - 1);
    if(root->left != nullptr){
        root->left->parent = root;
    }
    // Use the upper-half of the array to build the right of root
    root->right = convertArrayToAVL(arr, root_index + 1, end_point);
    if(root->right != nullptr){
        root->right->parent = root;
    }

    return root;
}

template<class Key, class Value>
AVLTree<Key,Value>* mergeTrees(AVLTree<Key,Value>* tree_a, AVLTree<Key,Value>* tree_b,
                               int a_size, int b_size){
    // 1) convert two trees to sorted arrays
    AVLTree<Key, Value>** array_a = new AVLTree<Key, Value>*[a_size];
    AVLTree<Key, Value>** array_b = new AVLTree<Key, Value>*[b_size];
    int* a_index = new int(0);
    int* b_index = new int(0);
    arrayInOrder(tree_a, a_index, array_a, a_size);
    arrayInOrder(tree_b, b_index, array_b, b_size);
    delete a_index;
    delete b_index;
    AVLTree<Key, Value>** merged_array = mergeTwoSortedArrays(array_a, array_b, a_size, b_size);
    // mergeTwoSortedArrays Allocates memory for merged_array,
    // meaning we can free what we allocated above
    AVLTree<Key,Value>* result_AVL = convertArrayToAVL(merged_array, 0, a_size+b_size-1);
    delete[] array_a;
    delete[] array_b;
    delete [] merged_array;
    return result_AVL;
}


/* --------------------------------------------------------------------------------------------------------------------
 *                                                Quit.
  --------------------------------------------------------------------------------------------------------------------*/

template<class Key,class Value>
void Quit(AVLTree<Key,Value>* root){
    if(root == nullptr){
        return;
    }
    Quit(root->right);
    Quit(root->left);
    free(root);
}











