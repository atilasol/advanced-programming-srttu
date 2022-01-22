#include <fstream>
#include <string>
#include "customer.h"

class cannotSendLoanReqException
{
};

Customer::Customer(string fName, string lName, string ID, Date bDate, string uName, string pass, Bank *b)
    : firstName{fName}, lastName{lName}, nationalCode{ID}, birthDate{bDate}, username{uName}, password{pass}
{
    this->bank = b;
}

string Customer::getUsername() { return username; }
string Customer::getPassword() { return password; }
string Customer::getNationalCode() { return nationalCode; }

int Customer::chooseWhichAccount()
{
    vector<string> IDs;
    vector<int> accountIndices;
    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        if (bank->getAllAccounts()->at(i).nationalCode == nationalCode)
        {
            IDs.push_back(bank->getAllAccounts()->at(i).accountID);
            accountIndices.push_back(i);
        }
    }
    while (true)
    {
        cout << "Account ID :";
        string accountID;
        cin >> accountID;

        for (size_t i = 0; i < IDs.size(); i++)
        {
            if (accountID == IDs.at(i))
            {
                return accountIndices.at(i);
                break;
            }
        }
    }
}

void Customer::loanRequest()
{
    string accountIDs;
    bool loanPot = false;
    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        if (bank->getAllAccounts()->at(i).loanReqPotential == true)
        {
            cout << "You can send loan request for this account" << endl;
            bank->getAllAccounts()->at(i).showAccountInfo();
            loanPot = true;
        }
    }
    if (loanPot == false)
    {
        throw cannotSendLoanReqException();
    }
    else
    {
        int accIndex = chooseWhichAccount();
        fstream fout;
        fout.open("./DataBase/loanReq", ios::app);
        fout << bank->getAllAccounts()->at(accIndex).accountID << "-";
        fout << generateSerialNumber(bank) << "-";
        fout << bank->todayDate() << "-";
        fout << bank->getAllAccounts()->at(accIndex).loanAmountPotential << "-";
        fout << chooseNumberOfInstallments() << "-0-0";


        cout << "Loan request sent successfuly" << endl;
        fout.close();
    }
}

void Customer::showPersonalInfo()
{
    cout << "=== Username : " << username << " ==========" << endl;
    cout << "Name : " << firstName << " " << lastName << endl;
    cout << "Birth date :" << birthDate << " | National Id : " << nationalCode << endl;
    cout << "============================================" << endl;
    while (true)
    {
        cout << "1-Show accounts information\n2-Show loans information\nSelect:";
        char choose;
        cin >> choose;
        if (choose == '1')
        {
            showAccountsInfo();
            break;
        }
        else if (choose == '2')
        {
            showLoansInfo();
            break;
        }
        else
        {
            cerr << "#Enter a valid number#" << endl;
        }
    }
}

void Customer::showAccountsInfo()
{
    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        cout << "=== Account " << i + 1 << " ==========" << endl;
        bank->getAllAccounts()->at(i).showAccountInfo();
        cout << "============================================" << endl;
    }
}
void Customer::showLoansInfo()
{
    
}

string generateSerialNumber(Bank *bank)
{
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