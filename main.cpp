#include <iostream>
#include <fstream>
#include <ctime>
#include "bank.h"
#include "report.h"
#include "date.h"

using namespace std;

int selectChoice();
int employeeLogin();
int customerLogin();

string inputUsername();
string inputPassword();
void showCustomerMenu();
void selectAndDoOperationForCustomer(int, int);
void selectAndDoOperationForEmployee(int);
void doOperationForManager();
void doOperationForFacilityEmployee();

void showEmployeeMenu();
void showFacilityEmployeeMenu();
void showManagerMenu();
void availableAccounts(string nationalCode);

Bank *bank = new Bank("Bank Melli Hamedan", "1150036");

int main()
{
    Report report;
    report.updateDate();

    while (true)
    {
        cout << "1-Employee\n2-Customer\n3-Exit" << endl;

        int choice = selectChoice();
        if (choice == 1)
        {
            int i = employeeLogin();
            if (i != -3)
            {
                // Normal Employee
                if (i >= 0)
                {
                    report.employeeLogin(bank->getEmployees()->at(i).getPersonalNumber());
                    selectAndDoOperationForEmployee(i);
                }
                // Facility Employee
                else if (i == -1)
                {
                    report.employeeLogin(bank->getFacilityEmployee()->at(0).getPersonalNumber());
                    doOperationForFacilityEmployee();
                }
                // Manager
                else if (i == -2)
                {
                    report.employeeLogin(bank->getManager()->at(0).getPersonalNumber());
                    doOperationForManager();
                }
            }
            else
            {
                cerr << "# Try Again #" << endl;
            }
        }
        else if (choice == 2)
        {
            int cIndex = customerLogin();
            availableAccounts(bank->getCustomers()->at(cIndex).getNationalCode());

            if (cIndex >= 0)
            {
                report.customerLogin(bank->getCustomers()->at(cIndex).getNationalCode());
                int accIndex = bank->getCustomers()->at(cIndex).chooseWhichAccount();
                selectAndDoOperationForCustomer(cIndex, accIndex);
            }
            else
            {
                cerr << "# Try Again #" << endl;
            }
        }
        else if (choice == 3)
        {
            bank->dailyReporting();
            return 1;
        }
    }

    return 0;
}

////////////
// Customer
////////////
int customerLogin()
{
    string username = inputUsername();
    string password = inputPassword();

    int n{-1};
    for (size_t i = 0; i < bank->getCustomers()->size(); i++)
    {
        if (username == bank->getCustomers()->at(i).getUsername() && password == bank->getCustomers()->at(i).getPassword())
        {
            cout << "\n$$$ Welcome " << bank->getCustomers()->at(i).getFirstName() << " " << bank->getCustomers()->at(i).getLastName() << "$$$" << endl;
            n = i;
        }
    }

    return n;
}

void availableAccounts(string nationalCode)
{
    cout << "\n+++ Your Accounts +++++++++" << endl;

    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        if (nationalCode == bank->getAllAccounts()->at(i).getNationalCode())
        {
            bank->getAllAccounts()->at(i).showAccountInfo();
        }
    }
}

void showCustomerMenu()
{
    cout << "\n1-Deposit" << endl;
    cout << "2-Withdrawal" << endl;
    cout << "3-Loan Request" << endl;
    cout << "4-Show Personal Info" << endl;
    cout << "5-Exit" << endl;
}

void selectAndDoOperationForCustomer(int cIndex, int accIndex)
{
    while (true)
    {
        showCustomerMenu();
        int choice = selectChoice();

        // Deposit
        if (choice == 1)
        {
            cout << "Enter the amount for deposit: ";
            double amount;
            cin >> amount;
            if (amount > 0)
                bank->getAllAccounts()->at(accIndex).deposit(amount);
            else
                cerr << "Please enter a valid amount of money" << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter the amount of withdrawal: ";
            double amount;
            cin >> amount;
            if (amount > 0)
                bank->getAllAccounts()->at(accIndex).withdraw(amount);
            else
                cerr << "Please enter a valid amount of money" << endl;
        }
        else if (choice == 3)
        {
            bank->getCustomers()->at(cIndex).loanRequest(accIndex);
        }
        else if (choice == 4)
        {
            bank->getCustomers()->at(cIndex).showPersonalInfo();
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cerr << "Please enter a valid number" << endl;
        }
    }
}

////////////
// Employee
////////////
int employeeLogin()
{
    string username = inputUsername();
    string password = inputPassword();

    int n = -4;
    if (username == bank->getManager()->at(0).getUsername() && password == bank->getManager()->at(0).getPassword())
    {
        n = -2;
    }
    else if (username == bank->getFacilityEmployee()->at(0).getUsername() && password == bank->getFacilityEmployee()->at(0).getPassword())
    {
        n = -1;
    }
    else
    {
        for (size_t i = 0; i < bank->getEmployees()->size(); i++)
        {
            if (username == bank->getEmployees()->at(i).getUsername() && password == bank->getEmployees()->at(i).getPassword())
            {
                n = i;
            }
        }
    }

    return n;
}

void showEmployeeMenu()
{
    cout << "\n**************************************" << endl;
    cout << "1-Offtime Request" << endl;
    cout << "2-Overtime Request" << endl;
    cout << "3-Show Personal Info" << endl;
    cout << "4-Show Customer Info By National Code" << endl;
    cout << "5-Create New Customer Account" << endl;
    cout << "6-Delete Customer Account" << endl;
}
void showFacilityEmployeeMenu()
{
    cout << "7-Deactivate All Customer Account Based On National Code" << endl;
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

void selectAndDoOperationForEmployee(int eIndex)
{
    while (true)
    {
        showEmployeeMenu();
        cout << "10-Exit" << endl;
        int choice = selectChoice();

        if (choice == 1)
        {
            bank->getEmployees()->at(eIndex).offTimeReq();
        }
        else if (choice == 2)
        {
            bank->getEmployees()->at(eIndex).overtimeReq();
        }
        else if (choice == 3)
        {
            bank->getEmployees()->at(eIndex).showPersonalInfo();
        }
        else if (choice == 4)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            bank->getEmployees()->at(eIndex).showCustomerInfoByNationalID(nCode);
        }
        // Create Customer Account
        else if (choice == 5)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            if(nCode.length() == 10)
            {
                bank->getEmployees()->at(eIndex).createAccount(nCode);
            }
            else
            {
                cerr << "# National code should be 10 digits #" << endl;
            }
        }
        // Delete Customer Account
        else if (choice == 6)
        {
            bank->getEmployees()->at(eIndex).deleteAccount();
        }
        else if (choice == 10)
        {
            break;
        }
        else
        {
            cerr << "Please enter a valid number" << endl;
        }
    }
}

void doOperationForManager()
{
    while (true)
    {
        showEmployeeMenu();
        showManagerMenu();
        cout << "10-Exit" << endl;
        int choice = selectChoice();

        if (choice == 1)
        {
            bank->getManager()->at(0).offTimeReq();
        }
        else if (choice == 2)
        {
            bank->getManager()->at(0).overtimeReq();
        }
        else if (choice == 3)
        {
            bank->getManager()->at(0).showPersonalInfo();
        }
        else if (choice == 4)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            bank->getManager()->at(0).showCustomerInfoByNationalID(nCode);
        }
        // Create  Account
        else if (choice == 5)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            bank->getManager()->at(0).createAccount(nCode);
        }
        // Delete  Account
        else if (choice == 6)
        {
            bank->getManager()->at(0).deleteAccount();
        }
        else if (choice == 7)
        {
            cout << "Enter personal number: ";
            int pNumber;
            cin >> pNumber;

            int exist = false;
            for (size_t i = 0; i < bank->getEmployees()->size(); i++)
            {
                if (bank->getEmployees()->at(i).getPersonalNumber() == pNumber)
                {
                    exist = true;
                    bank->getEmployees()->at(i).showPersonalInfo();
                }
            }
            if (exist == false)
            {
                cerr << "There is no employee with this personal number" << endl;
            }
        }
        // hire employee
        else if (choice == 8)
        {
            bank->getManager()->at(0).hireEmployee();
        }
        // fire employee
        else if (choice == 9)
        {
            bank->getManager()->at(0).fireEmployee();
        }
        else if (choice == 10)
        {
            break;
        }
        else
        {
            cerr << "Please enter a valid number" << endl;
        }
    }
}

void doOperationForFacilityEmployee()
{
    while (true)
    {
        showEmployeeMenu();
        showFacilityEmployeeMenu();
       cout << "11-Exit" << endl;
        int choice = selectChoice();

        if (choice == 1)
        {
            bank->getFacilityEmployee()->at(0).offTimeReq();
        }
        else if (choice == 2)
        {
            bank->getFacilityEmployee()->at(0).overtimeReq();
        }
        else if (choice == 3)
        {
            bank->getFacilityEmployee()->at(0).showPersonalInfo();
        }
        else if (choice == 4)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            bank->getFacilityEmployee()->at(0).showCustomerInfoByNationalID(nCode);
        }
        // Create  Account
        else if (choice == 5)
        {
            cout << "Enter the national code: ";
            string nCode;
            cin >> nCode;
            bank->getFacilityEmployee()->at(0).createAccount(nCode);
        }
        // Delete  Account
        else if (choice == 6)
        {
            bank->getFacilityEmployee()->at(0).deleteAccount();
        }
        else if (choice == 7)
        {
            bank->getFacilityEmployee()->at(0).deactivateAllAccountsByNationalCode();
        }
        else if (choice == 8)
        {
            bank->getFacilityEmployee()->at(0).showAllLoanRequests();
        }
        else if (choice == 9)
        {
            bank->getFacilityEmployee()->at(0).checkLoanReq();
        }
        else if (choice == 10)
        {
            bank->getFacilityEmployee()->at(0).showLoanInfoBasedOnSerialNumber();
        }
        else if (choice == 11)
        {
            break;
        }
        else
        {
            cerr << "Please enter a valid number" << endl;
        }
    }
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
