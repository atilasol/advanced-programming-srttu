#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "bank.h"
#include "employee.h"

using namespace std;

class Manager : public Employee
{
private:
    Bank *bank;
public:
    Manager(string type , string fName, string lName, Date bDate, string uName, string pass, int pNumber, double bSalary , double offH , double overH , Bank *b);

    void showEmployeeByPersonalNumber(int personalNumber);
    void hireEmployee();
    void fireEmployee();

};

#endif // MANAGER_H
