#include <iomanip>
#include <fstream>
#include "report.h"
#include "bank.h"
#include "exceptions/aboveOverTimeRequestEx.h"
#include "exceptions/customerExistEx.h"
#include "exceptions/usernameExistEx.h"

string inputFirstname();
string inputLastname();
string inputBirthdate();
string inputNationalCode();
string inputUsername();
string inputPassword();
double inputBasicSalary();
string generateAccountID();
int generatePersonalNum();

Employee::Employee(string fName, string lName, string bDate, string uName, string pass, int pNum, double bSalary, double offH, double overH, Bank *b)
    : firstName{fName}, lastName{lName}, birthDate{bDate}, username{uName}, password{pass}, personalNumber{pNum}, basicSalary{bSalary}, offTimeHours{offH}, overTimeHours{overH}
{
    cout << setprecision(1);
    cout << fixed << endl;
    this->bank = b;
    overallSalary = basicSalary;
}

Employee::Employee(string fName, string lName, string bDate, string uName, string pass, double bSalary, double offH, double overH, Bank *b)
    : firstName{fName}, lastName{lName}, birthDate{bDate}, username{uName}, password{pass}, basicSalary{bSalary}, offTimeHours{offH}, overTimeHours{overH}
{
    personalNumber = generatePersonalNum();

    cout << setprecision(1);
    cout << fixed << endl;
    this->bank = b;
    overallSalary = basicSalary;
}
Employee::Employee() = default;

void Employee::showPersonalInfo()
{
    cout << "=== Username : " << username << " ==========" << endl;
    cout << "Name : " << firstName << " " << lastName << endl;
    cout << "Overall Salary: " << overallSalary << endl;
    cout << "Birth date :" << birthDate << " | Personal Number : " << personalNumber << endl;
    cout << "Offtime hours: " << offTimeHours << "   | Overtime hours: " << overTimeHours << endl;
    cout << "=====================================" << endl;
}

string Employee::getFirstName() { return firstName; }
string Employee::getLastName() { return lastName; }
int Employee::getPersonalNumber() { return personalNumber; }
string Employee::getUsername() { return username; }
string Employee::getPassword() { return password; }

void Employee::offTimeReq()
{
    cout << "How many hours do you want for your offtime ? ";
    int hours;
    cin >> hours;
    offTimeHours += hours;

    if (offTimeHours > offTimePerMonth)
    {
        cout << setprecision(1);
        cout << fixed << endl;
        overallSalary -= ((offTimeHours - offTimePerMonth) * salaryReduction);
        cout << "Yor overall salary will be : " << overallSalary << " after these offtimes!" << endl;

        Report report;
        report.getOfftime(this->getPersonalNumber(), hours);
    }
    else
    {
        cout << "You will have " << offTimePerMonth - offTimeHours << " allowed hours for getting offtime!" << endl;
    }
}

void Employee::overtimeReq()
{
    cout << "How many hours do you want to work more this month ? ";
    int hours;
    cin >> hours;

    if (overTimeHours + hours < overTimePerMonth)
    {
        overTimeHours += hours;

        cout << setprecision(1);
        cout << fixed << endl;
        overallSalary += ((overTimeHours + hours) * salaryIncrease);
        cout << "Yor overall salary will be : " << overallSalary << " after these overtimes!" << endl;
    }
    else
    {
        throw aboveOverTimeRequestEx();
    }
}

void Employee::showCustomerInfoByNationalID(string nationalCode)
{
    bool customerExist = false;
    for (size_t i = 0; i < bank->getCustomers()->size(); i++)
    {
        if (nationalCode == bank->getCustomers()->at(i).getNationalCode())
        {
            customerExist = true;
            bank->getCustomers()->at(i).showPersonalInfo();
        }
    }

    if (customerExist == false)
    {
        cerr << "Customer not found with this national code" << endl;
    }
}
void Employee::activateAccount(string accountID)
{
    for (size_t i = 0; i < bank->allAccounts->size(); i++)
    {
        if (accountID == bank->allAccounts->at(i).accountID)
        {
            if (bank->allAccounts->at(i).isActive)
                std::cerr << "Account is already active" << std::endl;
            else
                bank->allAccounts->at(i).isActive = true;
        }
    }
}

void Employee::deactivateAccount(string accountID)
{
    for (size_t i = 0; i < bank->allAccounts->size(); i++)
    {
        if (accountID == bank->allAccounts->at(i).accountID)
        {
            if (bank->allAccounts->at(i).isActive)
            {
                bank->allAccounts->at(i).isActive = false;
                Report report;
                report.deactivated(bank->getAllAccounts()->at(i).getNationalCode(), bank->getAllAccounts()->at(i).getAccountID());
            }
            else
                std::cerr << "Account is already NOT active" << std::endl;
        }
    }
}

void Employee::createNewCustomer(string nationalCode, double amount)
{
    cout << "Please enter the information : " << endl;
    string firstName, lastName, birthDate, username, password;

    while (true)
    {
        firstName = inputFirstname();
        lastName = inputLastname();

        bool customerExist = false;
        try
        {
            for (size_t i = 0; i < bank->getCustomers()->size(); i++)
            {
                if (firstName == bank->getCustomers()->at(i).getFirstName() && lastName == bank->getCustomers()->at(i).getLastName())
                {
                    customerExist = true;
                    throw customerExistEx();
                }
            }
        }
        catch (const customerExistEx &e)
        {
            std::cerr << e.what() << '\n';
        }

        if (customerExist == false)
        {

            break;
        }
    }

    birthDate = inputBirthdate();

    while (true)
    {
        username = inputUsername();
        bool usernameExist = false;
        try
        {
            for (size_t i = 0; i < bank->getCustomers()->size(); i++)
            {
                if (username == bank->getCustomers()->at(i).getUsername())
                {
                    usernameExist = true;
                    throw usernameExistEx();
                }
            }
        }
        catch (const usernameExistEx &e)
        {
            std::cerr << e.what() << '\n';
        }

        if (usernameExist == false)
        {
            break;
        }
    }
    password = inputPassword();

    Customer customer(firstName, lastName, nationalCode, birthDate, username, password, bank);
    bank->customers->push_back(customer);

    cout << "Customer \"" << firstName << " " << lastName << "\" added successfuly" << endl;
    Report report;

    Account account(generateAccountID(), nationalCode, report.todayDate(), amount, 1, 0, 0);
    bank->getAllAccounts()->push_back(account);

    report.newCustomer(nationalCode);
}

void Employee::deleteCustomer(string nationalCode)
{
    for (size_t i = 0; i < bank->getCustomers()->size(); i++)
    {
        if (bank->getCustomers()->at(i).getNationalCode() == nationalCode)
        {
            vector<Customer>::iterator it;
            it = bank->getCustomers()->begin() + i;
            bank->getCustomers()->erase(it);
        }
    }
}

void Employee::createAccount(string nationalCode)
{
    while (true)
    {
        double balance;
        cout << "Balance (Should be more than 50000): ";
        cin >> balance;

        bool customerExist = false;
        if (balance > 50000)
        {
            for (size_t i = 0; i < bank->getCustomers()->size(); i++)
            {
                if (nationalCode == bank->getCustomers()->at(i).getNationalCode())
                {
                    customerExist = true;
                    Report report;
                    Account account(generateAccountID(), bank->getCustomers()->at(i).getNationalCode(), report.todayDate(), balance, 1, 0, 0);
                    bank->getAllAccounts()->push_back(account);
                }
            }

            if (customerExist)
            {
                break;
            }
            else
            {
                createNewCustomer(nationalCode, balance);
                break;
            }
        }
        else
        {
            cerr << "Min balance should be more than 50000 for creating new account" << endl;
        }
    }
}

void Employee::deleteAccount()
{
    string nCode = inputNationalCode();
    for (size_t i = 0; i < bank->getAllAccounts()->size(); i++)
    {
        if (nCode == bank->getAllAccounts()->at(i).getNationalCode())
        {
            vector<Account>::iterator it;
            it = bank->allAccounts->begin() + i;
            bank->getAllAccounts()->erase(it);

            cout << "Account deleted successfully" << endl;
            Report report;
            report.deleteAccount(nCode);

            bool anotherAccount = false;
            for (size_t j = 0; j < bank->getAllAccounts()->size(); j++)
            {
                if (nCode == bank->getAllAccounts()->at(j).getNationalCode())
                {
                    anotherAccount = true;
                }
            }
            if (anotherAccount == false)
            {
                deleteCustomer(nCode);
            }
        }
    }
}

// non-member functions
string inputFirstname()
{
    cout << "First name :";
    string firstName;
    cin >> firstName;
    return firstName;
}
string inputLastname()
{
    cout << "Last name :";
    string lastName;
    cin >> lastName;
    return lastName;
}

string inputBirthdate()
{
    cout << "Birthdate :";
    string birthdate;
    cin >> birthdate;
    return birthdate;
}

string inputNationalCode()
{
    cout << "National code :";
    string nCode;
    cin >> nCode;
    return nCode;
}

string inputUsername()
{
    cout << "Username :";
    string userName;
    cin >> userName;
    return userName;
}

string inputPassword()
{
    cout << "Password :";
    string password;
    cin >> password;
    return password;
}

// implement personal number

double inputBasicSalary()
{
    cout << "Basic Salary : ";
    double basicSalary;
    cin >> basicSalary;
    return basicSalary;
}

string generateAccountID()
{
    srand(time(0));
    int accountID = rand() % 999999999;
    string number = to_string(accountID);
    number = number.substr(0, 8);

    return number;
}

int generatePersonalNum()
{
    srand(time(0));
    int personalNum = rand() % 999;

    return personalNum;
}
