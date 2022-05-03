#ifndef COMPANY_H_
#define COMPANY_H_
#include "AVLTree.h"
#include "Employee.h"

typedef enum {
    SUCCESS = 0,
    ALREADY_EXIST=1,
    DOES_NOT_EXIST=2,
    INVALID_INPUT=3
} Result;

class Company{
    public:
        int companyId;
        AVLTree<int,Employee*>* workersId;
        AVLTree<int,Employee*>* workersSal;
        int value;
        bool empty;
        Employee* highest_earner;
        Company(int company_id,int value) : companyId(company_id),empty(true),value(value) {
        workersId = nullptr;
        workersSal = nullptr;
        highest_earner=nullptr;
        }
        ~Company() = default;
        void func();
        Result AddEmployee(Employee* emp);
        Result RemoveEmployeeByID(const int employee_id);
};

#endif