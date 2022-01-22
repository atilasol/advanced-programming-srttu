#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include "bank.h"
#include "date.h"

using namespace std;

class Employee
{
    friend class Bank;
private:
    static constexpr double offTimePerMonth = 15;
    static constexpr double overTimePerMonth = 12;
    static constexpr double salaryReduction = 100000;
    static constexpr double salaryIncrease = 120000;

protected:
    string employeeType;
    string firstName;
    string lastName;
    Date birthDate;
    string username;
    string password;
    int personalNumber;
    double basicSalary;
    double overallSalary;
    double offTimeHours;
    double overTimeHours;
    Bank *bank;

public:
    Employee(string type ,string fName , string lName , Date bDate , string uName , string pass , int pNumber ,double bSalary , double offH , double overH,Bank *b);

    void showPersonalInfo();
    string getFirstName();
    string getLastName();
    string getUsername();
    string getPassword();
    string getEmployeeType();
    int getPersonalNumber();

    void offTimeReq();
    void overtimeReq();

    void showCustomerInfoByNationalID(string nationalCode);
    void activateAccount(string accountID);
    void deactivateAccount(string accountID);
};

#endif // EMPLOYEE_H
