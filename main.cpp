#include <iostream>
#include "bank.h"

using namespace std;

int selectChoice();
int employeeLogin();
int customerLogin();

string getUsername();
string getPassword();
void showCustomerMenu();
void selectAndDoOperationForCustomer(int, int);
int selectAndDoOperationForCustomer(int);

void showEmployeeMenu();
void showFacilityEmployeeMenu();
void showManagerMenu();
void availableAccounts(string nationalCode);

Bank bank("Bank Melli Hamedan", "1150036");

int main()
{
    while (true)
    {
        cout << "1-Employee\n2-Customer\n3-Exit" << endl;

        // Employee
        if (selectChoice() == 1)
        {
            int eIndex = employeeLogin();

            if (eIndex >= 0)
            {
                if (bank.getEmployees()->at(eIndex).getEmployeeType() == "Employee")
                {
                    showEmployeeMenu();
                    selectAndDoOperationForEmployee(eIndex);
                }
                else if (bank.getEmployees()->at(eIndex).getEmployeeType() == "Facility Employee")
                {
                    showFacilityEmployeeMenu();
                    int choice = selectAndDoOperationForEmployee(eIndex);
                }
                else if (bank.getEmployees()->at(eIndex).getEmployeeType() == "Manager")
                {
                    showManagerMenu();
                    selectAndDoOperationForEmployee(eIndex);
                    int choice = selectAndDoOperationForEmployee(eIndex);

                    if (choice == 7)
                    {
                        cout << "Enter personal number: ";
                        int pNumber;
                        cin >> pNumber;

                        int exist = false;
                        for (size_t i = 0; i < bank.getEmployees()->size(); i++)
                        {
                            if (bank.getEmployees()->at(i).getPersonalNumber() == pNumber)
                            {
                                exist = true;
                                bank.getEmployees()->at(i).showPersonalInfo();
                            }
                        }
                        if (exist == false)
                        {
                            cerr << "There is no employee with this personal number" << endl;
                        }
                    }
                    else if (choice == 8)
                    {
                    }
                    else if (choice == 9)
                    {
                    }
                }
            }
        }
        // Customer
        else if (selectChoice() == 2)
        {
            int cIndex = customerLogin();
            availableAccounts(bank.getCustomers()->at(cIndex).getNationalCode());

            if (cIndex >= 0)
            {
                int accIndex = bank.getCustomers()->at(cIndex).chooseWhichAccount();
                showCustomerMenu();
                selectAndDoOperationForCustomer(cIndex, accIndex);
            }
            else
            {
                cerr << "#Enter a valid number#" << endl;
            }
        }

        return 0;
    }
}

////////////
// Customer
////////////
int customerLogin()
{
    string username = getUsername();
    string password = getPassword();

    for (size_t i = 0; i < bank.getCustomers()->size(); i++)
    {
        if (username == bank.getCustomers()->at(i).getUsername() && password == bank.getCustomers()->at(i).getPassword())
        {
            return i;
        }
    }

    return -1;
}

void availableAccounts(string nationalCode)
{
    cout << "+++ Your Accounts +++++++++" << endl;

    for (size_t i = 0; i < bank.getAllAccounts()->size(); i++)
    {
        if (nationalCode == bank.getAllAccounts()->at(i).getNationalCode())
        {
            bank.getAllAccounts()->at(i).showAccountInfo();
        }
    }
}

void showCustomerMenu()
{
    cout << "1-Deposit" << endl;
    cout << "2-Withdrawal" << endl;
    cout << "3-Loan Request" << endl;
    cout << "4-Show Personal Info" << endl;
    cout << "5-Exit" << endl;
}

void selectAndDoOperationForCustomer(int cIndex, int accIndex)
{
    int choice = selectChoice();

    // Deposit
    if (choice == 1)
    {
        cout << "Enter the amount for deposit: ";
        double amount;
        cin >> amount;
        if (amount > 0)
            bank.getAllAccounts()->at(accIndex).deposit(amount);
        else
            cerr << "Please enter a valid amount of money" << endl;
    }
    else if (choice == 2)
    {
        cout << "Enter the amount of withdrawal: ";
        double amount;
        cin >> amount;
        if (amount > 0)
            bank.getAllAccounts()->at(accIndex).withdraw(amount);
        else
            cerr << "Please enter a valid amount of money" << endl;
    }
    else if (choice == 3)
    {
        bank.getCustomers()->at(cIndex).loanRequest();
    }
    else if (choice == 4)
    {
        bank.getCustomers()->at(cIndex).showAccountsInfo();
    }
    else if (choice == 5)
    {
        return;
    }
}

////////////
// Employee
////////////
int employeeLogin()
{
    string username = getUsername();
    string password = getPassword();

    for (size_t i = 0; i < bank.getEmployees()->size(); i++)
    {
        if (username == bank.getEmployees()->at(i).getUsername() && password == bank.getEmployees()->at(i).getPassword())
        {
            return i;
        }
    }

    return -1;
}

void showEmployeeMenu()
{
    cout << "1-Offtime Request" << endl;
    cout << "2-Overtime Request" << endl;
    cout << "3-Show Personal Info" << endl;
    cout << "4-Show Customer Info By National Code" << endl;
    cout << "5-Create New Customer Account" << endl;
    cout << "6-Delete Customer Account" << endl;
}
void showFacilityEmployeeMenu()
{
    cout << "8-Deactivate All Customer Account Based On National Code" << endl;
    cout << "8-Show All Loans Requests" << endl;
    cout << "9-Checking Loan Requests" << endl;
    cout << "10-Show Loan Condition Based On Serial Number" << endl;
}
void showManagerMenu()
{
    cout << "7-Show Employee Info Based On Personal Number" << endl;
    cout << "8-Hire An Employee" << endl;
    cout << "9-Fire An Employee" << endl;
}

int selectAndDoOperationForEmployee(int eIndex)
{
    int choice = selectChoice();

    if (choice == 1)
    {
        bank.getEmployees()->at(eIndex).offTimeReq();
    }
    else if (choice == 2)
    {
        bank.getEmployees()->at(eIndex).overtimeReq();
    }
    else if (choice == 3)
    {
        bank.getEmployees()->at(eIndex).showPersonalInfo();
    }
    else if (choice == 4)
    {
        cout << "Enter the national code: ";
        string nCode;
        cin >> nCode;
        bank.getEmployees()->at(eIndex).showCustomerInfoByNationalID(nCode);
    }
    // Create Customer Account
    else if (choice == 5)
    {
    }
    // Delete Customer Account
    else if (choice == 6)
    {
    }

    return choice;
}

////////////////////
// Useful functions
////////////////////
int selectChoice()
{
    cout << "Select: ";
    int choice;
    cin >> choice;
    return choice;
}
string getUsername()
{
    cout << "Username: ";
    string username;
    getline(cin, username);
    return username;
}
string getPassword()
{
    cout << "Password: ";
    string password;
    getline(cin, password);
    return password;
}
