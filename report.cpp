#include <fstream>
#include <iomanip>
#include "report.h"
#include "date.h"

void Report::customerLogin(string nationalCode)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Customer with national code " << nationalCode << " login" << endl;
    fapp.close();
}
void Report::employeeLogin(int personalNumber)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Employee with personal number " << personalNumber << " login" << endl;
    fapp.close();
}
void Report::newCustomer(string nationalCode)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] New customer with national code " << nationalCode << " created" << endl;
    fapp.close();
}
void Report::deleteAccount(string nationalCode)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Account with national code " << nationalCode << " deleted" << endl;
    fapp.close();
}

void Report::deposit(string nationalCode, double amount)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << setprecision(0);
    fapp << fixed;
    fapp << "[" << todayDate() << " " << now() << "] Deposit " << amount << " to Account with national code " << nationalCode << endl;
    fapp.close();
}
void Report::withdrawal(string nationalCode, double amount)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << setprecision(0);
    fapp << fixed;
    fapp << "[" << todayDate() << " " << now() << "] Withrawal " << amount << " from Account with national code " << nationalCode << endl;
    fapp.close();
}
void Report::getLoan(string nationalCode, double value)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << setprecision(0);
    fapp << fixed;
    fapp << "[" << todayDate() << " " << now() << "] Account with national code " << nationalCode << " got " << value << " as loan" << endl;
    fapp.close();
}
void Report::getOfftime(int personalNumber, int hours)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Employee with personal number " << personalNumber << " got " << hours << " hours as offtimes" << endl;
    fapp.close();
}
void Report::changePassword(string firstname, string lastname, string nationalCode)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Password of account with national code " << nationalCode << " changed " << endl;
    fapp.close();
}
void Report::loanWithdrawal(string nationalCode, double value)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Withdrawal installment with value " << value << " for account with national code " << nationalCode << endl;
    fapp.close();
}
void Report::deactivated(string nationalCode, string accountID)
{
    fstream fapp;
    fapp.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/dailyReport.txt", ios::app);
    fapp << "[" << todayDate() << " " << now() << "] Account with national code " << nationalCode << " and " << accountID << " as account id has been deactivated" << endl;
    fapp.close();
}

void Report::updateDate()
{
    Date date = str_to_date(todayDate());
    date.inc_one_day();
    cout << date << endl;
    fstream fout;
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/date.txt", ios::out);
    fout << date;
    fout.close();
}

string Report::todayDate()
{
    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/date.txt", ios::in);
    string today;
    getline(fin, today);
    fin.close();

    return today;
}

string Report::now()
{
    time_t now = time(0);
    // convert now to string form
    tm *ltm = localtime(&now);

    fstream fout;
    fout.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/now.txt", ios::out);

    fout << ltm->tm_hour << ":";
    fout << ltm->tm_min << ":";
    fout << ltm->tm_sec << endl;

    fout.close();

    fstream fin;
    fin.open("/home/atila/Dropbox/BankingManagementSystemProject/DataBase/now.txt", ios::in);
    string time;
    getline(fin, time);
    fin.close();

    return time;
}
