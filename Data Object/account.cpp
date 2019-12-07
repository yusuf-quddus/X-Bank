
// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

#include <iostream>
#include "Account.h"

//default constructor
Account::Account() {
	name = "(NO NAME)";
	accountNumber = -1;
	savingsAccount = 0;
	checkingAccount = 0;
}

//overloaded constructor
Account::Account(std::string n, std::string a) {
	name = n;
	accountNumber = a;
	savingsAccount = 0;
	checkingAccount = 0;
}

//overloaded constructor 
Account::Account(std::string n, std::string a, double s, double c, std::string u, std::string p, std::string d, std::string v) {
	name = n;
	accountNumber = a;
	savingsAccount = s;
	checkingAccount = c;
	username = u;
	password = p;
	dateCreation = d;
	sortValue = v;
	total = s + c;
}


//getters 
std::string Account::getName() { return name; }
double Account::getChecking() { return checkingAccount; }
double Account::getSavings() { return savingsAccount; }
std::string Account::getAcctNbr() { return accountNumber; }
std::string Account::getDateCreation() { return dateCreation; }
std::string Account::getPassword() { return password; }
std::string Account::getUserName() { return username; }
std::string Account::getSortValue() { return sortValue; }
double Account::getTotal() {
	total = checkingAccount + savingsAccount;
	return total;
}

//**********
//setters 
void Account::setName(std::string n) {
	name = n;
}

void Account::setAcctNbr(std::string n) {
	accountNumber = n;
}

void Account::setSavings(double s) {
	savingsAccount = s;
	total = savingsAccount + checkingAccount;
}

void Account::setChecking(double c) {
	checkingAccount = c;
	total = savingsAccount + checkingAccount;
}

void Account::setDateCreation(std::string d) {
	dateCreation = d;
}
void Account::setUserName(std::string u) {
	username = u;
}
void Account::setPassword(std::string p) {
	password = p;
}
void Account::setValue(std::string p) {
	sortValue = p;
}



//*********************************************************
//		void Account::depositSavings(double)
// pre: recieves a double value
// pos: the savings amount has been updated 
// the function adds a double value to savings and is saved
//***********************************************************
void Account::depositSavings(double s) {
	savingsAccount += s;
	total = savingsAccount + checkingAccount;
}



//*********************************************************
//		void Account::depositChecking(double)
// pre: receives a double value
// pos: the checkings amount has been updated
// The fuunction adds a double value to the checkings account 
//***********************************************************
void Account::depositChecking(double c) {
	checkingAccount += c;
	total = savingsAccount + checkingAccount;
}



//*********************************************************
//		void ACcount::withdrawSavings(double)
// pre: receives a double value to be withdrawn
// pos: the savings account has been updated
// the function subtracts desired amount from savings 
//***********************************************************
void Account::withdrawSavings(double s) {

	if ((savingsAccount - s) >= 0)
		savingsAccount -= s;
	//if value desired is larger than intial amount
	else
		savingsAccount -= savingsAccount;		//set back to 0
	total = savingsAccount + checkingAccount;
}



//*********************************************************
//		void Account::WithdrawChecking(double)
// pre: receives a double amount to be withdrawn
// pos: the checkings account has been updated
// the function subtracts desired amount from checkings 
//***********************************************************
void Account::withdrawChecking(double c) {
	if ((checkingAccount - c) >= 0)
		checkingAccount -= c;

	//if desired amount is larger than initial
	else
		checkingAccount -= checkingAccount;			//set back to 0
	total = savingsAccount + checkingAccount;
}



//*********************************************************
//		void Account::checkingToSavingTransfer(double)
// pre: receives a double value to be transferred
// pos: savings has been updated 
// the function transfers value from checkings to be added to 
// savings account 
//***********************************************************
void Account::checkingToSavingTransfer(double c) {
	if ((checkingAccount - c) >= 0) {
		checkingAccount -= c;
		savingsAccount += c;
	}
	else {
		checkingAccount -= checkingAccount;
		savingsAccount += checkingAccount;
	}
	total = savingsAccount + checkingAccount;
}


//*********************************************************
//		void Account::savingToCheckingTransfer(double)
// pre: receives a double value to be transferred
// pos: checkings has been updated 
// the function transfers value from savings to be added to 
// checkings account 
//***********************************************************
void Account::savingToCheckingTransfer(double s) {
	if ((savingsAccount - s) >= 0) {
		savingsAccount -= s;
		checkingAccount += s;
	}
	else {
		savingsAccount -= savingsAccount;
		checkingAccount += savingsAccount;
	}
	total = savingsAccount + checkingAccount;
}

/*
operator >
returns true if p1 > p2
pre: person 1 and person 2
post: return boolean
return: bool
*/

bool operator > (Account p1, Account p2)
{
	if (p1.getSortValue() == "name" && p2.getSortValue() == "name")
		if (p1.getName() > p2.getName())
			return true;
		else
			return false;
	else if (p1.getSortValue() == "creationDate" && p2.getSortValue() == "creationDate")
		if (p1.getName() > p2.getName())
			return true;
		else
			return false;
	else if (p1.getSortValue() == "number" && p2.getSortValue() == "number")
		if (p1.accountNumber > p2.accountNumber)
			return true;
		else
			return false;
	else
	{
		std::cout << "Value error. " << std::endl;
		return 1;
	}
}

/*
operator <
returns true if p1 < p2
pre: person 1 and person 2
post: return boolean
return: bool
*/
bool operator < (Account p1, Account p2)
{
	if (p1.getSortValue() == "name" && p2.getSortValue() == "name")
		if (p1.getName() < p2.getName())
			return true;
		else
			return false;
	else if (p1.getSortValue() == "creationDate" && p2.getSortValue() == "creationDate")
		if (p1.getName() < p2.getName())
			return true;
		else
			return false;
	else if (p1.getSortValue() == "number" && p2.getSortValue() == "number")
		if (p1.accountNumber < p2.accountNumber)
			return true;
		else
			return false;
	else
	{
		std::cout << "Value error. " << std::endl;
		return 1;
	}
}

/*
operator ==
returns true if p1 == p2
pre: person 1 and person 2
post: return boolean
return: bool
*/
bool operator == (Account p1, Account p2)
{
	if (p2.getSortValue() == "name") {
		if (p1.name == p2.name)
			return true;
	}
	else if (p2.sortValue == "number") {
		if (p1.accountNumber == p2.accountNumber && p1.name == p2.name)
			return true;
	}
	else return false;
}

/*
operator <<
returns ostream and outputs person information
pre: ostream and person
post: return ostream, outputs person info
return: ostream
*/
std::ostream& operator << (std::ostream& out, const Account& p)
{
	// std::cout << "sort value: " << p.sortValue << std::endl;
	if (p.sortValue == "database") {
		out << "Name: " << p.name << "\nAccount Number: #" << p.accountNumber << "\nCreation Date: " << p.dateCreation;
		out << "\nChecking: $" << p.checkingAccount << "\nSavings: $" << p.savingsAccount << "\nTotal: $" << p.total;
		out << "\nUsername: " << p.username << "\nPassword: " << p.password << std::endl << std::endl;
	}
	else {
		
		out << p.name << std::endl << p.dateCreation << std::endl << p.accountNumber << std::endl << p.savingsAccount;
		out << std::endl << p.checkingAccount << std::endl << p.username << std::endl << p.password << std::endl << std::endl; 
	}
	return out;
}