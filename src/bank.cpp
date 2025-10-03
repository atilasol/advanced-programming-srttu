#include <iostream>
#include <iomanip>
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
    numOfComponents = new vector<int>;

    readNumOfComponents();
    readCustomers();
    readEmployees();
    readFacilityEmployee();
    readManager();
    readAccounts();
    readLoan();
    readLoanReqs();
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
    delete[] numOfComponents;
}

vector<Employee> *Bank::getEmployees() { return employees; }
vector<Customer> *Bank::getCustomers() { return customers; }
vector<Account> *Bank::getAllAccounts() { return allAccounts; }
vector<Loan> *Bank::getLoans() { return loans; }
vector<Loan> *Bank::getLoanReqs() { return loanRequests; }
vector<Manager> *Bank::getManager() { return manager; }
vector<FacilityEmployee> *Bank::getFacilityEmployee() { return fEmployee; }

// read from db
void Bank::readNumOfComponents()
{
    fstream fin;
    fin.open("data/numOfComponents.txt", ios::in);

    int nCusomers, nEmployees, nAccounts, nLoans, nLoanReqs;
    fin >> nCusomers >> nEmployees >> nAccounts >> nLoans >> nLoanReqs;

    numOfComponents->push_back(nCusomers);
    numOfComponents->push_back(nEmployees);
    numOfComponents->push_back(nAccounts);
    numOfComponents->push_back(nLoans);
    numOfComponents->push_back(nLoanReqs);

    fin.close();
}

void Bank::readCustomers()
{
    fstream fin;
    fin.open("data/customers.txt", ios::in);

    for (size_t i = 0; i < numOfComponents->at(0); i++)
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
    fin.open("data/employees.txt", ios::in);

    for (size_t i = 0; i < numOfComponents->at(1); i++)
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

        Employee employee(fName, lName, bDate, uName, pass, stoi(pNumber), stod(bSalary), stod(offH), stod(overH), this);
        employees->push_back(employee);
    }

    fin.close();
}

void Bank::readAccounts()
{
    fstream fin;
    fin.open("data/accounts.txt", ios::in);

    for (size_t i = 0; i < numOfComponents->at(2); i++)
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
    fstream fin;
    fin.open("data/loans.txt", ios::in);

    for (size_t i = 0; i < numOfComponents->at(3); i++)
    {
        string accID, serialNum, date, amount, numOfIns, numOfPaidIns, numOfOverdue, numOfWar;
        getline(fin, accID, '-');
        getline(fin, serialNum, '-');
        getline(fin, date, '-');
        getline(fin, amount, '-');
        getline(fin, numOfIns, '-');
        getline(fin, numOfPaidIns, '-');
        getline(fin, numOfOverdue, '-');
        getline(fin, numOfWar);

        Loan loan(accID, serialNum, date, stod(amount), stoi(numOfIns), stoi(numOfPaidIns), stoi(numOfOverdue), stoi(numOfWar));
        loans->push_back(loan);
    }

    fin.close();
}

void Bank::readLoanReqs()
{
    fstream fin;
    fin.open("data/loanReqs.txt", ios::in);

    for (size_t i = 0; i < numOfComponents->at(4); i++)
    {
        string accID, date, amount, numOfIns;
        getline(fin, accID, '-');
        getline(fin, date, '-');
        getline(fin, amount, '-');
        getline(fin, numOfIns);

        Loan loan(accID, date, stod(amount), stoi(numOfIns));
        loanRequests->push_back(loan);
    }

    fin.close();
}
void Bank::readManager()
{
    fstream fin;
    fin.open("data/manager.txt", ios::in);

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

    Manager boss(fName, lName, bDate, uName, pass, stoi(pNumber), stod(bSalary), stod(offH), stod(overH), this);
    manager->push_back(boss);
    fin.close();
}

void Bank::readFacilityEmployee()
{
    fstream fin;
    fin.open("data/facilityemployee.txt", ios::in);

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

    FacilityEmployee fEmp(fName, lName, bDate, uName, pass, stoi(pNumber), stod(bSalary), stod(offH), stod(overH), this);
    fEmployee->push_back(fEmp);

    fin.close();
}
// write into db
void Bank::writeNumOfComponents()
{
    fstream fout;
    fout.open("data/numOfComponents.txt", ios::out);
    fout << getCustomers()->size() << " ";
    fout << getEmployees()->size() << " ";
    fout << getAllAccounts()->size() << " ";
    fout << getLoans()->size() << " ";
    fout << getLoanReqs()->size();

    fout.close();
}

void Bank::writeCustomers()
{
    fstream fout;
    fout.open("data/customers.txt", ios::out);

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
    fout.open("data/employees.txt", ios::out);

    for (size_t i = 0; i < employees->size(); i++)
    {
        fout << employees->at(i).firstName << "-";
        fout << employees->at(i).lastName << "-";
        fout << employees->at(i).birthDate << "-";
        fout << employees->at(i).username << "-";
        fout << employees->at(i).password << "-";
        fout << employees->at(i).personalNumber << "-";
        fout << setprecision(1);
        fout << fixed;
        fout << employees->at(i).basicSalary << "-";
        fout << employees->at(i).offTimeHours << "-";
        fout << employees->at(i).overTimeHours << endl;
    }
    fout.close();
}
void Bank::writeAccounts()
{
    fstream fout;
    fout.open("data/accounts.txt", ios::out);

    for (size_t i = 0; i < allAccounts->size(); i++)
    {
        fout << allAccounts->at(i).accountID << "-";
        fout << allAccounts->at(i).nationalCode << "-";
        fout << allAccounts->at(i).accountOpeningDate << "-";
        fout << setprecision(1);
        fout << fixed;
        fout << allAccounts->at(i).balance << "-";
        fout << allAccounts->at(i).isActive << "-";
        fout << allAccounts->at(i).loanReqPotential << "-";
        fout << allAccounts->at(i).daysMoreThanMinBalance << endl;
    }
    fout.close();
}

void Bank::writeLoans()
{
    fstream fout;
    fout.open("data/loans.txt", ios::out);

    for (size_t i = 0; i < loans->size(); i++)
    {
        fout << loans->at(i).connectedAccountID << "-";
        fout << loans->at(i).serialNumber << "-";
        fout << loans->at(i).dateReceived << "-";
        fout << setprecision(1);
        fout << fixed;
        fout << loans->at(i).amount << "-";
        fout << loans->at(i).totalNumberOfInstallments << "-";
        fout << loans->at(i).numberOfInstallmentsPaid << "-";
        fout << loans->at(i).numberOfOverdueInstallments << "-";
        fout << loans->at(i).numberOfWarnings;
    }

    fout.close();
}

void Bank::writeLoanReqs()
{
    fstream fout;
    fout.open("data/loanReqs.txt", ios::out);

    for (size_t i = 0; i < getLoanReqs()->size(); i++)
    {
        fout << loanRequests->at(i).connectedAccountID << "-";
        fout << loanRequests->at(i).dateReceived << "-";
        fout << setprecision(1);
        fout << fixed;
        fout << loanRequests->at(i).amount << "-";
        fout << loanRequests->at(i).totalNumberOfInstallments << endl;
    }

    fout.close();
}

void Bank::writeManager()
{
    fstream fout;
    fout.open("data/manager.txt", ios::out);

    fout << manager->at(0).firstName << "-";
    fout << manager->at(0).lastName << "-";
    fout << manager->at(0).birthDate << "-";
    fout << manager->at(0).username << "-";
    fout << manager->at(0).password << "-";
    fout << manager->at(0).personalNumber << "-";
    fout << setprecision(1);
    fout << fixed;
    fout << manager->at(0).basicSalary << "-";
    fout << manager->at(0).offTimeHours << "-";
    fout << manager->at(0).overTimeHours << endl;

    fout.close();
}

void Bank::writeFacilityEmployee()
{
    fstream fout;
    fout.open("data/facilityemployee.txt", ios::out);

    fout << fEmployee->at(0).firstName << "-";
    fout << fEmployee->at(0).lastName << "-";
    fout << fEmployee->at(0).birthDate << "-";
    fout << fEmployee->at(0).username << "-";
    fout << fEmployee->at(0).password << "-";
    fout << fEmployee->at(0).personalNumber << "-";
    fout << setprecision(1);
    fout << fixed;
    fout << fEmployee->at(0).basicSalary << "-";
    fout << fEmployee->at(0).offTimeHours << "-";
    fout << fEmployee->at(0).overTimeHours << endl;

    fout.close();
}

void Bank::dailyReporting()
{
    cout << "Updating the database ..." << endl;
    for (size_t i = 0; i < getLoans()->size(); i++)
    {
        for (size_t j = 0; j < getAllAccounts()->size(); j++)
        {
            if (getLoans()->at(i).getAccountID() == getAllAccounts()->at(j).getAccountID())
            {
                if (getLoans()->at(i).getNumberOfInstallments() > getLoans()->at(i).getNumberOfPaidInstallments())
                {
                    if (getAllAccounts()->at(j).getBalance() > getLoans()->at(i).getAmountOfEachInstallment())
                    {
                        getAllAccounts()->at(j).withdraw(getLoans()->at(i).getAmountOfEachInstallment());
                    }
                    else
                    {
                        if (getLoans()->at(i).getNumberOfWarnings() == 0)
                        {
                            getLoans()->at(i).setWarning();
                            getLoans()->at(i).numberOfOverdueInstallments++;
                            cerr << "Warning sent to the customer successfuly" << endl;
                        }
                        else if (getLoans()->at(i).getNumberOfWarnings() == 1)
                        {
                            getLoans()->at(i).setWarning();
                            getLoans()->at(i).numberOfOverdueInstallments++;
                            cerr << "Deactivating all the accounts of  customer with national code " << getAllAccounts()->at(j).getNationalCode() << endl;
                            for (size_t k = 0; k < getAllAccounts()->size(); k++)
                            {
                                // deactivating accounts
                                Employee employee;
                                employee.deactivateAccount(getAllAccounts()->at(k).getAccountID());
                            }
                        }
                    }
                }
            }
        }
    }

    writeNumOfComponents();
    writeCustomers();
    cout << "Update customers db successfully" << endl;
    writeEmployees();
    cout << "Update employees db successfully" << endl;
    writeAccounts();
    cout << "Update accounts db successfully" << endl;
    writeLoans();
    cout << "Update loans db successfully" << endl;
    writeManager();
    cout << "Update manager db successfully" << endl;
    writeFacilityEmployee();
    cout << "Update facility employee db successfully" << endl;
    writeLoanReqs();
    cout << "Update loan requests db successfully" << endl;
}
