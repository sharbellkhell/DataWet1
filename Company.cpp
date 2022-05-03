#include "Company.h"
#include "exceptions.h"
#include <iostream>


void Company::func(){
    std::cout<<"hello\n";
}
Result Company::AddEmployee(Employee* emp){
    try{
    this->workersId = insertNode(emp->EmployeeId, emp,this->workersId);
    this->workersSal=insertNode(emp->salary, emp,this->workersSal);
    }catch(InvalidInput){
        return INVALID_INPUT;
    }
    catch(NodeAlreadyExists){
        return ALREADY_EXIST;
    }
    if(this->highest_earner==nullptr)
    {
        highest_earner=emp;
    }
    else if(this->highest_earner->salary<=emp->salary)
    {
        if(this->highest_earner->salary==emp->salary)
        {
            if(this->highest_earner->EmployeeId>emp->EmployeeId)
                this->highest_earner=emp;
        }
        else
            this->highest_earner=emp;
    }
    this->empty = false;
    return SUCCESS;

}
static Employee* find_highest_earner(Company* company)
{
    AVLTree<int,Employee*>* temp=company->workersSal;
    while(temp->right!=nullptr)
        temp=temp->right;
    return temp->value;
}
Result Company::RemoveEmployeeByID(const int employee_id)
{
    AVLTree<int,Employee*>* employee = findNode(this->workersId,employee_id);
    if(employee == nullptr)
        return DOES_NOT_EXIST;
    int sal_to_remove=employee->value->salary;
    this->workersId=removeNode(this->workersId,employee_id);
    this->workersSal=removeNode(this->workersSal,sal_to_remove);
    if(this->highest_earner->EmployeeId==employee_id)
        this->highest_earner=find_highest_earner(this);
    return SUCCESS;
}



