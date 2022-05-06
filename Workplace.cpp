#include "Workplace.h"
#include "AVLTree.h"
#include "Company.h"
#include <cmath>
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

static AVLTree<int,AVLTree<int,Employee*>*>* removeDuplicate(int sal,int emp_id,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    temp->value=removeNode(temp->value,emp_id);
    if(temp->value==nullptr)
        root=removeNode(root,sal);
    return root;
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
    this->employeeSAL=removeDuplicate(to_remove->salary,to_remove->EmployeeId,this->employeeSAL);
    this->employeeID=removeNode(this->employeeID,emp_id);
    comp->value->RemoveEmployeeByID(emp_id);
    this->employee_count--;
    if(comp->value->employee_count==0)
    {
        this->nonEmptyCompanies=removeNode(this->nonEmptyCompanies,comp->value->companyId);
    }
    return SUCCESS;
}

StatusType Workplace::RemoveCompanyFromWorkplace(int id){
    AVLTree<int,Company*>* comp=findNode(this->companies,id);
    if(comp->value->employee_count!=0)
        return FAILURE;
    this->companies=removeNode(this->companies,id);
    return SUCCESS;
}

StatusType Workplace::GetCompanyInfoFromWorkplace(int id, int* val,int *employee_count)
{
    AVLTree<int,Company*>* comp=findNode(this->companies,id);
    if(comp==nullptr)
        return FAILURE;
    *val=comp->value->value;
    *employee_count=comp->value->employee_count;
    return SUCCESS;
}


StatusType Workplace::GetEmployeeInfo(int emp_id, int *employer_id, int *sal, int *grade)
{
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(temp==nullptr)
        return FAILURE;
    *employer_id=temp->value->EmployerId;
    *sal=temp->value->salary;
    *grade=temp->value->grade;
    return SUCCESS;
}

StatusType Workplace::IncreaseCompanyValue(int comp_id, int value_increase)
{
    AVLTree<int,Company*>* comp=findNode(this->companies,comp_id);
    if(comp==nullptr)
        return FAILURE;
    comp->value->setValue(value_increase+comp->value->value);
    return SUCCESS;
}


StatusType Workplace::PromoteEmployee(int emp_id, int sal_increase, int bump)
{
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(temp==nullptr)
        return FAILURE;
    temp->value->Promote(sal_increase,bump);
    return SUCCESS;
}

StatusType Workplace::HireEmployee(int emp_id, int new_comp_id)
{
    AVLTree<int,Company*>* comp=findNode(this->companies,new_comp_id);
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(comp==nullptr || temp==nullptr)
        return FAILURE;
    AVLTree<int,Company*>* old_comp=findNode(this->nonEmptyCompanies,temp->value->EmployerId);
    old_comp->value->RemoveEmployeeByID(emp_id);
    comp->value->AddEmployee(temp->value);
    temp->value->EmployerId=new_comp_id;
    return SUCCESS;
}


StatusType Workplace::AcquireCompany(int new_comp_id, int old_comp_id, double factor)
{
    AVLTree<int,Company*>* new_comp=findNode(this->companies,new_comp_id);
    AVLTree<int,Company*>* old_comp=findNode(this->companies,old_comp_id);
    if(new_comp==nullptr || old_comp==nullptr || new_comp->value->value<10*old_comp->value->value)
        return FAILURE;
    new_comp->value->workersId=mergeTrees(new_comp->value->workersId,old_comp->value->workersId,new_comp->value->employee_count,old_comp->value->employee_count);
    //replaces new_companies employees with old_company, basically dosent work
    new_comp->value->setValue(floor((new_comp->value->value+old_comp->value->value)*factor));
    this->RemoveCompanyFromWorkplace(old_comp_id);
    return SUCCESS;

}