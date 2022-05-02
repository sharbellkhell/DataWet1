#ifndef WORKPLACE_H
#define WORKPLACE_H
#include "AVLTree.h"
#include "Employee.h"
#include "Company.h"
#include "library1.h"


class Workplace{
    public:
        AVLTree<int, Company*>* companies;
        AVLTree<int, Employee*>* employeeID;
        AVLTree<int, Employee*>* employeeSAL;
        AVLTree<int, Company*>* nonEmptyCompanies;
        Workplace();
        ~Workplace();
};

#endif