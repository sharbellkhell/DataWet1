#ifndef COMPANY_H_
#define COMPANY_H_
#include "AVLTree.h"
#include "Employee.h"


class Company{
    public:
        int companyId;
        AVLTree<int,Employee*>* workersId;
        AVLTree<int,Employee*>* workersSal;
        int value;
        bool empty;
        Employee* highest_earner;
        Company(int companyId, int value);
        ~Company() = default;
        void AddEmployee(Employee* employee);
        void RemoveEmployeeByID(int employee_id);
};

#endif