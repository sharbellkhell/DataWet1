#include "Workplace.h"
#include "AVLTree.h"
#include <ostream>

Workplace::Workplace(){
    this->companies=AVLTree::init(1,nullptr);
}