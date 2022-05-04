#include "Company.h"
#include <iostream>

Company::Company(int company_id,int value) : companyId(company_id),value(value),employee_count(0) {
    workersId = nullptr;
    workersSal = nullptr;
    highest_earner=nullptr;
}


Result Company::AddEmployee(Employee* emp){
    try{
    this->workersId = insertNode(emp->EmployeeId, emp, this->workersId);
    this->workersSal = insertNode(emp->salary, emp, this->workersSal);
    }catch(InvalidInput const&){
        return INVALID_INPUT;
    }
    catch(NodeAlreadyExists const&){
        return ALREADY_EXIST;
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
    this->employee_count--;
    return SUCCESS;
}

void Company::CompanyInfo(int* v,int* c)
{//send pointer to local ints i.e. int num1=0,int* v=&num1 and then CompanyInfo(v..)
    *v=this->value;
    *c=this->employee_count;
}
static void printTreeInternal(AVLTree<int,Employee*>* root, std::string indent, bool last) { //TODO delete
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        } else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->key << std::endl;
        printTreeInternal(root->left, indent, false);
        printTreeInternal(root->right, indent, true);
    }
}

void Company::PrintEmployees() const
{   
    std::cout<<this->companyId<<"'s workers: \n ID: \n";
    printTreeInternal(this->workersId, "", true);
    std::cout<<"Salaries: \n";
    printTreeInternal(this->workersSal, "", true);
}

void Company::setValue(const int value)
{
    this->value=value;
}



