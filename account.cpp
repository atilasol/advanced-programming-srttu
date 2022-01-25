#include <iostream>
#include "account.h"
#include "report.h"
#include "./Exceptions/accountIsNotActiveEx.h"
#include "./Exceptions/notEnoughBalanceEx.h"

using namespace std;

Account::Account(string aID, string nID, string date, double amount, bool isActive, bool lPotential, int days)
    : accountID{aID}, nationalCode{nID}, accountOpeningDate{date}, balance{amount}, isActive{isActive}, loanReqPotential{lPotential}, daysMoreThanMinBalance{days}
{
    if (balance >= minBalanceForLoan)
    {
        daysMoreThanMinBalance++;
        loanAmountPotential = daysMoreThanMinBalance * balance;
    }
}

void Account::deposit(double amount)
{
    Report report;
    report.deposit(this->getNationalCode(), amount);
    balance += amount;

    if (isActive == false && amount > 10000000)
    {
        isActive = true;
    }
}

void Account::withdraw(double amount)
{

    try
    {
        if (isActive)
        {
            try
            {
                if (amount <= balance)
                {
                    Report report;
                    report.withdrawal(this->getNationalCode(), amount);
                    balance -= amount;
                    if (balance < minBalanceForLoan)
                    {
                        loanReqPotential = false;
                    }
                }
                else
                    throw notEnoughBalanceEx();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
            throw accountIsNotActiveEx();
    }
    catch (const accountIsNotActiveEx &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Account::showAccountInfo()
{
    cout << boolalpha;

    cout << "*****************************************" << endl;
    cout << "National ID :" << nationalCode << endl;
    cout << "Account ID : " << accountID << endl;
    cout << "Balance : " << balance << endl;
    cout << "Account Opening Date : " << accountOpeningDate << endl;
    cout << boolalpha;
    cout << "Is Active? : " << isActive << " | Loan Request Potential : " << loanReqPotential << endl;
}

string Account::getNationalCode() { return nationalCode; }
string Account::getAccountID() { return accountID; }
double Account::getLoanAmountPotential() { return loanAmountPotential; }
double Account::getBalance() { return balance; }
bool Account::getStatus() { return isActive; }