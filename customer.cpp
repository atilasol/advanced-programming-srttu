#include <iomanip>
#include <fstream>
#include <string>
#include "customer.h"
#include "bank.h"
#include "report.h"
#include "./Exceptions/cannotSendLoanReqEx.h"

string generateSerialNumber(Bank *bank);
int chooseNumberOfInstallments();

Customer::Customer(string fName, string lName, string ID, string bDate, string uName, string pass, Bank *b)
    : firstName{fName}, lastName{lName}, nationalCode{ID}, birthDate{bDate}, username{uName}, password{pass}
{
    this->bank = b;
}

string Customer::getFirstName() { return firstName; }
string Customer::getLastName() { return lastName; }
string Customer::getUsername() { return username; }
string Customer::getPassword() { return password; }
string Customer::getNationalCode() { return nationalCode; }

int Customer::chooseWhichAccount()
{
    int accIndex = -1;
    while (true)
    {
        cout << "Account ID :";
        string accountID;
        cin >> accountID;

        for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
        {
            if (bank->getAllAccounts()->at(i).getAccountID() == accountID)
            {
                accIndex = i;
            }
        }
        if (accIndex != -1)
        {
            break;
        }
        else
        {
            cerr << "Please enter a valid account ID" << endl;
        }
    }
    return accIndex;
}

void Customer::loanRequest(int accIndex)
{
    try
    {
        if (bank->getAllAccounts()->at(accIndex).loanReqPotential)
        {
            fstream fout;
            fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/loanReqs.txt", ios::app);
            fout << bank->getAllAccounts()->at(accIndex).accountID << "-";
            Report report;
            fout << report.todayDate() << "-";

            fout << generateSerialNumber(this->bank) << "-";
            fout << setprecision(1);
            fout << fixed;
            fout << bank->getAllAccounts()->at(accIndex).loanAmountPotential << "-";

            int nIns = chooseNumberOfInstallments();
            fout << nIns << "-0-0" << endl;
            
            cout << "Loan request sent successfuly" << endl;

            fout.close();
        }
        else
            throw cannotSendLoanReqEx();
    }
    catch (const cannotSendLoanReqEx &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Customer::showPersonalInfo()
{
    cout << "=== Username : " << username << " ==========" << endl;
    cout << "Name : " << firstName << " " << lastName << endl;
    cout << "Birth date :" << birthDate << " | National Id : " << nationalCode << endl;
    cout << "============================================" << endl;

    cout << "1-Show accounts information\n2-Show loans information\nSelect:";
    char choose;
    cin >> choose;
    if (choose == '1')
    {
        showAccountsInfo();
    }
    else if (choose == '2')
    {
        showLoansInfo();
    }
    else
    {
        cerr << "#Enter a valid number#" << endl;
    }
}

void Customer::showAccountsInfo()
{
    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        if (this->getNationalCode() == bank->getAllAccounts()->at(i).getNationalCode())
        {
            cout << "\n=== Account " << i + 1 << " ==========" << endl;
            bank->getAllAccounts()->at(i).showAccountInfo();
            cout << "============================================" << endl;
        }
    }
}
void Customer::showLoansInfo()
{
}

string generateSerialNumber(Bank *bank)
{
    srand(time(0));
    int serialNumber = rand() % 999999999;
    string number = to_string(serialNumber);
    number = number.substr(0, 8);

    return number;
}

int chooseNumberOfInstallments()
{
    cout << "\tNumber Of Installments\t\tInterest Rate" << endl;
    cout << "1-\t\t12\t\t\t\t4%" << endl;
    cout << "2-\t\t24\t\t\t\t8%" << endl;
    cout << "3-\t\t36\t\t\t\t12%" << endl;

    while (true)
    {
        cout << "Select: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            return 12;
            break;
        }
        else if (choice == 2)
        {
            return 24;
            break;
        }
        else if (choice == 3)
        {
            return 36;
            break;
        }
        else
        {
            cerr << "Please enter a valid number" << endl;
        }
    }
}

void Customer::changePassword()
{
    cout << "Your current password : " << getPassword() << endl;
    cout << "Enter new password : ";
    string newPass;
    cin >> newPass;
    if (newPass != this->getPassword())
    {
        password = newPass;
        Report report;
        report.changePassword(this->getFirstName(), this->getLastName(), this->getNationalCode());
    }
    else
        cerr << "Enter a new password" << endl;
}
