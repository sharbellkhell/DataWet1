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
static AVLTree<int,AVLTree<int,Employee*>*>* insertDuplicate(int sal,Employee* emp,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    if(temp==nullptr)
    {
        AVLTree<int, Employee*>* sal_Range=init(emp->EmployeeId,emp);
        root=insertNode(sal,sal_Range,root);
    }
    else{
        temp->value=insertNode(emp->EmployeeId,emp,temp->value);
    }
    return root;
}

static void removeDuplicate(int sal,int emp_id,AVLTree<int,AVLTree<int,Employee*>*>* root)
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
    this->employeeSAL=insertDuplicate(sal,emp,this->employeeSAL);
    }catch(NodeAlreadyExists)
    {
        return FAILURE;
    }
    StatusType res=temp->value->AddEmployee(emp);
    if(res==FAILURE)
        return FAILURE;
    AVLTree<int,Company*>* nonTemp=findNode(this->nonEmptyCompanies,comp_id);
    if(nonTemp==nullptr)
        this->nonEmptyCompanies=insertNode(comp_id,temp->value,this->nonEmptyCompanies);
    else
        nonTemp->value->AddEmployee(emp);
    this->employee_count++;
    return SUCCESS;
}

StatusType Workplace::RemoveEmployeeFromWorkplace(int emp_id)
{
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(temp==nullptr)
        return FAILURE;
    AVLTree<int,Company*>* comp=findNode(this->companies,temp->value->EmployerId);
    if(comp==nullptr)
        return FAILURE;
    Employee* to_remove=temp->value;
    removeDuplicate(to_remove->salary,to_remove->EmployeeId,this->employeeSAL);
    this->employeeID=removeNode(this->employeeID,emp_id);
    comp->value->RemoveEmployeeByID(emp_id);
    this->employee_count--;
    return SUCCESS;
}
        