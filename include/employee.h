#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>

class Bank;

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
    string firstName;
    string lastName;
    string birthDate;
    string username;
    string password;
    int personalNumber;
    double basicSalary;
    double overallSalary;
    double offTimeHours;
    double overTimeHours;
    Bank *bank;

public:
    Employee(string fName, string lName, string bDate, string uName, string pass, int pNum ,double bSalary, double offH, double overH, Bank *b);
    Employee(string fName, string lName, string bDate, string uName, string pass, double bSalary, double offH, double overH, Bank *b);
    Employee();

    void showPersonalInfo();
    string getFirstName();
    string getLastName();
    string getUsername();
    string getPassword();
    int getPersonalNumber();

    void offTimeReq();
    void overtimeReq();

    void showCustomerInfoByNationalID(string nationalCode);
    void activateAccount(string accountID);
    void deactivateAccount(string accountID);

    void createNewCustomer(string nationalCode , double amount);
    void deleteCustomer(string nationalCode);
    void createAccount(string nationalCode);
    void deleteAccount();
};

#endif // EMPLOYEE_H
