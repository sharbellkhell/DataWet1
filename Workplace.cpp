#include "Workplace.h"
#include "AVLTree.h"
#include "Company.h"
#include <ostream>

Workplace::Workplace():employee_count(0){
    companies=nullptr;
    employeeID=nullptr;
    employeeSAL=nullptr;
    nonEmptyCompanies=nullptr;
}

StatusType Workplace::AddCompanyToWorkplace(int id,int val)
{
    Company* cmp =new Company(id,val);
    if(cmp==NULL)
        return ALLOCATION_ERROR;
    try{
    this->companies=insertNode(id, cmp,this->companies);
    }catch(NodeAlreadyExists)
    {
        return FAILURE;
    }
    return SUCCESS;
}
static void insertDuplicateNode(int sal,Employee* emp,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    if(temp==nullptr)
    {
        AVLTree<int, Employee*>* sal_Range=insertNode(emp->EmployeeId,emp,sal_Range);
        root=insertNode(sal,sal_Range,root);
    }
    else{
        temp->value=insertNode(emp->EmployeeId,emp,temp->value);
    }
}

static void removeDuplicateNode(int sal,int emp_id,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    temp->value=removeNode(temp->value,emp_id);
}

StatusType Workplace::AddEmployeeToWorkplace(int emp_id,int comp_id,int sal,int grade)
{
    Employee* emp=new Employee(emp_id,comp_id,sal,grade);
    AVLTree<int, Company*>* temp=findNode(this->companies,comp_id);
    if(temp==nullptr)
        return INVALID_INPUT;
    if(emp==NULL)
        return ALLOCATION_ERROR;
    try{
    this->employeeID=insertNode(emp_id,emp,this->employeeID);
    insertDuplicateNode(sal,emp,this->employeeSAL);
    }catch(NodeAlreadyExists)
    {
        return FAILURE;
    }
    Result res=temp->value->AddEmployee(emp);
    if(res==ALREADY_EXIST)
        return FAILURE;
    this->nonEmptyCompanies=insertNode(comp_id,temp->value,this->nonEmptyCompanies);
    return SUCCESS;
}

StatusType Workplace::RemoveEmployeeFromWorkplace(int emp_id)
{
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(temp==nullptr)
        return FAILURE;
    Employee* to_remove=temp->value;
    removeDuplicateNode(to_remove->salary,to_remove->EmployeeId,this->employeeSAL);
    AVLTree<int,Company*>* comp=findNode(this->companies,temp->value->EmployerId);

}
        