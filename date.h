#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Date
{
    friend ostream &operator<<(ostream &os , Date &date);
    friend istream &operator>>(istream &is , Date &date);
public:
    Date(int d, int m, int y);
    Date();
    void set_date(int d, int m, int y);
    void print_date();
    bool equals(Date d);
    int compare(Date d2);

    int getDay();
    int getMonth();
    int getYear();
    void inc_one_day();

private:
    int day;
    int month;
    int year;
};

int days_between(Date d1, Date d2);
Date str_to_date(string s);



#endif // DATE_H
