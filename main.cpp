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
    AVLTree<int,int>* root = insertNode(367, 1);


    for(int i = 0; i < 20 ; i++){
        int num = rand() % 1000 - 100;
        root = insertNode(num + i,1,root);

        std::cout << std::endl;

    }
    root = insertNode(1000,1,root);
    root = insertNode(1100,1,root);
    root = insertNode(1200,1,root);
    root = insertNode(1300,1,root);
    root = removeNode(root, 629);
    root = removeNode(root, 403);


    NEWLINE
    PrintTree(root);
    PrintTreeText(root);
    isAVL(root);

    return 0;


}

