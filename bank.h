#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <vector>
#include "customer.h"
#include "employee.h"
#include "facilityemployee.h"
#include "manager.h"
#include "account.h"
#include "loan.h"
#include "date.h"

class Employee;
class Manager;
class FacilityEmployee;
class Account;

using namespace std;

class Bank
{
    friend class Employee;
    friend class Manager;

protected:
    vector<Customer> *customers;
    vector<Account> *allAccounts;
    vector<Employee> *employees;
    vector<Loan> *loans;
    vector<Loan> *loanRequests;
    vector<Manager> *manager;
    vector<FacilityEmployee> *fEmployee;
    string branchName;
    string branchCode;

public:
    Bank(string bName, string bCode);
    ~Bank();

    vector<Employee> *getEmployees();
    vector<Customer> *getCustomers();
    vector<Account> *getAllAccounts();
    vector<Loan> *getLoans();
    vector<Loan> *getLoanReqs();
    vector<Manager> *getManager();
    vector<FacilityEmployee> *getFacilityEmployee();
    // Read from db
    void readCustomers();
    void readEmployees();
    void readAccounts();
    void readLoan();
    void readManager();
    void readFacilityEmployee();
    // write into db
    void writeCustomers();
    void writeEmployees();
    void writeAccounts();
    void writeLoans();
    void writeManager();
    void writeFacilityEmployee();

    string todayDate();

    void dailyReporting();
};

#endif // BANK_H
