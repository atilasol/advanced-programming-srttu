#ifndef REPORT_H
#define REPORT_H

#include <iostream>

using namespace std;

class Report
{
public:
    string todayDate();
    void updateDate();
    string now();

public:
    void customerLogin(string nationalCode);
    void employeeLogin(int personalNumber);
    void newCustomer(string nationalCode);
    void deleteAccount(string nationalCode);
    void deposit(string nationalCode , double amount);
    void withdrawal(string nationalcode , double amout);
    void getLoan(string nationalCode , double value);
    void getOfftime(int personalNumber , int hours);
    void changePassword(string firstname, string lastname , string nationalCode);
    void loanWithdrawal(string nationalCode , double value);
    void deactivated(string nationalCode , string accountID);
};

#endif // REPORT_H
