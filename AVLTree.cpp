#include "AVLTree.h"
#include "Auxilaries.h"


    template<class Key, class Value>
    AVLTree<Key,Value>::AVLTree(const Key &key, const Value &value, AVLTree* parent)
     : key(key) , value(value) , parent(parent) , left(nullptr) , right(nullptr), height(0) {}

    template<class T> //TODO move function
    T max(T a, T b){
        return (a>b ? a : b);
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
    int GetHeight(AVLTree<Key,Value>* node){
        if(node == nullptr) return -1;
        node->height = RecursiveCalcHeight(node);
        return (node->height);
    }

    template<class Key, class Value>
    typename AVLTree<Key,Value>::NodeChildren AVLTree<Key,Value>::nodeChildren() const{
        if(right == nullptr && left == nullptr){
            return Leaf;
        }
        if(right != nullptr && left == nullptr){
            return HasRightSon;
        }
        if(right == nullptr && left != nullptr){
            return HasLeftSon;
        }
        return HasTwoSons;
    }







