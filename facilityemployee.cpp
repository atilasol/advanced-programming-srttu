#include "facilityemployee.h"

FacilityEmployee::FacilityEmployee(string fName, string lName, string bDate, string uName, string pass, int pNumber, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH, b)
{
}

void FacilityEmployee::deactivateAllAccountsByNationalCode()
{
    cout << "Enter a national code : ";
    string nCode;
    cin >> nCode;
    for (size_t i = 0; i < bank->getCustomers()->size(); i++)
    {
        if (bank->getAllAccounts()->at(i).getNationalCode() == nCode)
        {
            this->deactivateAccount(bank->getAllAccounts()->at(i).getAccountID());
        }
    }
}

void FacilityEmployee::showAllLoanRequests()
{
    for (size_t i = 0; i < bank->getLoanReqs()->size(); i++)
    {
        bank->getLoanReqs()->at(i).showLoanInfo();
    }
}

void FacilityEmployee::checkLoanReq()
{
    cout << "First Loan Request" << endl;
    bank->getLoanReqs()->at(0).showLoanInfo();
    cout << "Agree? ";
    string yesOrno;
    if (yesOrno == "yes")
    {
        for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
        {
            if (bank->getLoanReqs()->at(0).getAccountID() == bank->getAllAccounts()->at(i).getAccountID())
            {
                bank->getAllAccounts()->at(i).deposit(bank->getAllAccounts()->at(i).getLoanAmountPotential());
                cout << "Loan amount transfered successfuly to the account\nLoan details has been sent to the customer" << endl;
                bank->getLoans()->push_back(bank->getLoanReqs()->at(0));

                // deleting the first line of loan reqs
                // shifing elements
                // write and read loan reqs
                // write and read loans
            }
        }
    }
    else if (yesOrno == "no")
    {
        return;
    }
    else
        cerr << "Enter a valid string " << endl;
}

void FacilityEmployee::showLoanInfoBasedOnSerialNumber()
{
    
}
