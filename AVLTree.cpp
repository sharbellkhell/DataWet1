#include "AVLTree.h"
#include "Auxilaries.h"
#include <assert.h>
#include <iostream>


template<class Key, class Value>
AVLTree<Key,Value>::AVLTree(const Key &key, const Value &value, AVLTree* parent)
 : key(key) , value(value) , parent(parent) , left(nullptr) , right(nullptr), height(0) {}


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

template<class T> //TODO move function
T max(T a, T b){
    return (a>b ? a : b);
}

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


template<class Key, class Value>
int RecursiveCalcHeight(AVLTree<Key,Value>* node) {
    if(node == nullptr){
        return -1;
    }
    int rightHeight = RecursiveCalcHeight(node->right);
    int leftHeight = RecursiveCalcHeight(node->left);
    return (max<int>(rightHeight, leftHeight) + 1);
}

template<class Key, class Value>
int updateHeight(AVLTree<Key,Value>* node){
    if(node == nullptr) return -1;
    node->height = RecursiveCalcHeight(node);
    return (node->height);
}


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
    // TODO probably need to update heights
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
    // TODO probably need to update heights
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


template<class Key, class Value>
int getBF( AVLTree<Key,Value>* node){
    if(node == nullptr){
        return 0;
    } 
    return(updateHeight(node->left) - updateHeight(node->right) );

}

template<class Key, class Value>
AVLTree<Key,Value>* getRoot(AVLTree<Key,Value>* node){
    if(node->parent == nullptr){
        return node;
    }
    return (getRoot(node->parent));
}
#define WHATIS(this) std::cout << #this << ": " << this << std::endl;

template<class Key,class Value>
AVLTree<Key,Value>* insertNode(const Key& key, const Value& value, AVLTree<Key,Value>* root){
    if(root == nullptr){
        return init(key, value);
    }
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
    if(root == nullptr){
        return nullptr;
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
            free(to_remove);
            break; //TODO memory isn't being freed
    }
    return new_root;
}


template<class Key,class Value>
void Quit(AVLTree<Key,Value>* root){
    if(root == nullptr){
        return;
    }
    Quit(root->right);
    Quit(root->left);
    free(root);
}









