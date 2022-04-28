#include "AVLTree.h"
#include "Auxilaries.h"
#include <assert.h>


template<class Key, class Value>
AVLTree<Key,Value>::AVLTree(const Key &key, const Value &value, AVLTree* parent)
 : key(key) , value(value) , parent(parent) , left(nullptr) , right(nullptr), height(0), num_of_nodes(0) {}

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
    n1->num_of_nodes++; //TODO This functionality could be unnecessary
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
int getHeight(AVLTree<Key,Value>* node){
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
    assert(B); // TODO if reached assert, we are performing illegal rotation
    AVLTree<Key,Value>* Bl = B->left;
    B->left = A;
    A->right = Bl;

    //relink with outside tree
    B->parent = absolute_parent;
    switch(absolute_son_type){
        case isLeft:
            absolute_parent->left = B;
            break;
        case isRight:
            absolute_parent->right = B;
            break;
        case root:
            break;
    }
    return B;

    // TODO probably need to update heights
}


template<class Key,class Value>
AVLTree<Key,Value>* rotateRight(AVLTree<Key,Value>* B){
AVLTree<Key,Value>* absolute_parent = B->parent;
SonType absolute_son_type = whichSonIsNode(B);

AVLTree<Key,Value>* A = B->left;
assert(A); // TODO if reached assert, we are performing illegal rotation
AVLTree<Key,Value>* Ar = A->right;
//Ar = (A != nullptr ? A->right : nullptr);
A->right = B;
B->left = Ar;
// TODO probably need to update heights
A->parent = absolute_parent;
switch(absolute_son_type){
    case isLeft:
        absolute_parent->left = A;
    case isRight:
        absolute_parent->right = A;
    case root: ;
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
    return(node->left->height - node->right->height );
}

template<class Key,class Value>
AVLTree<Key,Value>* insertNode(const Key& key, const Value& value, AVLTree<Key,Value>* root){
    if(root == nullptr){
        return init(key, value);
    }
    if(findNode(root, key) != nullptr){
        throw NodeAlreadyExists();
    }
    AVLTree<Key,Value>* placement_pointer = root;
    AVLTree<Key,Value>* parent = nullptr;
    SonType son_type = SonType::root;
    while(placement_pointer != nullptr && placement_pointer->key != key){
        parent = placement_pointer->parent;
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
    root->num_of_nodes++;
    return(n1);
}

template<class KeyType, class ValueType>
void fixUpwardPathHeights(AVLTree<KeyType,ValueType>* node){
    AVLTree<KeyType,ValueType>* temp_node = node;
    while(temp_node != nullptr){
        getHeight(temp_node);
        temp_node = temp_node->parent;
    }
}

template<class Key, class Value>
void fixUpwardPath(AVLTree<Key,Value>* node, Function function) {
    fixUpwardPathHeights(node);

    while(node != nullptr ) {
        if (getBF(node) == 2) {
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
        } else if (getBF(node) == -2) {
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









