#ifndef FACILITYEMPLOYEE_H
#define FACILITYEMPLOYEE_H

#include <iostream>
#include "bank.h"

using namespace std;

class FacilityEmployee : public Employee
{
public:
    FacilityEmployee(string fName, string lName, string bDate, string uName, string pass, int pNum, double bSalary, double offH, double overH, Bank *b);
    FacilityEmployee(string fName, string lName, string bDate, string uName, string pass, double bSalary, double offH, double overH, Bank *b);

    void deactivateAllAccountsByNationalCode();
    void showAllLoanRequests();
    void checkLoanReq();
    void showLoanInfoBasedOnSerialNumber();
};

#endif // FACILITYEMPLOYEE_H
