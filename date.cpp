#include <iostream>
#include "date.h"

using namespace std;

int Date::getDay() { return day; }
int Date::getMonth() { return month; }
int Date::getYear() { return year; }


int Date::compare(Date d2)
{
    int num = 0;
    if (year > d2.year || month > d2.month || day > d2.day)
    {
        num = 1;
    }
    else if (d2.year > year || d2.month > month || d2.day > day)
    {
        num = -1;
    }

    return num;
}

Date::Date(int d, int m, int y)
{
    // constructor
    set_date(d, m, y);
}
Date::Date()
{
    // default constructor
    set_date(1, 1, 1390);
}

bool is_leap_year(int year)
{
    int r = year % 33;
    return r == 1 || r == 5 || r == 9 || r == 13 || r == 17 || r == 22 || r == 26 || r == 30;
}

int max_day_for_month(int m, int y)
{
    if (m < 7)
        return 31;
    else if (m < 12)
        return 30;
    else if (m == 12)
        return is_leap_year(y) ? 30 : 29;
    else
        abort();
}

void Date::inc_one_day()
{
    day++;
    if (day > max_day_for_month(month, year))
    {
        day = 1;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
}

void Date::set_date(int d, int m, int y)
{
    if (y < 0 || m < 1 || m > 12 || d < 1 || d > max_day_for_month(m, y))
        abort();

    day = d;
    month = m;
    year = y;
}

void Date::print_date()
{
    // baraye chape tarikh
    cout << day << '/' << month << '/' << year << endl;
}

bool Date::equals(Date d)
{
    // moghaieseye 2 tarikh
    return day == d.day && month == d.month && year == d.year;
}

ostream &operator<<(ostream &os , Date &date)
{
    os << date.day << '/' << date.month << '/' << date.year;
    return os;
}

istream &operator>>(istream &is , Date &date)
{
    cout << "Date: ";
    is >> date.day;
    cout << "Month: ";
    is >> date.month;
    cout << "Year: ";
    is >> date.year;
    return is;
}

int days_between(Date d1, Date d2)
{
    int count = 1;
    switch (d1.compare(d2))
    {
    case 1:
        while (!d2.equals(d1))
        {
            d2.inc_one_day();
            count++;
        }
        break;
    case -1:
        while (!d1.equals(d2))
        {
            d1.inc_one_day();
            count++;
        }

        break;
    case 0:
        count = 0;
        break;
    }

    return count;
}


Date str_to_date(string s)
{
    // TODO: Handle formatting errors
    int slash_pos = s.find('/');           // 3/12/1394 => slash_pos=1
    int d = stoi(s.substr(0, slash_pos));  //=> d=3
    s = s.substr(slash_pos + 1);           //=>s=12/1394
    slash_pos = s.find('/');               //=>slash_pos=2
    int m = stoi(s.substr(0, slash_pos));  //=>m=12
    int y = stoi(s.substr(slash_pos + 1)); //=>y=1394

    return Date(d, m, y);
}
