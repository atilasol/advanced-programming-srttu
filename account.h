#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

class Account
{
    friend class Bank;
    friend class Employee;
    friend class Customer;

private:
    static constexpr double minBalanceForLoan = 1000000;

    string accountID;
    string nationalCode;
    Date accountOpeningDate;
    double balance;
    double loanAmountPotential;
    bool isActive;
    bool loanReqPotential;
    int daysMoreThanMinBalance;

public:
    // constructor
    Account(string aID, string nID, Date date, double amount, bool isActive, bool lPotential, int daysForReq);
    void deposit(double amount);
    void withdraw(double amount);

    void showAccountInfo();

    string getNationalCode();
};

#endif // ACCOUNT_H
