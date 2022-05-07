#ifndef WORKPLACE_H_
#define WORKPLACE_H_
#include <iostream>
#include "AVLTree.h"
#include "Employee.h"
#include "Company.h"
#include "library1.h"


class Workplace{
    public:
        AVLTree<int, Company*>* companies;
        AVLTree<int, Employee*>* employeeID;
        AVLTree<int, AVLTree<int,Employee*>*>* employeeSAL;
        AVLTree<int, Company*>* nonEmptyCompanies;
        int non_empty_companies_count;
        int employee_count;
        Workplace();
        ~Workplace() = default;
        void QuitWorkplace();
        StatusType AddCompanyToWorkplace(int id,int val);
        StatusType AddEmployeeToWorkplace(int emp_id,int comp_id,int sal,int grade);
        StatusType RemoveEmployeeFromWorkplace(int emp_id);
        StatusType RemoveCompanyFromWorkplace(int id);
        StatusType GetCompanyInfoFromWorkplace(int id, int* val,int *employee_count);
        StatusType GetEmployeeInfo(int emp_id, int *employer_id, int *sal, int *grade);
        StatusType IncreaseCompanyValue(int comp_id, int value_increase);
        StatusType PromoteEmployee(int emp_id, int sal_increase, int bump);
        StatusType HireEmployee(int emp_id, int new_comp_id);
        StatusType AcquireCompany(int new_comp_id, int old_comp_id, double factor);
        StatusType GetHighestEarner(int comp_id, int* emp_id);
        StatusType GetAllEmployeesBySalary(int comp_id, int **emps, int* emp_count);
        StatusType GetHighestEarnerInEachCompany(int comp_count, int **emps);
        StatusType GetNumEmployeesMatching(int comp_id, int min_id, int max_id, int min_sal, int min_grade, int *total, int *count);

};

void releaseWorkers(AVLTree<int,Employee*>* root);
void removeCompanies(AVLTree<int,Company*>* root);
void releaseFromSal(AVLTree<int, AVLTree<int,Employee*>*>* root);
#endif