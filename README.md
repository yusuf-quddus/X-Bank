# X-Bank
Program that simulates a bank and manipulates a database of bank accounts which are read in from a file. Modules allow you to add
and delete account, output efficieny or data structures, output account in sorted order and print data in indented tree format. 
The program also has the ability to simulate an ATM. User authenticates account with a Username, Password and Account number and then
can manipulate the account such as deposite, withdraw and transfer money. When program ends, the input file is updated to changes made in 
data. 

## Binary Search Tree

Read data from database file into a BST using the name of account as the key. Used for sorting structures

## Hash Table
Used for searching and locating data

#### Hash Function

Hash Function uses bank account number. Hash key by adding the digits repeatedly until it ends up being a number between 0 and 9, which will be the index of the data in the hash table. So, a date of 2017-12-04 will reduce as 2+0+1+7+1+2+0+4 = 17 which will further reduce as 1+7 = 8 and its associated data record (name + birthday) will be added to index 8 in the hash table.

#### Collision Handling

For collision resolution, use quadratic probing in the same direction always, revert to linear probing. Data Structure capable of link based collision handling

## Stack
Use link based stack as an undo feature in the delete module. When data is deleted, the data is pushed on the stack. If the user wants to undo a delete, the data will be popped from the stack and inserted back into data structures. User can save changes and the stack will be emptied

## Queue
Use link based queue for breadth first traversal in the Binary Search Tree. Breadth First order is used to update input file at end of the program

## Modules
* Add Account  - Input info to create an account and insert into BST and Hash Table
* Delete Account - Use Account number to delete an account, can undo deletes until you input save option
* Display One Account - enter account number to display information of one account
* list Hash Table - list data in sequence it exists in hash table
* List Sorted Sequence - Uses Inorder traversal to sort by Account Name
* Print Indented Tree - prints bst in indented tree format
* Efficiency - outputs load factor, collisions, and operations that take place in BST
* ATM - simulates and ATM requires authentication
* quit

# Database Format
account name<br />
account creation date<br />
account number<br />
money in savings account<br />
money in checking account<br />
username<br />
password<br />

## Authors

* **Yusuf Quddus**
