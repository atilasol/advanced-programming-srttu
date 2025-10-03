#include "manager.h"
#include "exceptions/employeeExistEx.h"
#include "exceptions/usernameExistEx.h"

string inputFirstname();
string inputLastname();
string inputBirthdate();
string inputNationalCode();
string inputUsername();
string inputPassword();
double inputBasicSalary();

Manager::Manager(string fName, string lName, string bDate, string uName, string pass, int pNum, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, pNum, bSalary, offH, overH, b)
{
}
Manager::Manager(string fName, string lName, string bDate, string uName, string pass, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, bSalary, offH, overH, b)
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
    string birthDate;
    string username;
    string password;
    int personalNumber;
    double basicSalary;

    while (true)
    {
        firstName = inputFirstname();
        lastName = inputLastname();

        bool nameExist = false;
        try
        {
            for (size_t i = 0; i < bank->employees->size(); i++)
            {
                if (firstName == bank->employees->at(i).getFirstName() && lastName == bank->employees->at(i).getLastName())
                {
                    nameExist = true;
                    throw employeeExistEx();
                }
            }
        }
        catch (const employeeExistEx &e)
        {
            std::cerr << e.what() << '\n';
        }

        if (nameExist == false)
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
            for (size_t i = 0; i < bank->employees->size(); i++)
            {
                if (username == bank->employees->at(i).getUsername())
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
    // implemtn personal number
    basicSalary = inputBasicSalary();

    Employee employee(firstName, lastName, birthDate, username, password, basicSalary, 0, 0, this->bank);
    bank->employees->push_back(employee);
}

void Manager::fireEmployee()
{
    cout << "Enter the personal number: ";
    int pNumber;
    cin >> pNumber;

    for (size_t i = 0; i < bank->getEmployees()->size(); i++)
    {
        if (bank->getEmployees()->at(i).getPersonalNumber() == pNumber)
        {
            bank->getEmployees()->at(i).showPersonalInfo();
            cout << "Fire this employee? ";
            string yesOrno;
            cin >> yesOrno;
            if (yesOrno == "yes")
            {
                vector<Employee>::iterator it;
                it = bank->getEmployees()->begin() + i;
                bank->getEmployees()->erase(it);
            }
            else if (yesOrno == "no")
            {
                break;
            }
            else
            {
                cerr << "Please enter a valid string" << endl;
            }
        }
    }
}
