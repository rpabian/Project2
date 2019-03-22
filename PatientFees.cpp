#include "pch.h"
#include <iostream>
#include <string>

using namespace std;
class Surgery;
class Pharmacy;

class PatientAccount
{
private:
	int charges;
	int m_days;
	int dailyRate = 75;
public:
	PatientAccount(int days) 
	{
		m_days = days; 
		charges = m_days * dailyRate;
	}
	PatientAccount() {
		m_days = 0;
		charges = 0;
	}
	void addDays(int days) 
	{ 
		charges += days * dailyRate;
		m_days += days;
	}
	int getDays() { return m_days; }
	int getCharges() { return charges; }
	//friend void Surgery::addCharges(PatientAccount &);
	friend class Surgery;
	//friend void Pharmacy::addCharges(PatientAccount &);
	friend class Pharmacy;
};

class Surgery
{
private:
	const int sCharges[5] = { 100,150,175,200,300 };
	const string sNames[5] = { "Knee", "Plastic", "Hip",
		"Heart", "Brain" };
	int m_choice;
public:
	Surgery(int choice) { m_choice = choice - 1; }
	Surgery() { Surgery(1); }
	void setChoice(int choice) { m_choice = choice - 1; }
	void addCharges(PatientAccount& account)
	{
		account.charges += sCharges[m_choice];
	}
	void displaySurg()
	{
		for (int i = 0; i < 5; i++)
		{
			cout << "\n" << i + 1 << ") " << sNames[i]
				<< ":" << sCharges[i] << "$";
		}
		cout << endl;
	}
};

class Pharmacy
{
private:
	const int medPrice[5] = {20,25,35,45,50};
	const string meds[5] = {"Aderall", "Anti-depressant",
		"Crestor", "Enbrel", "Nexium"};
	int m_choice;
public:
	Pharmacy(int choice) { m_choice = choice - 1; }
	Pharmacy() { Pharmacy(1); }
	void setChoice(int choice) { m_choice = choice - 1; }
	void addCharges(PatientAccount& account)
	{
		account.charges += medPrice[m_choice];
	}
	void displayMeds()
	{
		for (int i = 0; i < 5; i++)
		{
			cout << "\n" << i + 1 << ") " << meds[i]
				<< ":" << medPrice[i] << "$";
		}
		cout << endl;
	}
};


int main()
{
	PatientAccount account1;
	Surgery surgery;
	Pharmacy pharmacy;
	int choice = 0;

	cout << "Patient account charge calculator:\n";
	while (choice < 1 || choice > 4)
	{
		cout << "Please select your action:\n"
			<< "1) add days in Hospital\n"
			<< "2) add a surgery procedure\n"
			<< "3) add a medication\n"
			<< "4) check out of hospital\n" << endl;
		cin >> choice;
		if (choice < 1 || choice > 4)
		{
			cout << "invalid choice, try again\n" << endl;
			continue;
		}
		else if (choice == 1)
		{
			int days;
			cout << "How many days are adding? ";
			cin >> days;
			account1.addDays(days);
			choice = 0;
			continue;
		}
		else if (choice == 2) 
		{
			int sChoice;
			cout << "Choose a surgery Procedure: ";
			surgery.displaySurg();
			cout << "Your Choice: ";
			cin >> sChoice;
			cout << endl;
			surgery.setChoice(sChoice);
			surgery.addCharges(account1);
			choice = 0;
			continue;
		}
		else if (choice == 3)
		{
			int mChoice;
			cout << "Choose a medication: ";
			pharmacy.displayMeds();
			cout << "Your choice: ";
			cin >> mChoice;
			cout << endl;
			pharmacy.setChoice(mChoice);
			pharmacy.addCharges(account1);
			choice = 0;
			continue;
		}
		else
		{
			int charges = account1.getCharges();
			cout << "Your Total Charges: " << charges
				<< "$" << endl;
			break;
		}
	}

	return 0;
}