#include "facilityemployee.h"
#include "report.h"
#include "exceptions/accountIsNotActiveEx.h"

FacilityEmployee::FacilityEmployee(string fName, string lName, string bDate, string uName, string pass, int pNum, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, pNum, bSalary, offH, overH, b)
{
}
FacilityEmployee::FacilityEmployee(string fName, string lName, string bDate, string uName, string pass, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, bSalary, offH, overH, b)
{
}
void FacilityEmployee::deactivateAllAccountsByNationalCode()
{
    while (true)
    {
        cout << "Enter the national code : ";
        string nCode;
        cin >> nCode;

        bool nationalCodeExist = false;

        for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
        {
            if (bank->getAllAccounts()->at(i).getNationalCode() == nCode)
            {
                nationalCodeExist = true;
                this->deactivateAccount(bank->getAllAccounts()->at(i).getAccountID());
                break;
            }
        }
        if (nationalCodeExist == false)
        {
            cerr << "# No account found with this national code. Try again #" << endl;
        }
        else
        {
            break;
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
    if (!bank->getLoanReqs()->empty())
    {
        cout << "First Loan Request" << endl;
        bank->getLoanReqs()->at(0).showLoanInfo();
        cout << "Agree? ";
        string yesOrno;
        cin >> yesOrno;

        if (yesOrno == "yes")
        {
            for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
            {
                if (bank->getLoanReqs()->at(0).getAccountID() == bank->getAllAccounts()->at(i).getAccountID())
                {
                    bank->getAllAccounts()->at(i).deposit(bank->getAllAccounts()->at(i).getLoanAmountPotential());
                    cout << "Loan amount transfered successfuly to the account\nLoan details has been sent to the customer" << endl;

                    Report report;
                    report.getLoan(bank->getAllAccounts()->at(i).getNationalCode(), bank->getLoanReqs()->at(0).getAmountOfLoan());

                    bank->getLoans()->push_back(bank->getLoanReqs()->at(0));
                    bank->getLoanReqs()->erase(bank->getLoanReqs()->begin());

                    break;
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
    else
    {
        cout << "# There is no loan requests #" << endl;
    }
}

void FacilityEmployee::showLoanInfoBasedOnSerialNumber()
{
    string serialNum;
    cout << "Enter serial number: ";
    cin >> serialNum;

    bool serialNumExist = false;

    for (size_t i = 0; i < bank->getLoans()->size(); i++)
    {
        if (serialNum == bank->getLoans()->at(i).getSerialNumber())
        {
            serialNumExist = true;
            bank->getLoans()->at(i).showLoanInfo();
        }
    }

    if (serialNumExist == false)
    {
        cerr << "# There is no employee with this serial number #" << endl;
    }
}
