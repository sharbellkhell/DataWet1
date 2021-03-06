#include <iostream>
#include "library1.h"
#include "Employee.h"
#include "AVLTree.h"
#include "Company.h"

Company::Company(int company_id,int value) : companyId(company_id),value(value),employee_count(0) {
    workersId = nullptr;
    workersSal = nullptr;
    highest_earner=nullptr;
}
Company::~Company()
{
    int* emps=new int[this->employee_count];
    int count=0;
    int* p = &count;
    lowest_to_highest(workersId,&emps,p);
    for(int i=0;i<count;i++)
        this->RemoveEmployeeByID(emps[i]);
    Quit(workersId);
    Quit(workersSal);
    delete[] emps;
}
static AVLTree<int,AVLTree<int,Employee*>*>* insertDuplicateNode(int sal,Employee* emp,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    if(temp==nullptr)
    {
        AVLTree<int, Employee*>* sal_Range=init(emp->EmployeeId,emp);
        root=insertNode(sal,sal_Range,root);
        return root;
    }
    else{
        temp->value=insertNode(emp->EmployeeId,emp,temp->value);
        return root;
    }

}

StatusType Company::AddEmployee(Employee* emp){
    try{
    this->workersId = insertNode(emp->EmployeeId, emp, this->workersId);
    this->workersSal = insertDuplicateNode(emp->salary, emp, this->workersSal);
    }catch(InvalidInput const&){
        return INVALID_INPUT;
    }
    catch(NodeAlreadyExists const&){
        return FAILURE;
    }
    catch(std::bad_alloc const&){
        return ALLOCATION_ERROR;
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
    this->employee_count++;
    return SUCCESS;

}
static Employee* find_highest_earner(Company* company)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=company->workersSal;
    while(temp->right!=nullptr)
        temp=temp->right;
    AVLTree<int,Employee*>* emp_temp=temp->value;
    if(emp_temp==nullptr)
        return nullptr;
    while(emp_temp->left!=nullptr)
        emp_temp=emp_temp->left;
    return emp_temp->value;
}
static void removeDuplicateNode(int sal,int emp_id,AVLTree<int,AVLTree<int,Employee*>*>* root)
{
    AVLTree<int,AVLTree<int,Employee*>*>* temp=findNode(root,sal);
    if(temp!=nullptr)
        temp->value=removeNode(temp->value,emp_id);
}
StatusType Company::RemoveEmployeeByID(const int employee_id)
{
    AVLTree<int,Employee*>* employee = findNode(this->workersId,employee_id);
    if(employee == nullptr)
        return FAILURE;
    int sal_to_remove=employee->value->salary;
    this->workersId=removeNode(this->workersId,employee_id);
    removeDuplicateNode(sal_to_remove,employee_id,this->workersSal);
    if(this->highest_earner!=nullptr)
    {
    if(this->highest_earner->EmployeeId==employee_id)
        this->highest_earner=find_highest_earner(this);
    }
    this->employee_count--;
    return SUCCESS;
}

void Company::CompanyInfo(int* v,int* c)
{//send pointer to local ints i.e. int num1=0,int* v=&num1 and then CompanyInfo(v..)
    *v=this->value;
    *c=this->employee_count;
}

void Company::setValue(const int value)
{
    this->value=value;
}



