#include "Company.h"

Company::Company(int id,int value):companyId(id),value(value){}

Result Company::AddEmp(Employee* emp){
    try
    {
    insert(this->companyId, emp->EmployeeId, emp);
    insert(this->companyId, emp->salary, emp);
    }catch(NodeAlreadyExists())

}

