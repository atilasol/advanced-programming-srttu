#include "manager.h"

string inputFirstname();
string inputLastname();
string inputBirthdate();
string inputNationalCode();
string inputUsername();
string inputPassword();
double getBasicSalary();

class employeeExistException
{
};
class usernameExistException
{
};

Manager::Manager(string fName, string lName, string bDate, string uName, string pass, int pNumber, double bSalary, double offH, double overH, Bank *b)
    : Employee(fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH, b)
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

    birthDate = inputBirthdate();

    while (true)
    {
        username = inputUsername();
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
                // bank->getEmployees()->erase();

                // Shifting elements
                for (size_t j = i; j < bank->getEmployees()->size() - 1; j++)
                {
                    bank->getEmployees()->at(j) = bank->getEmployees()->at(j + 1);
                }
                bank->getEmployees()->at(bank->getEmployees()->size() - 2) = bank->getEmployees()->at(bank->getEmployees()->size() - 1);
                bank->getEmployees()->pop_back();
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
