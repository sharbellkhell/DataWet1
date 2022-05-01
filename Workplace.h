#ifndef WORKPLACE_H
#define WORKPLACE_H
#include "AVLTree.h"
#include "Employee.h"
#include "Company.h"
typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
    } StatusType;



class Workplace{
    public:
        AVLTree<int, Company*> companies;
        AVLTree<int, Employee*> employeeID;
        AVLTree<int, Employee*> employeeSAL;
        AVLTree<int, Company*> nonEmptyCompanies;
        Workplace();
        ~Workplace();
};
        void *Init();

        StatusType AddCompany(void *DS, int CompanyID, int Value);

        StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade);

        StatusType RemoveCompany(void *DS, int CompanyID);

        StatusType RemoveEmployee(void *DS, int EmployeeID);

        StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees);

        StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade);

        StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease);

        StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade);

        StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID);

        StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor);

        StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID);

        StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees);

        StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees);

        StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

        void Quit(void** DS);


#endif