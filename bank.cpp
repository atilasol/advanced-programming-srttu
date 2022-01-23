#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "bank.h"

using namespace std;

// constructor
Bank::Bank(string bName, string bCode)
    : branchName{bName}, branchCode{bCode}
{
    customers = new vector<Customer>;
    employees = new vector<Employee>;
    allAccounts = new vector<Account>;
    manager = new vector<Manager>;
    fEmployee = new vector<FacilityEmployee>;
    loans = new vector<Loan>;
    loanRequests = new vector<Loan>;

    readCustomers();
    readEmployees();
    readFacilityEmployee();
    readManager();
    readAccounts();
    readLoan();
}

// destructor
Bank::~Bank()
{
    delete[] customers;
    delete[] employees;
    delete[] allAccounts;
    delete[] loans;
    delete[] loanRequests;
    delete[] manager;
    delete[] fEmployee;
}

vector<Employee> *Bank::getEmployees() { return employees; }
vector<Customer> *Bank::getCustomers() { return customers; }
vector<Account> *Bank::getAllAccounts() { return allAccounts; }
vector<Loan> *Bank::getLoans() { return loans; }
vector<Loan> *Bank::getLoanReqs() { return loanRequests; }
vector<Manager> *Bank::getManager() { return manager; }
vector<FacilityEmployee> *Bank::getFacilityEmployee() { return fEmployee; }

// read from db
void Bank::readCustomers()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/customers.txt", ios::in);

    while (!fin.eof())
    {
        string fName, lName, ID, bDate, uName, pass;
        getline(fin, fName, '-');
        getline(fin, lName, '-');
        getline(fin, ID, '-');
        getline(fin, bDate, '-');
        getline(fin, uName, '-');
        getline(fin, pass);

        Customer customer(fName, lName, ID, bDate, uName, pass, this);
        customers->push_back(customer);
    }

    fin.close();
}
void Bank::readEmployees()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/employees.txt", ios::in);
    int numberOfEmployees;
    fin >> numberOfEmployees;

    for (size_t i = 0; i < numberOfEmployees; i++)
    {
        string fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH;

        getline(fin, fName, '-');
        getline(fin, lName, '-');
        getline(fin, bDate, '-');
        getline(fin, uName, '-');
        getline(fin, pass, '-');
        getline(fin, pNumber, '-');
        getline(fin, bSalary, '-');
        getline(fin, offH, '-');
        getline(fin, overH);

        Employee employee(fName, lName, bDate, uName, pass, stod(pNumber), stod(bSalary), stod(offH), stod(overH), this);
        employees->push_back(employee);
    }

    fin.close();
}
void Bank::readAccounts()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/accounts.txt", ios::in);

    int numberOfAccounts;
    fin >> numberOfAccounts;

    for (size_t i = 0; i < numberOfAccounts; i++)
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

        Account account(aID, nID, date, stod(balance), isA, lP, stoi(daysForReq));
        allAccounts->push_back(account);
    }

    fin.close();
}

void Bank::readLoan()
{
}
void Bank::readManager()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/manager.txt", ios::in);

    string fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH;

    getline(fin, fName, '-');
    getline(fin, lName, '-');
    getline(fin, bDate, '-');
    getline(fin, uName, '-');
    getline(fin, pass, '-');
    getline(fin, pNumber, '-');
    getline(fin, bSalary, '-');
    getline(fin, offH, '-');
    getline(fin, overH);

    Manager boss(fName, lName, bDate, uName, pass, stod(pNumber), stod(bSalary), stod(offH), stod(overH), this);
    manager->push_back(boss);
    fin.close();
}

void Bank::readFacilityEmployee()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/facilityemployee.txt", ios::in);

    string fName, lName, bDate, uName, pass, pNumber, bSalary, offH, overH;

    getline(fin, fName, '-');
    getline(fin, lName, '-');
    getline(fin, bDate, '-');
    getline(fin, uName, '-');
    getline(fin, pass, '-');
    getline(fin, pNumber, '-');
    getline(fin, bSalary, '-');
    getline(fin, offH, '-');
    getline(fin, overH);

    FacilityEmployee fEmp(fName, lName, bDate, uName, pass, stod(pNumber), stod(bSalary), stod(offH), stod(overH), this);
    fEmployee->push_back(fEmp);

    fin.close();
}
// write into db
void Bank::writeCustomers()
{
    fstream fout;
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/customers.txt", ios::out);

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
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/employees.txt", ios::out);

    for (size_t i = 0; i < employees->size(); i++)
    {
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
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/accounts.txt", ios::out);

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

void Bank::writeLoans()
{
}
void Bank::writeManager()
{
    fstream fout;
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/manager.txt", ios::out);

    fout << manager->at(0).firstName << "-";
    fout << manager->at(0).lastName << "-";
    fout << manager->at(0).birthDate << "-";
    fout << manager->at(0).username << "-";
    fout << manager->at(0).password << "-";
    fout << manager->at(0).personalNumber << "-";
    fout << manager->at(0).basicSalary << endl;

    fout.close();
}

void Bank::writeFacilityEmployee()
{
    fstream fout;
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/facilityemployee.txt", ios::out);

    fout << fEmployee->at(0).firstName << "-";
    fout << fEmployee->at(0).lastName << "-";
    fout << fEmployee->at(0).birthDate << "-";
    fout << fEmployee->at(0).username << "-";
    fout << fEmployee->at(0).password << "-";
    fout << fEmployee->at(0).personalNumber << "-";
    fout << fEmployee->at(0).basicSalary << endl;

    fout.close();
}

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
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/time.txt", ios::in);
    string today;
    getline(fin, today);
    fin.close();

    return today;
}
