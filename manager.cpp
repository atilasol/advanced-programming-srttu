#include <iostream>
#include "manager.h"
#include "bank.h"
#include "date.h"

class employeeExistException
{
};
class usernameExistException
{
};

Manager::Manager(string type, string fName, string lName, Date bDate, string uName, string pass, int pNumber, double bSalary, double offH, double overH, Bank *b)
    : Employee(type, fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH, b)
{
}

void Manager::showEmployeeByPersonalNumber(int personalNumber)
{
    for (size_t i = 0; i < bank->employees->size(); i++)
    {
        if (personalNumber == bank->employees->at(i).getPersonalNumber())
        {
            bank->employees->at(i).showPersonalInfo();
            break;
        }
    }
}
void Manager::hireEmployee()
{
    cout << "Please enter the information" << endl;
    string firstName;
    string lastName;
    Date birthDate;
    string username;
    string password;
    int personalNumber;
    double basicSalary;

    while (true)
    {
        firstName = getFirstName();
        lastName = getLastName();

        for (size_t i = 0; i < bank->employees->size(); i++)
        {
            if (firstName == bank->employees->at(i).getFirstName() && lastName == bank->employees->at(i).getLastName())
            {
                throw employeeExistException();
            }
        }
        break;
    }

    birthDate = getBirthDate();

    while (true)
    {
        username = getUserName();
        for (size_t i = 0; i < bank->employees->size(); i++)
        {
            if (username == bank->employees->at(i).getUsername())
            {
                throw usernameExistException();
            }
        }
        break;
    }
    password = getPassword();
    // implemtn personal number
    basicSalary = getBasicSalary();
}

// non-member functions
string getFirstName()
{
    cout << "First name :";
    string firstName;
    getline(cin, firstName);
    return firstName;
}
string getLastName()
{
    cout << "Last name :";
    string lastName;
    getline(cin, lastName);
    return lastName;
}

Date getBirthDate()
{
    int day, month, year;
    cout << "Day: ";
    cin >> day;
    cout << "Month: ";
    cin >> month;
    cout << "Year: ";
    cin >> year;

    return Date(day, month, year);
}

string getUserName()
{
    cout << "Username :";
    string userName;
    getline(cin, userName);
    return userName;
}

string getPassword()
{
    cout << "Password :";
    string password;
    getline(cin, password);
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