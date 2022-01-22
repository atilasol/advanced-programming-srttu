#ifndef BANK_H
#define BANK_H

#include <iostream>
#include "customer.h"
#include "employee.h"
#include "manager.h"
#include "account.h"
#include "loan.h"

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
    string branchName;
    string branchCode;
public:
    Bank(string bName, string bCode);
    ~Bank();
    
    vector<Employee> *getEmployees();
    vector<Customer> *getCustomers();
    vector<Account> *getAllAccounts();
    vector<Loan> *getLoans();
    // Read from db
    void readCustomers();
    void readEmployees();
    void readAccounts();
    void readLoan();
    // write into db
    void writeCustomers();
    void writeEmployees();
    void writeAccounts();
    void writeLoans();

    string todayDate();

    void dailyReporting();
};

#endif // BANK_H
