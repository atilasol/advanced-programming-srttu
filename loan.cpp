#include "loan.h"

Loan::Loan(string aID, string serialN, string date, double amount, int nIns, int nInsPaid, int nOverdue)
    : connectedAccountID{aID}, serialNumber{serialN}, dateReceived{date}, amount{amount}, totalNumberOfInstallments{nIns}, numberOfInstallmentsPaid{nInsPaid}, numberOfOverdueInstallments{nOverdue}
{
    if(totalNumberOfInstallments == 12)
        interestRate = 4;
    else if(totalNumberOfInstallments == 24)
        interestRate = 8;
    else if(totalNumberOfInstallments == 36)
        interestRate = 12;


    amountOfEachInstallment = (amount + (amount * interestRate / 100)) / totalNumberOfInstallments;
}

string Loan::getSerialNumber() { return serialNumber; }
string Loan::getAccountID() { return connectedAccountID; }

void Loan::showLoanInfo()
{
    cout << "==== Account ID " << connectedAccountID << " ===============================" << endl;
    cout << "Serial Number : " << serialNumber << endl;
    cout << "Amount Remain: " << amount << endl;
    cout << "Installments: " << totalNumberOfInstallments << " | Paid: " << numberOfInstallmentsPaid << " | Remain Ins: " << totalNumberOfInstallments - numberOfInstallmentsPaid << endl;
}

