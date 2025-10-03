#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "bank.h"

using namespace std;

class Manager : public Employee
{
public:
    Manager(string fName, string lName, string bDate, string uName, string pass, int pNum, double bSalary, double offH, double overH, Bank *b);
    Manager(string fName, string lName, string bDate, string uName, string pass, double bSalary , double offH , double overH , Bank *b);

    void showEmployeeByPersonalNumber(int personalNumber);
    void hireEmployee();
    void fireEmployee();

};

#endif // MANAGER_H
