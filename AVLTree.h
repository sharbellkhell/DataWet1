#ifndef AVLTREE_H
#define AVLTREE_H
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
     //delete(key); //TODO DTOR
     //delete(value);
 }
    AVLTree(const Key &key,
            const Value &value,
            AVLTree* parent = nullptr);


};

enum SonType {isLeft, isRight, root};
template<class Key,class Value>
AVLTree<Key,Value>* init(const Key &key,
              const Value &value,
              SonType son_type = root,
              AVLTree<Key,Value>* parent = nullptr);

enum NodeChildren {Leaf, HasLeftSon, HasRightSon, HasTwoSons};
template<class Key,class Value>
NodeChildren DoesNodeHaveChildren(AVLTree<Key,Value>*);

template<class Key,class Value>
SonType whichSonIsNode(AVLTree<Key,Value>*);

template<class Key,class Value>
int RecursiveCalcHeight(AVLTree<Key,Value>*);

template<class Key,class Value>
int updateHeight(AVLTree<Key,Value>*);

template<class Key,class Value>
AVLTree<Key,Value>* rotateRight(AVLTree<Key,Value>*);

template<class Key,class Value>
AVLTree<Key,Value>* rotateLeft(AVLTree<Key,Value>*);

template<class Key,class Value>
AVLTree<Key,Value>* findNode(AVLTree<Key,Value>*, const Key&);

template<class Key, class Value>
int getBF( AVLTree<Key,Value>* );


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


enum Function {Delete, Insert};
template<class Key,class Value>
void fixUpwardPath(AVLTree<Key,Value>* , Function);


template<class Key, class Value>
void arrayInOrder(AVLTree<Key,Value>* starting_point, int* index,
                  AVLTree<Key,Value>** arr);

template<class Key,class Value>
AVLTree<Key, Value>** mergeTwoSortedArrays(AVLTree<Key, Value>** array_a,
                                           AVLTree<Key, Value>** array_b,
                                           int a_size, int b_size);

template<class Key, class Value>
AVLTree<Key, Value>* convertArrayToAVL(AVLTree<Key, Value>** arr,
                                       int start_point,
                                       int end_point);

template<class Key, class Value>
AVLTree<Key,Value>* mergeTrees(AVLTree<Key,Value>*, AVLTree<Key,Value>*);

template<class Key,class Value>
void highest_to_lowest(AVLTree<Key,Value*>* root, Key** keys,int* total_keys);

template<class Key,class Value>
void lowest_to_highest(AVLTree<Key,Value*>* root, Key** keys,int* total_keys);

template<class Key,class Value>
void Quit(AVLTree<Key,Value>* root);


#endif //AVLTREE_H
