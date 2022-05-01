#include "AVLTree.h"
#include <iostream>
#define WHATIS(this) std::cout << #this << ": " << this << std::endl;


template<class Key, class Value>
AVLTree<Key,Value>* recursiveRemove(AVLTree<Key,Value>* root, const Key& key){
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
    switch(DoesNodeHaveChildren(to_remove)){
        case HasTwoSons:{
            swap_with = getSmallestNodeBiggerThan(to_remove);
            swapData(to_remove, swap_with);
            recursiveRemove(swap_with,swap_with->key);
            break;
        }
        case HasRightSon: {
            swap_with = to_remove->right;
            to_remove->parent->right = swap_with;
            swap_with->parent = new_parent;
            break;
        }
        case HasLeftSon: {
            swap_with = to_remove->left;
            to_remove->parent->left = swap_with;
            swap_with->parent = new_parent;
            break;
        }
        case Leaf:
            if (whichSonIsNode(to_remove) == isRight){
                new_parent->right = nullptr;
            } else if (whichSonIsNode(to_remove) == isLeft){
                new_parent->left = nullptr;
            }
            break;
    }
    fixUpwardPath(to_remove, Delete);
    return getRoot(to_remove);
}