#include <iostream>
#include "AVLTree.cpp"
#include "Company.h"
#include "Employee.h"
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

void print_keys(AVLTree<int,Employee*>* comp)
{
    if(comp==nullptr)
        return;
    std::cout<<comp->key<<"\n";
    print_keys(comp->left);
    print_keys(comp->right);
}
int main() {

//
  /*  AVLTree<int,int>* root = insertNode(1, 1);
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

    AVLTree<int,int>* root2 = insertNode(14, 1);
    root2 = insertNode(5,1,root2);
    root2 = insertNode(1000,1,root2);
    root2 = insertNode(9,1,root2);
    root2 = insertNode(12,1,root2);
    root2 = insertNode(21,1,root2);
    root2 = insertNode(3,1,root2);
    //std::cout <<root->key<< "tesst";

    NEWLINE
    std::cout<<"first\n";
    PrintTree(root);
    std::cout<<"second\n";
    PrintTree(root2);
    
    /AVLTree<int,int>* merge=mergeTrees(root,root2,13,7);
    std::cout<<"merged\n";
    PrintTree(merge);
    //PrintTreeText(root);
    //isAVL(root);
    
    Quit(root);
*/
//    Company intel=Company(1,100);
//    Employee sam=Employee(300,1,10000,1);
//    Employee ben=Employee(305,1,11000,1);
//    Employee alex=Employee(350,1,10001,1);
//    Employee steve=Employee(320,1,12000,1);
//    intel.AddEmployee(&sam);
//    intel.AddEmployee(&ben);
//    intel.AddEmployee(&alex);
//    intel.AddEmployee(&steve);
//    std::cout<<intel.highest_earner->EmployeeId<<" is the highest earner with "<<intel.highest_earner->salary<<"\n";
//    int num1=0;
//    int num2=0;
//    int* v=&num1;
//    int* c=&num2;
//    intel.CompanyInfo(v,c);
//    intel.RemoveEmployeeByID(320);
//    std::cout<<*v<<" "<<*c;
//    int* ids=new int[intel.employee_count];
//    int** idss=&ids;
//    int count=0;
//    int* cc=&count;
//    intel.PrintEmployees();
//    highest_to_lowest(intel.workersId,idss,cc);
//    for(int i=0;i<intel.employee_count;i++)
//    {
//        std::cout<<ids[i]<<" ";
//    }
//    count=0;
//    lowest_to_highest(intel.workersId,idss,cc);
//    for(int i=0;i<intel.employee_count;i++)
//    {
//        std::cout<<ids[i]<<" ";
//    }
//    delete[] ids;
//    return 0;

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

    AVLTree<int,int>* root2 = insertNode(14, 1);
    root2 = insertNode(5,1,root2);
    root2 = insertNode(1000,1,root2);
    root2 = insertNode(9,1,root2);
    root2 = insertNode(12,1,root2);
    root2 = insertNode(21,1,root2);
    root2 = insertNode(3,1,root2);
    //std::cout <<root->key<< "tesst";

    NEWLINE
    std::cout<<"first\n";
    PrintTree(root);
    std::cout<<"secondd\n";
    PrintTree(root2);
    AVLTree<int,int>* merge=mergeTrees(root, root2, 13, 7);
    std::cout<<"merged\n";
    PrintTree(merge);
}

