#include "Company.h"
#include "exceptions.h"

Company::Company(int id,int value):companyId(id),workersId(NULL,NULL),workersSal(NULL,NULL),value(value){}

Result Company::AddEmp(Employee* emp){
    try
    {
    insertNode(emp->EmployeeId, emp,this->workersId);
    insertNode(emp->salary, emp,this->workersSal);
    }catch(NodeAlreadyExists()){
        return EXISTS;
    }
    return SUCCESS;
}

Result Company::RemoveEmp(int id)
{
    AVLTree<int,Employee*>* temp=findNode(this->workersId,id);
    if(temp==nullptr)
        return DONT_EXIST;
    int sal=temp->value->salary;
    deleteNode(this->workersId,id);
    deleteNode(this->workersSal,sal);
    return SUCCESS;
}

