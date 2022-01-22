#include "employee.h"

class aboveOverTimeRequestException
{
};

Employee::Employee(string type ,string fName, string lName, Date bDate, string uName, string pass, int pNumber, double bSalary, double offH, double overH, Bank *b)
    : firstName{fName}, lastName{lName}, personalNumber{pNumber}, birthDate{bDate}, username{uName}, password{pass}, basicSalary{bSalary}, offTimeHours{offH}, overTimeHours{overH}
{
    this->bank = b;
    employeeType = type;
    overallSalary = basicSalary;
}

void Employee::showPersonalInfo()
{
    cout << "=== Username : " << username << " ==========" << endl;
    cout << "Name : " << firstName << " " << lastName << endl;
    cout << "Birth date :" << birthDate << " | Personal Number : " << personalNumber << endl;
    cout << "============================================" << endl;
}

string Employee::getFirstName() { return firstName; }
string Employee::getLastName() { return lastName; }
int Employee::getPersonalNumber() { return personalNumber; }
string Employee::getUsername() { return username; }
string Employee::getPassword() { return password; }
string Employee::getEmployeeType() { return employeeType; }

void Employee::offTimeReq()
{
    cout << "How many hours do you want for your offtime ? ";
    int hours;
    cin >> hours;
    offTimeHours += hours;

    if (offTimeHours > offTimePerMonth)
    {
        overallSalary -= ((offTimeHours - offTimePerMonth) * salaryReduction);
        cout << "Yor overall salary will be : " << overallSalary << " after these offtimes!" << endl;
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
        overallSalary += ((overTimeHours + hours) * salaryIncrease);
        cout << "Yor overall salary will be : " << overallSalary << " after these overtimes!" << endl;
    }
    else
    {
        throw aboveOverTimeRequestException();
    }
}

void Employee::showCustomerInfoByNationalID(string nationalCode)
{
    for (size_t i = 0; i < bank->customers->size(); i++)
    {
        if (nationalCode == bank->customers->at(i).nationalCode)
        {
            bank->customers->at(i).showAccountsInfo();
        }
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
                bank->allAccounts->at(i).isActive = true;
            else
                std::cerr << "Account is already NOT active" << std::endl;
        }
    }
}