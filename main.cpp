#include <iostream>
#include "AVLTree.h"
#include "AVLTree.cpp"
#include <string>
#define WHATIS(this) std::cout << #this << ": " << this << std::endl;
#define NEWLINE std::cout << std::endl;
#include <random>



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

void isAVL(AVLTree<int,int>* root){
    if(!root){
        return;
    }
    WHATIS(root->key);
    WHATIS(getBF(root));
    isAVL(root->right);
    isAVL(root->left);
}

bool validCheck(AVLTree<int,int>* root){
    if(!root)
        return false;
    if(root->right){
        if(root->right->parent != root){
            std::cout << "SCREAMMM AHHHHHHH" << std::endl;
            return true;
            WHATIS(root->right->key)
            WHATIS(root->key)
        }
    }
    if(root->left){
        if(root->left->parent != root){
            std::cout << "SCREAMMM AHHHHHHH" << std::endl;
            return true;
            WHATIS(root->left->key)
            WHATIS(root->key)
        }
    }
    if( validCheck(root->right) || validCheck(root->left) ){
        return true;
    } else
        return false;

}


void PrintTree(AVLTree<int,int>* root){
    printTreeInternal(root, "", true);
}

void PrintTreeText(AVLTree<int,int>* root){
    if(!root){
        return;
    }
    std::cout << "parent: " << root->key;
    if (!root->left && !root->right){
        std::cout << std::endl;
        return;}
    if(root->left) {
        std::cout << " left son : " << root->left->key;
    }
    if(root->right) {
        std::cout << " right son : " << root->right->key;
    }
    std::cout << std::endl;
    PrintTreeText(root->left);
    PrintTreeText(root->right);
}


int main() {

//
    AVLTree<int,int>* root = insertNode(1, 1);
    root = insertNode(50,1,root);
    root = insertNode(100,1,root);
    root = insertNode(99,1,root);
    root = insertNode(102,1,root);
    root = insertNode(2,1,root);
    root = insertNode(103,1,root);
    root = insertNode(104,1,root);
    root = insertNode(11,1,root);
    root = insertNode(105,1,root);
    root = insertNode(106,1,root);
    root = insertNode(107,1,root);
    root = insertNode(7,1,root);
    root = insertNode(108,1,root);
    root = insertNode(109,1,root);
    root = insertNode(110,1,root);
    root = insertNode(10,1,root);
    root= removeNode(root,103);
    root= removeNode(root,2);
    root= removeNode(root,104);
    //std::cout <<root->key<< "tesst";

    NEWLINE
    PrintTree(root);
    PrintTreeText(root);
    isAVL(root);
    
    Quit(root);

    return 0;


}

