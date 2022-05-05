#ifndef COMPANY_H_
#define COMPANY_H_
#include "Employee.h"
#include "AVLTree.h"

typedef enum {
    SUCCESS = 0,
    ALREADY_EXIST=1,
    DOES_NOT_EXIST=2,
    INVALID_INPUT=3,
    ALLOCATION_ERROR
} Result;

class Company{
    public:
        int companyId;
        AVLTree<int,Employee*>* workersId;
        AVLTree<int,AVLTree<int,Employee*>*>* workersSal;
        int value;
        int employee_count;
        Employee* highest_earner;
        Company(int company_id,int value);
        ~Company() = default;
        Result AddEmployee(Employee* emp);
        Result RemoveEmployeeByID(const int employee_id);
        void CompanyInfo(int* value,int* num_of_employee);
        void setValue(const int value);
        void PrintEmployees()const;
};

#endif