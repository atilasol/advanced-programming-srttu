#ifndef LOAN_H
#define LOAN_H

#include <iostream>
#include "date.h"

using namespace std;

class Loan
{
    static constexpr int defaultNumberOfInstallments = 24;

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

public:
    Loan(string aID ,string serialN , string date ,double amount ,int nIns , int nInsPaid , int nOverdue );
    string getSerialNumber();
    string getAccountID();
    void showLoanInfo();
};

#endif // LOAN_H
