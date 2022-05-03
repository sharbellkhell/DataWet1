#include "Workplace.h"
#include "AVLTree.h"
#include "Company.h"
#include <ostream>

Workplace::Workplace():companies(){
    this->companies=new AVLTree<int, Company*>(1,nullptr);

}