
// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

/*
Pseudocode:
	Create Binary Tree and Hash Table
	Create Account Object
	Open File and read in data from file
	display menue and ask user to input option
	loop
		if add account
			ask user for bank account info
			create temporary account object
			put object into BST and Hash Table
		if delete account 
			ask user for accoun id number
			find object and delete from hash table and bst and stack
			give user option to save or undo
			if undo
				pop from stack and reinsert to data structures
			if save
				empty stack
		if display one account
			enter user account id number
			display one account object
		if display one account 
			enter bank account id
		if list hash account
			list objecgts in order they appear in hash table
		if list soerted account
			list accounts in inorder traversal in BST
		if print indented tree
			displays intented tree structure
			outputs in Inorder traversal
		if efficiency
			output operations count that took place in BST and BST node
			output Collisions and Load factor from hash table
		if user atm
			does user authentication of username and password and account id
			if accurate, allow atm user to work with that account
			ask user to deposite, withdraw or transfer
			ask for specific account, savings or checking it 
			can display updated account info
		if quit
			print bst tree to outfile in breadth first order
			outfile is same as input file
			goodbye functions
			ends program
		else wrong comand has been entered
	endloop

*/
#include <iostream>
#include <string>
#include <fstream>
#include "Account.h"
#include "BST_Node.h"
#include "BST.h"
#include "HashMap.h"
#include "HashNode.h"
#include "LinkNode.h"
#include "Stack.h"

using namespace std;

int SIZE = 70;
// menu functions
void greeting();
void menu();
void thankYou();

// module functions
void menuAndAction(BinarySearchTree<Account>&);
void addAccount(BinarySearchTree<Account>& bank, HashMap<Account, string>& table, ofstream& outFile);
void deleteAccount(BinarySearchTree <Account>& bankAccounts, HashMap<Account, string>& bankAccountsTable, ofstream& outFile);
void displayOneAccount(HashMap<Account, string>& table);
void listHashAccounts(HashMap<Account, string>& bankAccountsTable);
void listSortedAccounts(BinarySearchTree <Account>& bank);
void printIndentedTree(BST_Node<Account>*, int);
void efficiency(BinarySearchTree <Account>& bankAccounts, HashMap<Account, string>& bankAccountsTable);
void userATM(HashMap<Account, string>& table, ofstream& outFile);

int main()
{
	BinarySearchTree <Account> bankAccounts;
	HashMap<Account, string> bankAccountsTable(SIZE);
	Account account;
	bool loop = true,
		floop = true;
	string fname = "",
		lname = "",
		birthday = "",
		accountNbr = "",
		savings = "",
		checking = "",
		username = "",
		password = "",
		fileLocation = "";

	ifstream inFile;
	ofstream outFile;
	int size = 0,
		choice = 0,
		sizeCalc;

	bool fileLoop = true;
	do
	{
		cout << "Enter the file location of your input file: " << endl;
		getline(cin, fileLocation);

		inFile.open(fileLocation);
		// if file can't be opened 
		if (inFile.fail())
		{
			loop = 1;
			cout << "Please Try Again, input file is not found" << endl;
		}
		else
			fileLoop = 0;
	} while (fileLoop);


	// Take data from file and put them into Hash Table and BST
	while (inFile >> fname >> lname >> birthday >> accountNbr >> savings >> checking >> username >> password)
	{
		string name = fname + " " + lname;
		account.setName(name);
		account.setDateCreation(birthday);
		account.setAcctNbr(accountNbr);
		int save = stoi(savings);
		account.setSavings(save);
		int check = stoi(checking);
		account.setChecking(check);
		account.setUserName(username);
		account.setPassword(password);
		account.setValue("name");
		bankAccounts.insertData(bankAccounts.getRoot(), account);
		bankAccountsTable.insertValue(account, accountNbr);
	}

	greeting();
	cin.get();

	system("cls");

	do
	{
		menu();
		cin >> choice;

		system("cls");

		switch (choice)
		{
			// (1) Add account
		case 1:
			addAccount(bankAccounts, bankAccountsTable, outFile);
			break;

			// (2) Delete account
		case 2:
			deleteAccount(bankAccounts, bankAccountsTable, outFile);
			break;

			// (3) Find and display one account
		case 3:
			displayOneAccount(bankAccountsTable);
			break;

			// (4) List account (hash table sequence)
		case 4:
			listHashAccounts(bankAccountsTable);
			break;

			// (5) List account (sorted key sequence)
		case 5:
			listSortedAccounts(bankAccounts);
			break;

			// (6) Print indented tree
		case 6:
			printIndentedTree(bankAccounts.getRoot(), 0);
			cout << "========================================" << endl;
			cout << "Press Enter to Continue . . . " << endl;
			cout << "========================================" << endl;
			cin.ignore();
			cin.get();
			system("cls");
			break;
			// (7) Efficiency
		case 7:
			efficiency(bankAccounts, bankAccountsTable);
			break;

			// (8) User ATM
		case 8:
			userATM(bankAccountsTable, outFile);
			break;

		case 9:
			inFile.close();
			outFile.open(fileLocation);
			if (!outFile) {
				cout << "Error: Couldn't open input file" << endl;
				cin.get();
				return 0;
			}
			bankAccounts.breadthFirstPrint(outFile, bankAccounts.getRoot());
			outFile.close();
			thankYou();
			cin.ignore();
			cin.get();
			exit(0);
		default:
			cout << "Please try again by entering a number 1-9. " << endl << endl;
		}

	} while (loop);



	system("pause");
	return 0;
}

//******************************************************
//					void greeting()
// pre: receives nothing
// pos: returns nothing
// the function displays a welcome message
//******************************************************
void greeting()
{
	system("cls");

	cout << "========================================" << endl;
	cout << "Welcome to Money Bank " << endl;
	cout << "Press Enter to Continue . . . " << endl;
	cout << "========================================" << endl;
}

//******************************************************
//					void menu()
// pre: receives nothing
// pos: returns nothing
// the function displays the menu for the user 
//*******************************************************
void menu()
{
	cout << "========================================" << endl;
	cout << "Menu:" << endl;
	cout << "(1) Add account" << endl;
	cout << "(2) Delete account" << endl;
	cout << "(3) Find and display one account" << endl;
	cout << "(4) List accounts in hash sorting " << endl;
	cout << "(5) List accounts using sorted key sequence" << endl;
	cout << "(6) Print indented tree" << endl;
	cout << "(7) Efficiency" << endl;
	cout << "(8) User ATM" << endl;
	cout << "(9) Quit" << endl;
	cout << "========================================" << endl;
}

//*********************************************************************
//							void thankYou()
// pre: receives nothing
// pos: returns nothing
// the function displays a message for user when program ends 
//*********************************************************************
void thankYou()
{
	system("cls");

	cout << "========================================" << endl << endl;
	cout << "Program has successfully shut down" << endl;
	cout << "Have a nice day! :)  " << endl << endl;
	cout << "Press Enter to Continue . . . " << endl;
	cout << "========================================" << endl;
}


//*********************************************************************
//						void addAccount()
//pre: none 
//post: returns a new account object to be added into the bank
// This function asks user questions in order to create a new account and 
// returns the new object back to main where it is inserted.
//**********************************************************************
void addAccount(BinarySearchTree<Account>& bank, HashMap<Account, string>& table, ofstream& outFile)
{

	string name, bday, userName, pass, s, c, actNmbr;
	int savings, checkings;

	cout << "********** Please enter the following information start your account! *********" << endl;
	cout << endl;
	cin.ignore();

	cout << "=================================================================" << endl;
	cout << "Enter the Full Name of the Customer (format: FirstName LastName) : " << endl;
	cout << "=================================================================" << endl;
	getline(cin, name);
	system("cls");

	cout << "========================================" << endl;
	cout << "Enter the Username of the Customer: " << endl;
	cout << "========================================" << endl;
	getline(cin, userName);
	system("cls");

	cout << "========================================" << endl;
	cout << "Enter the Password of the Customer: " << endl;
	cout << "========================================" << endl;
	getline(cin, pass);
	system("cls");

	cout << "================================================" << endl;
	cout << "Enter the Enter amount of money in the Savings" << endl;
	cout << "Account of the Customer: " << endl;
	cout << "================================================" << endl;
	getline(cin, s);
	savings = stoi(s);
	system("cls");

	cout << "================================================" << endl;
	cout << "Enter the Enter amount of money in the Checking" << endl;
	cout << "Account of the Customer: " << endl;
	cout << "================================================" << endl;
	getline(cin, c);
	checkings = stoi(c);
	system("cls");

	cout << "============================================" << endl;
	cout << "Your date of birth (format = yyyy-mm-dd ):  " << endl;
	cout << "============================================" << endl;
	getline(cin, bday);
	system("cls");

	cout << "==========================================================" << endl;
	cout << "Enter your own account number in format 'xxx-xx-xxxx' : " << endl;
	cout << "==========================================================" << endl;
	getline(cin, actNmbr);
	system("cls");


	//creating a new Account obj named newAccount
	Account newAccount(name, actNmbr, savings, checkings, userName, pass, bday, "name");
	bank.insertData(bank.getRoot(), newAccount);
	table.insertValue(newAccount, newAccount.getAcctNbr());


	cout << "========================================\n" << endl;
	cout << name << " 's " << endl;
	cout << "Acount has successfully been created! \n" << endl;
	cout << "Press Enter to Continue . . .\n" << endl;
	cout << "========================================" << endl;
	cin.get();


	system("cls");
}


//*********************************************************************
//						void deleteAccount()
//pre: none 
//post: deletes an account
// This function deletes an object based on account number
// has undo functionality
//**********************************************************************
void deleteAccount(BinarySearchTree <Account>& bankAccounts, HashMap<Account, string>& bankAccountsTable, ofstream& outFile)
{
	string choice;
	Stack<Account> undo;
	do {
		// Ask for account number from user
		cout << "Delete Bank Account: " << endl;
		cout << "========================================" << endl;
		cout << "Enter the Account Number of the Customer or enter \"back\" " << endl;
		cout << "========================================" << endl;
		string deleteNBR;
		cin >> deleteNBR;
		Account temp;
		system("cls");
		if (deleteNBR != "back") {

			while (bankAccountsTable.findData(deleteNBR) == NULL) {
				cout << "An account with this number does not exist\nEnter the number of the bank you account you wish to delete: " << endl;
				cin >> deleteNBR;
				system("cls");
			}
			temp = bankAccountsTable.findData(deleteNBR)->getValue();

			// Push deleted object to stack for potential Undo
			undo.push(temp);

			// Delete object from Tree and Hash map
			bankAccounts.deleteNode(bankAccounts.getRoot(), temp);
			bankAccountsTable.removeValue(temp.getAcctNbr());

			system("cls");
			cout << "Account of " << temp.getName() << " #" << temp.getAcctNbr() << " has been deleted." << endl << endl;
		}

		do {
			cout << "========================================" << endl;
			cout << "Enter Option: " << endl;
			cout << "========================================" << endl;
			cout << "\ndelete\tundo\tsave \tquit" << endl;
			cin >> choice;
			string anotherChoice;
			bool valid = true;

			// Undo previous delete
			if (choice == "undo") {
				temp = undo.peek();
				// take object from top of Stack and place back into the objects
				bankAccounts.insertData(bankAccounts.getRoot(), temp);
				bankAccountsTable.insertValue(temp, temp.getAcctNbr());
				undo.pop();
				system("cls");

				cout << temp.getName() << " account #" << temp.getAcctNbr() << " has been reinstated" << endl;
				choice = "repeat";
			}

			// Asks user if they are sure then empties stacks
			else if (choice == "save") {
				string youSure;
				cout << "Are you sure you would like to save? You can not undo changes made. Type yes to continue: ";
				cin >> youSure;
				if (youSure == "yes") {
					// Empty Stack
					cout << "...Changes Saved..." << endl;
					if (undo.isEmpty())
						undo.empty();
					choice = "repeat";
				}
				else {
					cout << "Changes not saved" << endl;
					choice = "repeat";
				}
			}


			else if (choice == "delete") {}
			else if (choice == "quit") {
				cout << "Your Data was automatically saved" << endl;
				if (undo.isEmpty())
					undo.empty();
				return;
			}
			else {
				cout << "Invalid Input" << endl;
				choice = "repeat";
			}
		} while (choice == "repeat");
		system("cls");
	} while (choice == "delete");
}

//************************************************************
//		void displayOneACcount(Hashmap<Account, string>&
// pre: receives the hashTable
// pos: returns nothing
// The function asks user for the account number and displays
// its information 
//*************************************************************
void displayOneAccount(HashMap<Account, string>& table)
{
	string actnmbr;
	cout << "========================================" << endl;
	cout << "To display account: " << endl;
	cout << "Enter the Account Number of the Customer: " << endl;
	cout << "========================================" << endl;
	cin >> actnmbr;
	system("cls");


	cout << "========================================" << endl;
	cout << "	Displaying Account:				" << endl;
	cout << "========================================" << endl;
	table.displayData(actnmbr);


	cout << "========================================" << endl;
	cout << "Press Enter to Continue . . . " << endl;
	cout << "========================================" << endl;
	cin.ignore();
	cin.get();
	system("cls");

}

//******************************************************************
//		void listHashAccounts(HashMap<Account, string>&)
// pre: recieves the hashTable
// pos: nothing
// the entire bank database is listed through using the hashtable
//******************************************************************
void listHashAccounts(HashMap<Account, string>& bankAccountsTable)
{
	cout << "=============================================================" << endl;
	cout << "	Displaying sorted Accounts (Organized by Account Number)" << endl;
	cout << "=============================================================" << endl;
	bankAccountsTable.displayTable();
	cout << "========================================" << endl;
	cout << "Press Enter to Continue . . . " << endl;
	cout << "========================================" << endl;
	cin.ignore();
	cin.get();
	system("cls");
}

//*********************************************************
//	  void listSortedAccounts(BinarySearchTree<Account>
// pre: receives the BST object
// pos: returns nothing
// this function prints out the sorted accounts through using
// the BST.
//***********************************************************
void listSortedAccounts(BinarySearchTree <Account>& bank)
{
	cout << "=======================================" << endl;
	cout << "	Displaying sorted Accounts (Organized by Name)" << endl;
	cout << "=======================================" << endl;

	bank.inPrintData(bank.getRoot());
	cout << "========================================" << endl;
	cout << "Press Enter to Continue . . . " << endl;
	cout << "========================================" << endl;
	cin.ignore();
	cin.get();
	system("cls");
}


//**************************************************************************
//				void printIndentedTree()
// pre: bankAccount retrieves data of users, height of tree and root pointer
// pos: 
// The function will recursively prompt the data using in order traversal.
//**************************************************************************
void printIndentedTree(BST_Node<Account>* root, int height)
{
	 // bankAccounts.inPrintData(bankAccounts.getRoot());
	if (root) {
		// left, root, right
		printIndentedTree(root->getLeft(), height += 1);
		for (int i = 0; i < height; i++)
			cout << "  ";
		cout << root->getData().getName() << "\n";
		printIndentedTree(root->getRight(), height += 1);
	}
}

//*********************************************************
//			void efficiency()
// pre: takes in the BST, Hashtable, and the outfile
// pos: nothing
// outputs the efficiency for the Binary search tree, Hashtable
// and for the linkedlist 
//***********************************************************
void efficiency(BinarySearchTree <Account>& bankAccounts, HashMap<Account, string>& bankAccountsTable)
{
	cout << "========================================" << endl;
	cout << "Binary Search Tree Efficiency" << endl;
	cout << "========================================" << endl;
	cout << bankAccounts.getOperations() << " operations" << endl;
	cout << "========================================" << endl;

	cout << "========================================" << endl;
	cout << "Hash Table Efficiency" << endl;
	cout << "========================================" << endl;
	cout << "Table Size: " << bankAccountsTable.getCapacity() << endl;
	cout << "Load: " << bankAccountsTable.getSize() << endl;
	cout << "Load Factor: " << bankAccountsTable.getLoadFactor() << endl;
	cout << "Collisions: " << bankAccountsTable.getCollisions() << endl;
	cout << "========================================" << endl;
	cin.ignore();
	cin.get();
	system("cls");
}


//*****************************************************************************
//			void userATM(Hashmap<Account, string>, ofstream&)
// pre: receives the hashtable that holds the accounts along with the 
//		output file for any necessary updates 
// pos: returns nothing
// this function acts as an ATM where the user is able to withdraw, deposit,
// and transfer money as well as see their general account information after
// after entering their username and password
//*****************************************************************************
void userATM(HashMap<Account, string>& table, ofstream& outFile)
{
	//we also don't use outFile but im assuming we'll update later
	///// Typing in "Back345" will take the user back into the original main menu /////

	string username, password, accountNbr,
		accType, accType2, choice;
	bool loop[10],
		correct = false;
	double amt = 0,
		total = 0,
		total2 = 0;
	Account account, temp;

	for (int i = 0; i < 9; i++)
	{
		loop[i] = true;
	}

	system("cls");
	cin.ignore();


	cout << "******* Please enter the following information to enter your account! *******" << endl << endl;
	do
	{

		cout << "========================================" << endl;
		cout << "Please Enter Your Username " << endl;
		cout << "========================================" << endl;
		getline(cin, username);
		system("cls");

		cout << "========================================" << endl;
		cout << "Please Enter Your Password " << endl;
		cout << "========================================" << endl;
		getline(cin, password);
		system("cls");

		cout << "========================================" << endl;
		cout << "Please enter your account number: " << endl;
		cout << "========================================" << endl;
		getline(cin, accountNbr);
		system("cls");

		if (table.findData(accountNbr) != NULL) {
			temp = table.findData(accountNbr)->getValue();
			if (temp.getUserName() == username && temp.getPassword() == password && temp.getAcctNbr() == accountNbr)
			{
				account = temp;
				loop[0] = false;
				correct = true;
			}
		}	
		if (!correct)
			cout << "Wrong Username or Password, Please Try Again! \n\n";

	} while (loop[0]);


	do
	{
		loop[0] = true;
		cout << "========================================" << endl;
		cout << "Welcome to X Bank,  " << account.getName() << endl;
		cout << "========================================" << endl;
		cout << "Menu:" << endl;
		cout << "(1) Deposit Money" << endl;
		cout << "(2) Withdraw Money" << endl;
		cout << "(3) List Account Details" << endl;
		cout << "(4) Transfer" << endl;
		cout << "(5) Quit" << endl;
		cout << "========================================" << endl;
		cin >> choice;


		//if user chooses to deposit money, ask deposit or checking
		if (choice == "1")
		{
			system("cls");
			do
			{
				cin.ignore();
				cout << "========================================" << endl;
				cout << "Would you like to deposit money to your  " << endl;
				cout << "Savings account or Checking account: " << endl;
				cout << "========================================" << endl;
				getline(cin, accType);
				system("cls");

				cout << "========================================" << endl;
				cout << "How much money would you like to deposit:  " << endl;
				cout << "========================================" << endl;
				cin >> amt;
				system("cls");


				if (accType == "savings" || accType == "Savings" ||
					accType == "savings account" || accType == "Savings account")
				{
					account.depositSavings(amt);
					loop[1] = false;
					total = account.getSavings();
				}
				else if (accType == "checking" || accType == "Checking" ||
					accType == "checking account" || accType == "Checking account")
				{
					account.depositSavings(amt);
					loop[1] = false;
					total = account.getChecking();
				}
				else
					cout << "Please try again\n" << endl;

			} while (loop[1]);

			cout << "========================================\n\n" << endl;
			cout << "You have successfully deposited " << amt << endl;
			cout << "from your " << accType << "'s Account " << endl;
			cout << "You now have $" << total << "in your " << accType << "'s Account\n\n" << endl;

			cout << "Press Enter to Continue . . .\n\n" << endl;
			cout << "========================================" << endl;
			cin.ignore();
			cin.get();
			system("cls");
		}

		//if user chooses to withdraw money from the account 
		else if (choice == "2")
		{
			system("cls");
			do
			{
				cin.ignore();
				cout << "========================================" << endl;
				cout << "Would you like to withraw money from your  " << endl;
				cout << "Savings account or Checking account: " << endl;
				cout << "========================================" << endl;
				getline(cin, accType);
				system("cls");

				cout << "========================================" << endl;
				cout << "How much money would you like to withraw:  " << endl;
				cout << "========================================" << endl;
				cin >> amt;
				system("cls");


				if (accType == "savings" || accType == "Savings" ||
					accType == "savings account" || accType == "Savings account")
				{
					account.withdrawSavings(amt);
					loop[1] = false;
					total = account.getSavings();
				}
				else if (accType == "checking" || accType == "Checking" ||
					accType == "checking account" || accType == "Checking account")
				{
					account.withdrawChecking(amt);
					loop[1] = false;
					total = account.getChecking();
				}
				else
					cout << "Please try again\n" << endl;

			} while (loop[1]);

			cout << "========================================\n\n" << endl;
			cout << "You have successfully withdrawn " << amt << endl;
			cout << "from your " << accType << "'s Account " << endl;
			cout << "You now have $" << total << " in your " << accType << "'s Account\n\n" << endl;

			cout << "Press Enter to Continue . . .\n\n" << endl;
			cout << "========================================" << endl;
			cin.ignore();
			cin.get();
			system("cls");

		}

		//if user chooses to display their information
		else if (choice == "3")
		{
			system("cls");

			cin.ignore();

			cout << "========================================" << endl;
			cout << account.getName() << "'s Account Information:" << endl;
			cout << "Username: " << account.getUserName() << endl;
			cout << "Password: " << account.getPassword() << endl;
			cout << "Account Number: " << account.getAcctNbr() << endl;
			cout << "Amount in Savings Account: $" << account.getSavings() << endl;
			cout << "Amount in Checking Account: $" << account.getChecking() << "\n\n\n" << endl;
			cout << "Press Enter to Continue . . . " << endl;
			cout << "========================================" << endl;
			cin.get();
			system("cls");

		}

		//if user chooses to transfer money 
		else if (choice == "4")
		{
			system("cls");
			do
			{
				cin.ignore();
				cout << "========================================" << endl;
				cout << "Would you like to transfer money to your  " << endl;
				cout << "Savings account (from checking)" << endl;
				cout << "or Checking account (from savings): " << endl;
				cout << "========================================" << endl;
				getline(cin, accType);
				system("cls");

				cout << "========================================" << endl;
				cout << "How much money would you like to transfer:  " << endl;
				cout << "========================================" << endl;
				cin >> amt;
				system("cls");


				if (accType == "savings" || accType == "Savings" ||
					accType == "savings account" || accType == "Savings account")
				{
					account.checkingToSavingTransfer(amt);
					loop[1] = false;
					total = account.getSavings();
					total2 = account.getChecking();
					accType2 = "checking";
				}
				else if (accType == "checking" || accType == "Checking" ||
					accType == "checking account" || accType == "Checking account")
				{
					account.savingToCheckingTransfer(amt);
					loop[1] = false;
					total = account.getChecking();
					total2 = account.getSavings();
					accType2 = "savings";
				}
				else
					cout << "Please try again\n" << endl;

			} while (loop[1]);

			cout << "========================================\n\n" << endl;
			cout << "You have successfully transfered " << amt << endl;
			cout << "from your " << accType2 << "'s Account " << endl;
			cout << "to your " << accType << "'s Account " << endl;
			cout << "You have $" << total << " in your " << accType << "'s Account" << endl;
			cout << "You have $" << total2 << " in your " << accType2 << "'s Account\n\n" << endl;

			cout << "Press Enter to Continue . . .\n\n" << endl;
			cout << "========================================" << endl;
			cin.ignore();
			cin.get();
			system("cls");

		}

		//if user chooses to exit 
		else if (choice == "5")
		{
			system("cls");
			return;
		}
		// secret password allowing user to return to bank database
		else if (choice == "Back345")
		{
			system("cls");
			return;
		}
		else
		{
			system("cls");
			cout << "Please try again by entering a number 1-5. " << endl << endl;
		}

	} while (loop[0]);

}