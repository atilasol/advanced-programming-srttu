#include <iomanip>
#include "bank.h"

string inputFirstname();
string inputLastname();
string inputBirthdate();
string inputNationalCode();
string inputUsername();
string inputPassword();
double getBasicSalary();

class aboveOverTimeRequestException
{
};
class customerExistException
{
};
class usernameExistException
{
};

Employee::Employee(string fName, string lName, string bDate, string uName, string pass, int pNumber, double bSalary, double offH, double overH, Bank *b)
    : firstName{fName}, lastName{lName}, personalNumber{pNumber}, birthDate{bDate}, username{uName}, password{pass}, basicSalary{bSalary}, offTimeHours{offH}, overTimeHours{overH}
{
    cout << setprecision(1);
    cout << fixed << endl;
    this->bank = b;
    overallSalary = basicSalary;
}

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
        throw aboveOverTimeRequestException();
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
                bank->allAccounts->at(i).isActive = true;
            else
                std::cerr << "Account is already NOT active" << std::endl;
        }
    }
}

void Employee::createNewCustomer()
{
    cout << "Please enter the information : " << endl;
    string firstName, lastName, nationalCode, birthDate, username, password;

    while (true)
    {
        firstName = inputFirstname();
        lastName = inputLastname();

        for (size_t i = 0; i < bank->getCustomers()->size(); i++)
        {
            if (firstName == bank->getCustomers()->at(i).getFirstName() && lastName == bank->getCustomers()->at(i).getLastName())
            {
                throw customerExistException();
            }
        }
        break;
    }

    while (true)
    {
        nationalCode = inputNationalCode();

        for (size_t i = 0; i < bank->getCustomers()->size(); i++)
        {
            if (nationalCode == bank->getCustomers()->at(i).getNationalCode())
            {
                throw customerExistException();
            }
        }
        break;
    }

    birthDate = inputBirthdate();

    while (true)
    {
        username = inputUsername();
        for (size_t i = 0; i < bank->getCustomers()->size(); i++)
        {
            if (username == bank->getCustomers()->at(i).getUsername())
            {
                throw usernameExistException();
            }
        }
        break;
    }
    password = inputPassword();

    Customer customer(firstName, lastName, nationalCode, birthDate, username, password, bank);
    bank->customers->push_back(customer);
    cout << "Customer \"" << firstName << " " << lastName << "\" added successfuly" << endl;
}
void Employee::deleteACustomer()
{
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

double getBasicSalary()
{
    cout << "Basic Salary : ";
    double basicSalary;
    cin >> basicSalary;
    return basicSalary;
}
