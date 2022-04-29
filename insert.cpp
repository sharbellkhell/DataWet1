#include "AVLTree.h"

template<class Key,class Value>
AVLTree<Key, Value>* recursiveInsert(const Key& key,
                                     const Value& value,
                                     AVLTree<Key,Value>* root){



}

template<class Key,class Value>
AVLTree<Key, Value>* insert(const Key& key,
                            const Value& value,
                            AVLTree<Key,Value>* root){
    if(root == nullptr){
        return init(key, value);
    }
    if(findNode(root, key) != nullptr){
        throw NodeAlreadyExists();
    }
    return(recursiveInsert(key, value, root));
}

