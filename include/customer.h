#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>

using namespace std;

class Bank;
class Customer
{
private:
    friend class Bank;
    friend class Employee;
    friend class Account;

protected:
    string firstName;
    string lastName;
    string nationalCode;
    string birthDate;
    string username;
    string password;
    Bank *bank;

public:
    Customer(string fName, string lName, string ID, string bDate, string uName, string pass, Bank *b);

    string getFirstName();
    string getLastName();
    string getUsername();
    string getPassword();
    string getNationalCode();

    int chooseWhichAccount();
    void loanRequest(int accIndex);
    void showPersonalInfo();
    void showAccountsInfo();
    void showLoansInfo();
    void changePassword();
};

#endif // CUSTOMER_H
