#ifndef AVLTREE_H
#define AVLTREE_H



    template<class Key, class Value>
    class AVLTree {
    public:
        Key key;
        Value value;
        AVLTree* parent;
        AVLTree* left;
        AVLTree* right;
        int height;

        AVLTree(const Key &key,
                const Value &value,
                AVLTree* parent = nullptr);

        virtual ~AVLTree() = default; //TODO is default Dtor enough?

        enum NodeChildren {Leaf, HasLeftSon, HasRightSon, HasTwoSons};
        // Returns how many and what type of son the tree has
        NodeChildren nodeChildren() const;

    private:



    };

    // Recursive function used to make internal calculations for UpdateHeight()
    template<class Key,class Value>
    int RecursiveCalcHeight(AVLTree<Key,Value>*);

    // Updates Height of Tree and returns it
    template<class Key,class Value>
    int GetHeight(AVLTree<Key,Value>*);



#endif //AVLTREE_H
