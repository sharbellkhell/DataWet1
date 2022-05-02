#include "Company.h"
#include "exceptions.h"

Company::Company(int company_id,int value) : companyId(company_id),empty(true),value(value) {
    workersId = nullptr;
    workersSal = nullptr;
}

void Company::AddEmployee(Employee* emp){
    insertNode(emp->EmployeeId, emp,this->workersId);
    insertNode(emp->salary, emp,this->workersSal);
    this->empty = false;


}

void Company::RemoveEmployeeByID(int employee_id)
{
    AVLTree<int,Employee*>* employee = findNode(this->workersId,employee_id);
    if(employee == nullptr){
        throw NodeDoesntExist();
    }
    removeNode(this->workersId,employee_id);
    removeNode(this->workersSal,employee->value->salary);
    return SUCCESS;
}

