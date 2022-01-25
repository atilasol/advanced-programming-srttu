#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include "bank.h"
#include "date.h"

using namespace std;

class Loan
{
    static constexpr int defaultNumberOfInstallments = 24;
    friend class Bank;

private:
    string connectedAccountID;
    string dateReceived;
    double amount;
    double interestRate;
    int totalNumberOfInstallments;
    int numberOfInstallmentsPaid;
    double amountOfEachInstallment;
    int numberOfOverdueInstallments;
    string serialNumber;
    int numberOfWarnings;

public:
    Loan(string accID, string serialN, string date, double amount, int nIns, int nInsPaid, int nOverdue, int warnings);
    Loan(string accID, string date, double amount, int nIns);

    string getSerialNumber();
    string getAccountID();
    int getNumberOfInstallments();
    int getNumberOfPaidInstallments();
    double getAmountOfEachInstallment();
    int getNumberOfWarnings();

    void setWarning();
    void showLoanInfo();
};

#endif // LOAN_H
