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
 ~AVLTree();

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

// Returns height
template<class Key, class Value>
int getHeight(AVLTree<Key,Value>*);

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
void deleteNode(AVLTree<Key,Value>*, const Key&);

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


#endif //AVLTREE_H
