#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include "bank.h"

using namespace std;

class Account
{
    friend class Bank;
    friend class Employee;
    friend class Customer;

private:
    static constexpr double minBalanceForLoan = 1000000;

    string accountID;
    string nationalCode;
    string accountOpeningDate;
    double balance;
    double loanAmountPotential;
    bool isActive;
    bool loanReqPotential;
    int daysMoreThanMinBalance;
    bool haveLoan;

public:
    // constructor
    Account(string aID, string nID, string date, double amount, bool isActive, bool lPotential, int daysForReq);
    void deposit(double amount);
    void withdraw(double amount);

    void showAccountInfo();

    double getBalance();
    string getNationalCode();
    string getAccountID();
    bool getStatus();
    double getLoanAmountPotential();
};

#endif // ACCOUNT_H
