#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include "account.h"
#include "bank.h"
#include "date.h"

using namespace std;
class Customer
{
private:
    friend class Bank;
    friend class Employee;
    friend class Account;
    Bank *bank;

protected:
    string firstName;
    string lastName;
    string nationalCode;
    Date birthDate;
    string username;
    string password;
public:
    Customer(string fName , string lName , string ID , Date bDate , string uName , string pass , Bank *b);

    string getUsername();
    string getPassword();
    string getNationalCode();
    
    int chooseWhichAccount();
    void loanRequest();
    void showPersonalInfo();
    void showAccountsInfo();
    void showLoansInfo();


};

#endif // CUSTOMER_H
