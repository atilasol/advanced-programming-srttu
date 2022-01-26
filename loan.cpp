#include "loan.h"

Loan::Loan(string accID, string serialN, string date, double amount, int nIns, int nInsPaid, int nOverdue, int warnings)
    : connectedAccountID{accID}, serialNumber{serialN}, dateReceived{date}, amount{amount}, totalNumberOfInstallments{nIns}, numberOfInstallmentsPaid{nInsPaid}, numberOfOverdueInstallments{nOverdue}, numberOfWarnings{warnings}
{
    if (totalNumberOfInstallments == 12)
        interestRate = 4;
    else if (totalNumberOfInstallments == 24)
        interestRate = 8;
    else if (totalNumberOfInstallments == 36)
        interestRate = 12;

    amountOfEachInstallment = (amount + (amount * interestRate / 100)) / totalNumberOfInstallments;
}

Loan::Loan(string accID, string date, double amount, int nIns)
    : connectedAccountID{accID}, dateReceived{date}, amount{amount}, totalNumberOfInstallments{nIns}
{
}

string Loan::getSerialNumber() { return serialNumber; }
string Loan::getAccountID() { return connectedAccountID; }
int Loan::getNumberOfInstallments() { return totalNumberOfInstallments; }
int Loan::getNumberOfPaidInstallments() { return numberOfInstallmentsPaid; }
double Loan::getAmountOfEachInstallment() { return amountOfEachInstallment; }
int Loan::getNumberOfWarnings() { return numberOfWarnings; }
double Loan::getAmountOfLoan() { return amount;}

void Loan::setWarning() { numberOfWarnings++; }

void Loan::showLoanInfo()
{
    cout << "==== Account ID " << connectedAccountID << " ===============================" << endl;
    cout << "Serial Number : " << serialNumber << endl;
    cout << "Amount Remain: " << amount << endl;
    cout << "Installments: " << totalNumberOfInstallments << " | Paid: " << numberOfInstallmentsPaid << " | Remain Ins: " << totalNumberOfInstallments - numberOfInstallmentsPaid << endl;
    cout << "Amount Of Each Installment : " << amountOfEachInstallment << endl;
}
