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


    AVLTree<int,int>* root = insertNode(367, 1);
    root = insertNode(235,1,root);
    root = insertNode(402,1,root);
    root = insertNode(72,1,root);
    root = insertNode(628,1,root);
    root = insertNode(383,1,root);
    root = insertNode(264,1,root);
    root = insertNode(869,1,root);
    root = insertNode(372,1,root);
    root = insertNode(614,1,root);
    root = insertNode(55,1,root);
    root = insertNode(192,1,root);
    root = insertNode(739,1,root);
    root = insertNode(874,1,root);
    root = insertNode(405,1,root);
    root = insertNode(910,1,root);
    root = insertNode(858,1,root);
    root = insertNode(744,1,root);
    root = insertNode(354,1,root);
    root = insertNode(310,1,root);

    NEWLINE
    PrintTree(root);
    //WHATIS(findNode(root, 3)->key)











    return 0;


}

