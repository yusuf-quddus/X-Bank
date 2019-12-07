#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

#include <iostream>
#include <string>
#include "HashNode.h"

template<class T, class K>
class HashMap {
private:
	int count;
	int collisions;
	int capacity;
	HashNode<T, K> **arr;
	HashNode<T, K> *temp;

public:
	// Constructor
	HashMap();
	HashMap(int);

	// Operations
	int hashKey(K);
	bool isFull();
	bool removeValue(K);
	bool insertValue(T, K);

	// Setters
	void setCapacity(int);

	// Getters
	int getSize();
	int getCapacity();
	int getCollisions();
	double getLoadFactor();

	HashNode<T, K>* findData(K k);

	// Displays
	void displayTable();
	void displayTable(std::ofstream&);
	bool displayData(K);

	// Destructor
	~HashMap();
};

// Function headers
int stringHasher(std::string date);



/*******************************************
Constructor
*******************************************/
template <class T, class K>
HashMap<T, K>::HashMap() {
	count = collisions = 0;
}



/*******************************************
Constructor
pre: int
post:
return:
*******************************************/
template <class T, class K>
HashMap<T, K>::HashMap(int c)
{
	count = collisions = 0;
	capacity = c;

	// Allocate array based on specified size
	arr = new HashNode<T, K> *[capacity];

	// Set Each Index to NULL
	int i;
	for (i = 0; i < capacity; i++)
		arr[i] = NULL;
	arr[i] = NULL;
}



/*******************************************
hashKey
performs hashing operation on generic key
and returns a position of
pre: template variable K
post: returns an index address
return: int
*******************************************/
template <class T, class K>
int HashMap<T, K>::hashKey(K k) {
	return stringHasher(k);
}



/*******************************************
stringHasher
performs hashing operation on birthday
string by adding all and returns a position
digits until it is less than 9
pre: string
post: returns integer less than 9 as
hash index
return: int
*******************************************/
int stringHasher(std::string date)
{
	int sum = 0;
	int index = 0;

	while (date[index] != NULL) {
		// If ascii is number, turn to int and add to sum
		if (date[index] >= 48 && date[index] <= 57) {
			char *num = new char;
			*num = date[index];
			sum += atoi(num);
			delete num;
		}
		index++;
		// If end of string and sum is greater than 9
		// Turn sum to string and redo loop with new string
		if (date[index] == NULL && !(sum <= 50)) {
			date = std::to_string(sum);
			index = 0;
			sum = 0;
		}
	}
	return sum;
}



/*******************************************
insertValue
Inserts value into hash table based on
value returned from hashKey function.
Quadratic probing collision handling
pre: Template variable T Template variable K
post: value is inputed into the hash table
return: bool
*******************************************/
template <class T, class K>
bool HashMap<T, K>::insertValue(T val, K key) {
	// quadratic value
	int quad = 1;

	// Create temporary node with values
	temp = new HashNode<T, K>(val, key);

	// Get index value from key
	int hashIndex = hashKey(key);

	if (isFull()) {
		std::cout << "Hash Table Full" << std::endl;
		return false;
	}

	if (hashIndex > (capacity - 1))
		hashIndex = (0 + (hashIndex - capacity));

	// Find next empty space in the array using quadratic probing
	while (arr[hashIndex] != NULL)
	{
		// quadratic probing. if quadratic value gets too large/continuous loop then linear probing
		if ((hashIndex + (quad * quad)) < (2 * capacity))
			hashIndex = (hashIndex + (quad * quad));
		else
			hashIndex++;  // Linear probing is quad value gets too large

						  // If Index goes past table, starts back at beginning then continues
		if (hashIndex > (capacity - 1))
			hashIndex = (0 + (hashIndex - capacity));
		quad++;
		collisions++;
	}

	// Increment count then input data into hash table
	if (arr[hashIndex] == NULL)
		count++;
	arr[hashIndex] = temp;
	return true;
}



/*******************************************
removeValue
remove value from hash table based on
value returned from hashKey function and key
pre: Template variable T Template variable K
post: value is removed from the hash table
return: bool
*******************************************/
template <class T, class K>
bool HashMap<T, K>::removeValue(K key) {
	// Find index
	int hashIndex = hashKey(key);

	// Go through array
	while (arr[hashIndex] != NULL) {
		// Find node with specified key
		if (arr[hashIndex]->getKey() == key) {
			delete arr[hashIndex];
			arr[hashIndex] = NULL;
			count--;
			return true;
		}
		hashIndex++;

		// Loops to beginning if goes past end of table
		if (hashIndex > (capacity - 1))
			hashIndex = (0 + (hashIndex - capacity));
	}
	return false;
}



/*******************************************
displayData
displays specific data in hash table based
on provided key
pre: Template variable K
post: value outputed
return: bool
*******************************************/
template <class T, class K>
bool HashMap<T, K>::displayData(K key) {
	// Find index
	int hashIndex = hashKey(key);
	int var = hashIndex;

	// Go through array
	while (arr[hashIndex] != NULL) {
		// Find node with specified key
		if (arr[hashIndex]->getKey() == key) {
			std::cout << arr[hashIndex]->getValue() << std::endl;
			return true;
		}
		hashIndex++;

		// Loops to beginning if goes past end of table
		if (hashIndex > (capacity - 1))
			hashIndex = (0 + (hashIndex - capacity));
		if (hashIndex == var) {
			std::cout << "Invalid Data" << std::endl;
			return false;
		}
	}
	return false;
}



/*******************************************
displayTable
displays entire hash table
pre:
post: hash table outputted
return: void
*******************************************/
template <class T, class K>
void HashMap<T, K>::displayTable() {
	int hashIndex = 0;
	while (hashIndex < capacity) {
		if (arr[hashIndex] != NULL)
			std::cout << arr[hashIndex]->getValue();
		hashIndex++;
	}
}


/*******************************************
displayTable
displays entire hash table
pre:
post: hash table outputted
return: void
*******************************************/
template <class T, class K>
void HashMap<T, K>::displayTable(std::ofstream& outFile) {
	int hashIndex = 0;
	while (hashIndex < capacity) {
		if (arr[hashIndex] != NULL) {
			//arr[hashIndex]->getValue().setValue("database");
			outFile << arr[hashIndex]->getValue();
		}
		hashIndex++;
	}
}



/*******************************************
isFull
Determines if hash table is full or not
pre:
post: returns true if full, false if not
return: bool
*******************************************/
template <class T, class K>
bool HashMap<T, K>::isFull() {
	for (int index = 0; index < capacity; index++) {
		if (arr[index] == NULL) {
			return false;
		}
	}
	return true;
}

/*******************************************
findData
Returns value in hash index
pre: template variable K
post: returns data
return: HashNode
*******************************************/
template <class T, class K>
HashNode<T, K> *HashMap<T, K>::findData(K k) {
	int index = 0;
	while (index < capacity) {
		if (arr[index] != NULL) {
			if (arr[index]->getKey() == k)
				return arr[index];
		}
		index++;
	}
	return NULL;
}

/*******************************************
getSize
returns number of values in hash table
pre:
post: returns count
return: int
*******************************************/
template <class T, class K>
int HashMap<T, K>::getSize() {
	return count;
}



/*******************************************
getCapacity
returns size of hash table array
pre:
post: returns capacity
return: int
*******************************************/
template <class T, class K>
int HashMap<T, K>::getCapacity() {
	return capacity;
}



/*******************************************
getCollisions
returns number of collisions which took
place when inputing data to table
pre:
post: returns collisions
return: int
*******************************************/
template <class T, class K>
int HashMap<T, K>::getCollisions() {
	return collisions;
}



/*******************************************
getLoadFactor
performs calculation to determin load factor
and returns the value. Load factor is number
of filled space divided by index's
pre:
post: returns count
return: int
*******************************************/
template <class T, class K>
double HashMap<T, K>::getLoadFactor() {
	double counter = 0;
	int index = 0;
	// counts number of filled spaces
	while (index < capacity) {
		index++;
		if (arr[index] != NULL) {
			counter++;
		}
	}
	// returns performed calculation
	return (counter / (capacity - 1));
}



/*******************************************
setCapacity
setsCapacity of array
pre:
post: returns count
return: int
*******************************************/
template <class T, class K>
void HashMap<T, K>::setCapacity(int c) {
	capacity = c;
}




/*******************************************
Destructor
*******************************************/
template <class T, class K>
HashMap<T, K>::~HashMap() {
	arr = NULL;
	temp = NULL;
	delete temp;
	delete[] arr;
}