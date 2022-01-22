#include <iostream>
#include "account.h"
#include "date.h"

using namespace std;

class accountIsNotActiveEx
{
};

Account::Account(string aID, string nID, Date date, double amount, bool isActive, bool lPotential, int days)
    : accountID{aID}, nationalCode{nID}, accountOpeningDate{date}, balance{amount}, isActive{isActive}, loanReqPotential{lPotential}
{
    if (balance >= minBalanceForLoan)
    {
        daysMoreThanMinBalance++;
        loanAmountPotential = daysMoreThanMinBalance * balance;
    }
    
}

void Account::deposit(double amount)
{
    balance += amount;
}

void Account::withdraw(double amount)
{
    isActive ? balance -= amount : throw accountIsNotActiveEx();
}

void Account::showAccountInfo()
{
    cout << "Owner national ID :" << nationalCode << " | Account ID : " << accountID << endl;
    cout << "Balance : " << balance << endl;
    cout << "Account Opening Date : " << accountOpeningDate << endl;
    cout << boolalpha;
    cout << "Status : " << isActive;
    cout << "Loan Request Potential : " << loanReqPotential << endl;
}

string Account::getNationalCode() { return nationalCode; }