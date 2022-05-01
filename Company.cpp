#include "Company.h"
#include "exceptions.h"

Company::Company(int id,int value):companyId(id),empty(true),value(value){
    workersId=nullptr;
    workersSal=nullptr;
}

Result Company::AddEmp(Employee* emp){
    try
    {
    insertNode(emp->EmployeeId, emp,this->workersId);
    insertNode(emp->salary, emp,this->workersSal);
    this->empty=true;
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
    removeNode(this->workersId,id);
    removeNode(this->workersSal,sal);
    return SUCCESS;
}

Employee* highestEarner(Company* company)
{
    AVLTree<int,Employee*>* temp=company->workersSal;
    while(temp->right!=nullptr)
        temp=temp->right;
    return temp->value;
}