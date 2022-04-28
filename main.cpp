#include <iostream>
#include "AVLTree.h"
#include "AVLTree.cpp"
#include <string>
#define WHATIS(this) std::cout << #this << ": " << this << std::endl;
#define NEWLINE std::cout << std::endl;



// Print the tree TODO DELETE CODE LATER
void printTreeInternal(AVLTree<int,int>* root, std::string indent, bool last) {
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->key << std::endl;
        printTreeInternal(root->left, indent, false);
        printTreeInternal(root->right, indent, true);
    }
}

void PrintTree(AVLTree<int,int>* root){
    printTreeInternal(root, "", true);
}


int main() {


    std::cout << "Hello, World!" << std::endl;
    AVLTree<int,int>* n1 = init(1,5);
    AVLTree<int,int>* n2 = init(2,4, isLeft,n1);
    AVLTree<int,int>* n3 = init(3,2, isRight,n1);

//    WHATIS(getHeight(n1))
//    WHATIS(getHeight(n2))
//    WHATIS(getHeight(n2->right))
//    WHATIS(DoesNodeHaveChildren(n1))

    PrintTree(n1);
    WHATIS(findNode(n1, 3)->key)

    AVLTree<int,int>* root = insertNode(1, 5);
    insertNode(2,3,root);
    insertNode(3,5,root);
    NEWLINE
    PrintTree(root);
    WHATIS(findNode(root, 3)->key)











    return 0;


}

