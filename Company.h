#ifndef COMPANY_H_
#define COMPANY_H_
#include "AVLTree.h"
#include "Employee.h"

typedef enum {SUCCESS=0,EXISTS=1,DONT_EXIST=2,} Result;

class Company{
    public:
        int companyId;
        AVLTree<int,Employee*>* workersId;
        AVLTree<int,Employee*>* workersSal;
        int value;
        Company(int companyId, int value);
        ~Company() = default;
        Result AddEmp(Employee* emp);
        Result RemoveEmp(int id);
};
#endif