#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

#include <iostream>
#include <string>

class Account {
protected:
	std::string name;
	std::string dateCreation;
	std::string sortValue;
	std::string accountNumber;
	double total;
	double savingsAccount;
	double checkingAccount;

	std::string username, password;

public:

	//default and overloaded constructors
	Account();
	Account(std::string, std::string);
	Account(std::string, std::string, double, double, std::string, std::string, std::string, std::string);

	//getters
	std::string getName();
	double getChecking();
	double getSavings();
	double getTotal();
	std::string getAcctNbr();
	std::string getDateCreation();
	std::string getPassword();
	std::string getUserName();
	std::string getSortValue();

	//setters
	void setName(std::string);
	void setAcctNbr(std::string);
	void setSavings(double);
	void setChecking(double);
	void setDateCreation(std::string);
	void setUserName(std::string);
	void setPassword(std::string);
	void setValue(std::string);

	//functions
	void depositSavings(double);
	void depositChecking(double);
	void withdrawSavings(double);
	void withdrawChecking(double);
	void checkingToSavingTransfer(double);
	void savingToCheckingTransfer(double);

	//operator overloads
	friend bool operator > (Account p1, Account p2);
	friend bool operator < (Account p1, Account p2);
	friend bool operator == (Account p1, Account p2);
	friend std::ostream& operator << (std::ostream& out, const Account& p);
};