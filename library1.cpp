#include "library1.h"
#include "Workplace.h"

void* Init(){
    Workplace* DS = new Workplace();
    return (void*)DS;
}

StatusType AddCompany(void *DS, int CompanyID, int Value){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->AddCompanyToWorkplace(CompanyID,Value);
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->AddEmployeeToWorkplace(EmployeeID,CompanyID,Salary,Grade);
}

StatusType RemoveEmployee(void *DS, int EmployeeID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->RemoveEmployeeFromWorkplace(EmployeeID);
}

StatusType RemoveCompany(void *DS, int CompanyID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->RemoveCompanyFromWorkplace(CompanyID);
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetCompanyInfoFromWorkplace(CompanyID, Value, NumEmployees);
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetEmployeeInfo(EmployeeID,EmployerID,Salary, Grade);
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->IncreaseCompanyValue(CompanyID, ValueIncrease);
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->PromoteEmployee(EmployeeID, SalaryIncrease, BumpGrade);
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->HireEmployee(EmployeeID,NewCompanyID);
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->AcquireCompany(AcquirerID, TargetID, Factor);
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetHighestEarner(CompanyID, EmployeeID);
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetAllEmployeesBySalary(CompanyID, Employees, NumOfEmployees);
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetHighestEarnerInEachCompany(NumOfCompanies, Employees);
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int
    MaxEmployeeId, int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Workplace*)DS)->GetNumEmployeesMatching(CompanyID, MinEmployeeID, MaxEmployeeId,
                                                     MinSalary, MinGrade, TotalNumOfEmployees ,
                                                     NumOfEmployees);
}

void Quit(void **DS){
    releaseWorkers( (*((Workplace**)DS))->employeeID);
    removeCompanies( (*((Workplace**)DS))->companies);
    (*((Workplace**)DS)) = NULL;
}






