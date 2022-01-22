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
    Date dateReceived;
    double amount;
    double interestAmount;
    int totalNumberOfInstallments;
    int numberOfInstallmentsPaid;
    double amountOfEachInstallment;
    int numberOfOverdueInstallments;
    string serialNumber;

public:
    Loan(string aID ,string serialN , Date date ,double amount ,int nIns , int nInsPaid , int nOverdue );
    string getSerialNumber();
};

#endif // LOAN_H
