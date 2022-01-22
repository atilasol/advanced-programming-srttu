#include <fstream>
#include <string>
#include <sstream>
#include "date.h"
#include "bank.h"

// constructor
Bank::Bank(string bName, string bCode)
    : branchName{bName}, branchCode{bCode}
{
    customers = new vector<Customer>();
    employees = new vector<Employee>();
    allAccounts = new vector<Account>();
    loans = new vector<Loan>();
}

// destructor
Bank::~Bank()
{
    delete[] customers;
    delete[] employees;
    delete[] allAccounts;
    delete[] loans;
}

vector<Employee> *Bank::getEmployees() { return employees; }
vector<Customer> *Bank::getCustomers() { return customers; }
vector<Account> *Bank::getAllAccounts() { return allAccounts; }
vector<Loan> *Bank::getLoans() { return loans; }

// read from db
void Bank::readCustomers()
{
    fstream fin;
    fin.open("./Bank/customers.txt", ios::in);

    while (!fin.eof())
    {
        string fName, lName, ID, bDate, uName, pass;
        getline(fin, fName, '-');
        getline(fin, lName, '-');
        getline(fin, ID, '-');
        getline(fin, bDate, '-');
        getline(fin, uName, '-');
        getline(fin, pass);

        Customer customer(fName, lName, ID, str_to_date(bDate), uName, pass, this);
        customers->push_back(customer);
    }

    fin.close();
}
void Bank::readEmployees()
{
    fstream fin;
    fin.open("./Bank/employees.txt", ios::in);

    while (!fin.eof())
    {
        string type ,fName, lName, bDate, uName, pass, pNumber, bSalary , offH , overH;

        getline(fin , type , '-');
        getline(fin, fName, '-');
        getline(fin, lName, '-');
        getline(fin, bDate, '-');
        getline(fin, uName, '-');
        getline(fin, pass, '-');
        getline(fin, uName, '-');
        getline(fin, pass, '-');
        getline(fin, pNumber, '-');
        getline(fin, bSalary) , '-';
        getline(fin, offH, '-');
        getline(fin, overH);

        Employee employee(type , fName, lName, str_to_date(bDate), uName, pass, stoi(pNumber), stod(bSalary) , stod(offH) , stod(overH), this);
        employees->push_back(employee);
    }

    fin.close();
}
void Bank::readAccounts()
{
    fstream fin;
    fin.open("./Bank/accounts.txt", ios::in);

    while (!fin.eof())
    {
        string aID, nID, date, balance, isActive, lPotential, daysForReq;

        getline(fin, aID, '-');
        getline(fin, nID, '-');
        getline(fin, date, '-');
        getline(fin, balance, '-');
        getline(fin, isActive, '-');
        getline(fin, lPotential, '-');
        getline(fin, daysForReq);

        bool isA, lP;
        istringstream(isActive) >> isA;
        istringstream(lPotential) >> lP;

        Account account(aID, nID, str_to_date(date), stod(balance), isA, lP, stoi(daysForReq));
        allAccounts->push_back(account);
    }

    fin.close();
}

// void readLoan();

// write into db
void Bank::writeCustomers()
{
    fstream fout;
    fout.open("./Bank/customers.txt", ios::out);

    for (size_t i = 0; i < customers->size(); i++)
    {
        fout << customers->at(i).firstName << "-";
        fout << customers->at(i).lastName << "-";
        fout << customers->at(i).nationalCode << "-";
        fout << customers->at(i).birthDate << "-";
        fout << customers->at(i).username << "-";
        fout << customers->at(i).password << endl;
    }
    fout.close();
}
void Bank::writeEmployees()
{
    fstream fout;
    fout.open("./Bank/employees.txt", ios::out);

    for (size_t i = 0; i < employees->size(); i++)
    {
        fout << employees->at(i).employeeType << "-";
        fout << employees->at(i).firstName << "-";
        fout << employees->at(i).lastName << "-";
        fout << employees->at(i).birthDate << "-";
        fout << employees->at(i).username << "-";
        fout << employees->at(i).password << "-";
        fout << employees->at(i).personalNumber << "-";
        fout << employees->at(i).basicSalary << endl;
    }
    fout.close();
}
void Bank::writeAccounts()
{
    fstream fout;
    fout.open("./Bank/accounts.txt", ios::out);

    for (size_t i = 0; i < allAccounts->size(); i++)
    {
        fout << allAccounts->at(i).accountID << "-";
        fout << allAccounts->at(i).nationalCode << "-";
        fout << allAccounts->at(i).accountOpeningDate << "-";
        fout << allAccounts->at(i).balance << "-";
        fout << allAccounts->at(i).isActive << "-";
        fout << allAccounts->at(i).loanReqPotential << "-";
        fout << allAccounts->at(i).daysMoreThanMinBalance << endl;
    }
    fout.close();
}

// void writeLoans();

void Bank::dailyReporting()
{
    writeCustomers();
    writeEmployees();
    writeAccounts();
    writeLoans();
}

string Bank::todayDate()
{
    fstream fin;
    fin.open("/DataBase/time.txt" , ios::in);
    string today;
    getline(fin , today);
    fin.close();

    return today;
}