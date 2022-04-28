#include <iostream>
#include "AVLTree.h"
#include "AVLTree.cpp"
#define WHATIS(this) std::cout << #this << ": " << this << std::endl;




int main() {


    std::cout << "Hello, World!" << std::endl;
    AVLTree<int,int> n1(4,5);
    AVLTree<int,int> n2(1,4, &n1);
    n1.right = &n2;


    WHATIS(GetHeight(&n1))
    WHATIS(GetHeight(&n2))
    WHATIS(GetHeight(n2.right))
    WHATIS(n1.nodeChildren())





    return 0;


}

