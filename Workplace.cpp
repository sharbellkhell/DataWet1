#include <iostream>
#include "Workplace.h"
#include "AVLTree.h"
#include "Company.h"
#include <cmath>


Workplace::Workplace(){
    employee_count=0;
    non_empty_companies_count=0;
    companies=nullptr;
    employeeID=nullptr;
    employeeSAL=nullptr;
    nonEmptyCompanies=nullptr;
}

StatusType Workplace::AddCompanyToWorkplace(int id,int val)
{
    if(id <= 0 || val <= 0){
        return INVALID_INPUT;
    }
    Company* cmp;
    try{
        cmp = new Company(id,val);
    }
    catch (std::bad_alloc const&){
        return ALLOCATION_ERROR;
    }
    try{
        this->companies=insertNode(id, cmp,this->companies);
    }
    catch(NodeAlreadyExists const&){
        delete cmp;
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
    temp->value = removeNode(temp->value,emp_id);
    if(temp->value==nullptr){
        root=removeNode(root,sal);
    }
    return root;
}

StatusType Workplace::AddEmployeeToWorkplace(int emp_id,int comp_id,int sal,int grade)
{
    if( emp_id <= 0 || comp_id <= 0 || sal <= 0 || grade < 0){
        return INVALID_INPUT;
    }
    Employee* emp;
    try{
        emp = new Employee(emp_id,comp_id,sal,grade);
    }
    catch (std::bad_alloc const&){
        return ALLOCATION_ERROR;
    }
    AVLTree<int, Company*>* temp=findNode(this->companies,comp_id);
    if(temp==nullptr){
        delete emp;
        return FAILURE; //Company Already Exists
    }
    try{
        this->employeeID=insertNode(emp_id,emp,this->employeeID);
        this->employeeSAL=insertDuplicate(sal,emp,this->employeeSAL);
    }
    catch(NodeAlreadyExists const&){
        delete emp;
        return FAILURE; //Employee Already Exists
    }
    StatusType res=temp->value->AddEmployee(emp);
    if(res != SUCCESS){
        delete emp;
        return res;
    }
    AVLTree<int,Company*>* nonTemp=findNode(this->nonEmptyCompanies,comp_id);
    if(nonTemp==nullptr){
        this->nonEmptyCompanies=insertNode(comp_id,temp->value,this->nonEmptyCompanies);
        this->non_empty_companies_count++;
    }
    else
        nonTemp->value->AddEmployee(emp);
    this->employee_count++;
    return SUCCESS;
}

StatusType Workplace::RemoveEmployeeFromWorkplace(int emp_id)
{
    if(emp_id <= 0){
        return INVALID_INPUT;
    }
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
        this->non_empty_companies_count--;
    }
    return SUCCESS;
}

static void updateWorkers(AVLTree<int,Employee*>* root, int id)
{
    if(root==nullptr)
        return;
    root->value->EmployerId=id;
    updateWorkers(root->right,id);
    updateWorkers(root->left,id);
}
StatusType Workplace::RemoveCompanyFromWorkplace(int id){
    if(id  <= 0){
        return INVALID_INPUT;
    }
    AVLTree<int,Company*>* comp=findNode(this->companies,id);
    if(comp == nullptr){
        return FAILURE;
    }
    if(comp->value->employee_count!=0)
        return FAILURE;
    this->companies=removeNode(this->companies,id);
    delete comp->value;
    return SUCCESS;
}

StatusType Workplace::GetCompanyInfoFromWorkplace(int id, int* val,int *employee_count)
{
    if(id <= 0 || val == nullptr || employee_count == nullptr){
        return INVALID_INPUT;
    }
    AVLTree<int,Company*>* comp=findNode(this->companies,id);
    if(comp==nullptr)
        return FAILURE;
    *val=comp->value->value;
    *employee_count=comp->value->employee_count;
    return SUCCESS;
}


StatusType Workplace::GetEmployeeInfo(int emp_id, int *employer_id, int *sal, int *grade)
{
    if(emp_id <= 0 || employer_id == nullptr || sal == nullptr || grade == nullptr){
        return INVALID_INPUT;
    }
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
    if(comp_id <= 0 || value_increase <= 0){
        return INVALID_INPUT;
    }
    AVLTree<int,Company*>* comp=findNode(this->companies,comp_id);
    if(comp==nullptr)
        return FAILURE;
    comp->value->setValue(value_increase+comp->value->value);
    return SUCCESS;
}


StatusType Workplace::PromoteEmployee(int emp_id, int sal_increase, int bump)
{
    if(emp_id <= 0 || sal_increase <= 0){
        return INVALID_INPUT;
    }
    AVLTree<int,Employee*>* temp=findNode(this->employeeID,emp_id);
    if(temp==nullptr)
        return FAILURE;
    temp->value->Promote(sal_increase,bump);
    return SUCCESS;
}

StatusType Workplace::HireEmployee(int emp_id, int new_comp_id)
{
    if(emp_id <= 0 || new_comp_id <= 0){
        return INVALID_INPUT;
    }
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
{//unfinished
    if(new_comp_id <= 0 || old_comp_id <= 0 || factor < 1.00 || new_comp_id == old_comp_id){
        return INVALID_INPUT;
    }
    AVLTree<int,Company*>* new_comp=findNode(this->companies,new_comp_id);
    AVLTree<int,Company*>* old_comp=findNode(this->companies,old_comp_id);
    if(new_comp==nullptr || old_comp==nullptr || new_comp->value->value<10*old_comp->value->value)
        return FAILURE;
    new_comp->value->workersId=mergeTrees(new_comp->value->workersId,old_comp->value->workersId,new_comp->value->employee_count,old_comp->value->employee_count);
    //replaces new_companies employees with old_company, basically dosent work //TODO
    new_comp->value->setValue(floor((new_comp->value->value+old_comp->value->value)*factor));
    old_comp->value->employee_count=0;
    updateWorkers(old_comp->value->workersId,new_comp_id);
    this->RemoveCompanyFromWorkplace(old_comp_id);
    return SUCCESS;

}

StatusType Workplace::GetHighestEarner(int comp_id, int* emp_id)
{
    if(comp_id == 0 || emp_id == NULL){
        return INVALID_INPUT;
    }
    if(comp_id>0)
    {
        AVLTree<int,Company*>* comp=findNode(this->companies,comp_id);
        if(comp==nullptr)
            return FAILURE;
        *emp_id=comp->value->highest_earner->EmployeeId;
        return SUCCESS;
    }
    if(comp_id<0)
    {
        AVLTree<int, AVLTree<int,Employee*>*>* sals=this->employeeSAL;
        if(sals==nullptr)
            return FAILURE;
        while(sals->right!=nullptr)
            sals=sals->right;
        AVLTree<int,Employee*>* emps=sals->value;
        while(emps->left!=nullptr)
            emps=emps->left;
        *emp_id=emps->value->EmployeeId;
        return SUCCESS;
    }
    return FAILURE;
}

static void inInsert(AVLTree<int, AVLTree<int,Employee*>*>* sals,int** emps,int* count)
{
    if(sals==nullptr)
        return;
    inInsert(sals->right,emps,count);
    AVLTree<int,Employee*>* temp = sals->value;
    lowest_to_highest(temp,emps,count);
    inInsert(sals->left,emps,count);
}

StatusType Workplace::GetAllEmployeesBySalary(int comp_id, int **emps, int* emp_count)
{
    if(comp_id == 0 || emps == NULL || emp_count == NULL){
        return INVALID_INPUT;
    }
    if(comp_id>0)
    {
        AVLTree<int,Company*>* comp=findNode(this->companies,comp_id);
        if(comp==nullptr)
            return FAILURE;
        int* emp=new int[comp->value->employee_count];
        if(emp==NULL)
            return ALLOCATION_ERROR;
        int count=0;
        int* p=&count;
        AVLTree<int, AVLTree<int,Employee*>*>* sals=comp->value->workersSal;
        inInsert(sals,emps,p);
        *emp_count=comp->value->employee_count;
        return SUCCESS;
    }
    if(comp_id<0)
    {
        int* emp=new int[this->employee_count];
        if(emp==NULL)
            return ALLOCATION_ERROR;
        int count=0;
        int* p=&count;
        AVLTree<int, AVLTree<int,Employee*>*>* sals=this->employeeSAL;
        inInsert(sals,emps,p);
        *emp_count=this->employee_count;
        return SUCCESS;
    }
    return FAILURE;
}

StatusType Workplace::GetHighestEarnerInEachCompany(int comp_count, int **emps)
{
    if(comp_count < 1 || emps == NULL){
        return INVALID_INPUT;
    }
    if(this->non_empty_companies_count<comp_count)
        return FAILURE;
    int* comps=new int[this->non_empty_companies_count];
    int c=0;
    int* p=&c;
    lowest_to_highest(this->nonEmptyCompanies,&comps,p);
    (*emps)=(int*) malloc(sizeof(int)*comp_count);
    for(int i=0;i<comp_count;i++)
    {
       // AVLTree<int,Company*>* temp=findNode(this->nonEmptyCompanies,comps[i]);
        //(*emps)[i]=temp->value->highest_earner->EmployeeId;
        int temp=0;
        p=&temp;
        this->GetHighestEarner(comps[i],p);
        (*emps)[i]=temp;
    }
    delete[] comps;
    return SUCCESS;
}

static void countCondition(AVLTree<int,Employee*>* root,int min_id, int max_id, int min_sal, int min_grade, int *total, int *count)
{
    if(root==nullptr)
        return;
    int id=root->value->EmployeeId;
    if(id>=min_id && id<=max_id)
    {
        *total=*total+1;
        int salary=root->value->salary;
        int grade=root->value->grade;
        if(salary>=min_sal && grade>=min_grade)
            *count=*count+1;
    }
    countCondition(root->right,min_id,max_id,min_sal,min_grade,total,count);
    countCondition(root->left,min_id,max_id,min_sal,min_grade,total,count);
}
StatusType Workplace::GetNumEmployeesMatching(int comp_id, int min_id, int max_id, int min_sal, int min_grade,
                                              int *total, int *count)
{
    if(comp_id == 0 || min_id < 0 || max_id  < 0 || min_sal < 0 || min_grade < 0 || min_id > max_id){
        return INVALID_INPUT;
    }
    if(comp_id>0)
    {
        AVLTree<int,Company*>* temp=findNode(this->nonEmptyCompanies,comp_id);
        if(temp==nullptr)
            return FAILURE;
        countCondition(temp->value->workersId,min_id,max_id,min_sal,min_grade,total,count);
        return SUCCESS;
    }
    if(comp_id<0)
    {
        if(this->employee_count==0)
            return FAILURE;
        countCondition(this->employeeID,min_id,max_id,min_sal,min_grade,total,count);
        return SUCCESS;
    }
    return FAILURE;
}

void releaseFromSal(AVLTree<int, AVLTree<int,Employee*>*>* root)
{
    if(root==nullptr)
        return;
    Quit(root->value);
    releaseFromSal(root->right);
    releaseFromSal(root->left);
    
}
void releaseWorkers(AVLTree<int,Employee*>* root)
{
    if(root==nullptr)
        return;
    delete root->value;
    releaseWorkers(root->right);
    releaseWorkers(root->left);
}
void removeCompanies(AVLTree<int,Company*>* root)
{
    if(root==nullptr)
        return;
    delete root->value;
    removeCompanies(root->right);
    removeCompanies(root->left);
}

void Workplace::QuitWorkplace()
{
    removeCompanies(this->companies);
    releaseWorkers(this->employeeID);
    releaseFromSal(this->employeeSAL);
    Quit(this->employeeID);
    Quit(this->employeeSAL);
    Quit(this->companies);
    Quit(this->nonEmptyCompanies);
}