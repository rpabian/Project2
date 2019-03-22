#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Date;

ostream &operator <<(ostream &, Date &);
istream &operator >>(istream &, Date &);

class Date
{
private:
	int m_month;
	int m_day;
	int m_year;
    int calendar[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	string months[12] = { "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December" };
 public:
	Date(int month, int day, int year)
	{
		validateM(month);
		validateD(day);
		m_year = year;
	}
	Date() { Date(1, 1, 2000); }
	void validateM(int month)
	{
		if (month > 0 && month <= 12)
			m_month = month;
		else
		{
			while (month <= 0 || month > 12)
			{
				cout << "Month: " << month << " is not valid."
					<< " Please input a valid month: ";
				cin >> month;
				cout << endl;
			}
			m_month = month;
		}
	}
	void validateD(int day)
	{
		if (day > 0 && day <= calendar[m_month - 1])
			m_day = day;
		else
		{
			while (day <= 0 || day > calendar[m_month - 1])
			{
				cout << "Day: " << day << " is not valid."
					<< " Please inpt a valid day: ";
				cin >> day;
				cout << endl;
			}
			m_day = day;
		}
	}
	void printDate1()
	{
		cout << m_month << "/" << m_day
			<< "/" << m_year << endl;
	}
	void printDate2()
	{
		cout << months[m_month - 1] << " "
			<< m_day << ", " << m_year << endl;
	}
	void printDate3()
	{
		cout << m_day << " " << months[m_month - 1]
			<< " " << m_year << endl;
	}
	Date operator++()
	{
		++m_day;
		dayAdjust();
		return *this;
	}
	Date operator++(int)
	{
		Date temp(m_month, m_day, m_year);
		m_day++;
		dayAdjust();
		return temp;
	}
	Date operator--()
	{
		--m_day;
		dayAdjust();
		return *this;
	}
	Date operator--(int)
	{
		Date temp(m_month, m_day, m_year);
		m_day--;
		dayAdjust();
		return temp;
	}
	void dayAdjust()
	{
		if (m_day == calendar[m_month - 1] + 1)
		{
			if (m_month == 12)
			{
				m_day = 1;
				m_month = 1;
				++m_year;
			}
			else
			{
				m_day = 1;
				++m_month;
			}
		}
		else if (m_day == 0)
		{
			if (m_month == 1)
			{
				m_day = 31;
				m_month = 12;
				--m_year;
			}
			else
			{
				--m_month;
				m_day = calendar[m_month - 1];
			}
		}
	}
	int operator-(Date &date)
	{
		int days = 0;
		int yearDays = (m_year - date.m_year) * 365;
		int monthDays = 0;
		int numDays = m_day - date.m_day;
		if (m_month > date.m_month)
		{
			for (int i = date.m_month + 1; i <= m_month; i++)
				monthDays += calendar[i - 1];
		}
		else
		{
			for (int i = m_month + 1; i <= date.m_month; i++)
				monthDays += calendar[i - 1];
			monthDays = monthDays * -1;
		}
		days = abs(yearDays + monthDays + numDays);
		return days;
	}
	friend ostream &operator <<(ostream &, Date &);
	friend istream &operator >>(istream &, Date &);
};

ostream &operator<<(ostream &strm, Date &date)
{
	strm << date.months[date.m_month - 1] << " "
		<< date.m_day << " " << date.m_year;
	return strm;
}

istream &operator>>(istream &strm, Date &date)
{
	cout << "Enter the Month: ";
	strm >> date.m_month;
	date.validateM(date.m_month);

	cout << "Enter the day: ";
	strm >> date.m_day;
	date.validateD(date.m_day);

	cout << "Enter the Year: ";
	strm >> date.m_year;
	return strm;
}

int main()
{
	Date date1(10, 12, 2019);
	Date date2(6, 4, 2016);
	cout << "Dates:\n" << date1 << "\n" << date2 << endl;

	int difference = date1 - date2;
	cout << "Days between both dates: " << difference << "\n" << endl;

	cin >> date1;

	cout << "\nSubtracting day from " << date1 << "\n";
	date1--;
    cout << "Now it is: " << date1 << "\n\n";

	cin >> date2;

	cout << "Adding a day to: " << date2 << "\n";
	++date2;
	cout << "Now it is: " << date2 << endl;

	return 0;
}