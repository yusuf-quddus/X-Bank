#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

#include <iostream>
#include <string>
#include <fstream>
#include "BST_Node.h"
#include "linklist.h"
#include "Queue.h"

template <class T>
class BinarySearchTree {
protected:
	static int operationsBST;
	int count;
	BST_Node<T>* root;
public:
	BinarySearchTree();
	BinarySearchTree(T);
	bool createTree(T);

	// getters
	BST_Node<T>* getRoot();
	int getCount();
	BST_Node<T>* minValue(BST_Node<T>*);
	int getOperations();

	// data functions
	bool insertData(BST_Node<T>*, T);
	BST_Node<T>* findData(BST_Node<T>*, T);

	// print functions of different traversals with ostream
	void inPrintData(std::ofstream&, BST_Node<T>*);
	void prePrintData(std::ofstream&, BST_Node<T>*);
	void postPrintData(std::ofstream&, BST_Node<T>*);
	void breadthFirstPrint(std::ofstream&, BST_Node<T>*);

	// print functions of different traversals 
	void inPrintData(BST_Node<T>*);
	void prePrintData(BST_Node<T>*);
	void postPrintData(BST_Node<T>*);
	void breadthFirstPrint(BST_Node<T>*);

	// deletion functions
	bool emptyTree(BST_Node<T>*);
	BST_Node<T>* deleteNode(BST_Node<T>*, T);

	// destructor
	~BinarySearchTree();
};

template <class T>
int BinarySearchTree<T>::operationsBST = 0;

/*
*/
template <class T>
BinarySearchTree<T>::BinarySearchTree() {
	count = 0;
	root = NULL;
	operationsBST += 2;
}


/*
*/
template <class T>
BinarySearchTree<T>::BinarySearchTree(T data) {
	count = 0;
	root = NULL;
	createTree(data);
	operationsBST += 3;
}


/*
getRoot
returns root node of
pre:
post: return root pointer variable
return: BST_Node*
*/
template <class T>
BST_Node<T>* BinarySearchTree<T>::getRoot()
{
	operationsBST++;
	return root;
}


/*
createTree
create the first node in a tree
pre: template data
post: allocate new BST_Node and
assign to root pointer
return: bool
*/
template <class T>
bool BinarySearchTree<T>::createTree(T data) {
	if (root == NULL) {
		root = new BST_Node<T>(data);
		operationsBST += 2;
		if (root) {
			operationsBST += 3;
			count = 1;
			return true;
		}
		else {
			operationsBST += 2;
			std::cout << "Overflow" << std::endl;
			return false;
		}
	}
	operationsBST++;
	return false;
}


/*
getCount
returns number of nodes
pre:
post: return count variable
return: int
*/
template <class T>
int BinarySearchTree<T>::getCount() {
	operationsBST++;
	return count;
}


/*
getOperation
returns number of operations
pre:
post: return operations variable
return: static int
*/
template <class T>
int BinarySearchTree<T>::getOperations() {
	return operationsBST + root->getOperations();
}

/*
insertData
inserts node into BST
pre: BST_Node*, T var
post: node inserted into proper place
within the BST
return: bool
*/
template <class T>
bool BinarySearchTree<T>::insertData(BST_Node<T>* node, T data)
{
	bool flag = 0;
	operationsBST += 2;
	// if node doesn't exist, create new node
	if (root == NULL)
		return createTree(data);
	else
	{
		operationsBST++;
		// if data is less than node data, go into left branch 
		if (data < node->getData())
		{
			operationsBST++;
			// if left node does not exist, create a new left node 
			if (node->getLeft() == NULL)
			{
				operationsBST++;
				// allocate new node
				BST_Node<T>* nodeTemp = new BST_Node<T>(data);
				operationsBST++;
				if (nodeTemp)
				{
					operationsBST += 2;
					count++;
					flag = true;
				}
				else
				{
					operationsBST += 2;
					std::cout << "Overflow" << std::endl;
					flag = false;
				}
				node->setLeft(nodeTemp);
			}

			// if left node exists, use recursion with left node 
			else {
				insertData(node->getLeft(), data);
				operationsBST++;
			}
		}

		// if data is greater than or equal to node data, go right branch
		else
		{
			// if right node does not exist, create a new right node 
			if (node->getRight() == NULL)
			{
				operationsBST++;
				BST_Node<T>* nodeTemp = new BST_Node<T>(data);
				if (nodeTemp)
				{
					operationsBST += 2;
					count++;
					flag = true;
				}
				else
				{
					operationsBST += 2;
					std::cout << "Overflow" << std::endl;
					flag = false;
				}
				node->setRight(nodeTemp);
				operationsBST++;
			}

			// if right node exists, use recursion with right node 
			else
				insertData(node->getRight(), data);
		}
	}
	return flag;
	// if node doesn't exist, create new node
	if (node == NULL)
		createTree(data);
}


/*
findData
returns node on tree based on specific data
pre: BST_Node*, T var
post: returns BST_Node* of node that contains
requested data
return: BST_Node*
*/
template <class T>
BST_Node<T>* BinarySearchTree<T>::findData(BST_Node<T>* root, T d) {

	// Base Cases: root is null or key is present at root 
	if (root == NULL || root->getData() == d)
	{
		operationsBST++;
		return root;
	}

	// d is greater than root's data
	if (root->getData() < d)
		return findData(root->getRight(), d);

	// d is smaller than root's data
	return findData(root->getLeft(), d);
}


/*
inPrintData
prints data by infix traversal order
pre: ofstream, BST_Node* root
post: tree data printed in infix order
return: void
*/
template <class T>
void BinarySearchTree<T>::inPrintData(std::ofstream& outFile, BST_Node<T>* node) {
	// if node exists
	if (node) {
		// left, root, right
		inPrintData(outFile, node->getLeft());
		outFile << node->getData();
		std::cout << node->getData();
		operationsBST += 3;
		inPrintData(outFile, node->getRight());
		operationsBST += 1;
	}
}


/*
prePrintData
prints data by prefix traversal order
pre: ofstream, BST_Node* root
post: tree data printed in prefix order
return: void
*/
template <class T>
void BinarySearchTree<T>::prePrintData(std::ofstream& outFile, BST_Node<T>* node) {
	// if node exists
	if (node) {
		// root, left, right
		outFile << node->getData();
		std::cout << node->getData();
		operationsBST += 2;
		prePrintData(outFile, node->getLeft());
		prePrintData(outFile, node->getRight());
		operationsBST += 2;
	}
}


/*
postPrintData
prints data by postfix traversal order
pre: ofstream, BST_Node* root
post: tree data printed in postfix order
return: void
*/
template <class T>
void BinarySearchTree<T>::postPrintData(std::ofstream& outFile, BST_Node<T>* node) {
	// if node exists
	if (node) {
		// left, right, root
		postPrintData(outFile, node->getLeft());
		postPrintData(outFile, node->getRight());
		std::cout << node->getData();
		outFile << node->getData();
		operationsBST += 4;
	}
}


/*
breadthFirstPrint
prints data by breadth first traversal order
pre: ofstream, BST_Node* root
post: tree data printed in breadth first order
return: void
*/
template <class T>
void BinarySearchTree<T>::breadthFirstPrint(std::ofstream& outFile, BST_Node<T>* root) {
	if (root == NULL) { exit(1); }
	// create empty Queue
	Queue<BST_Node<T>*> q;
	operationsBST++;
	// enQueue root
	q.enQueue(root);
	operationsBST++;

	while (q.isEmpty() == false) {
		// print front data then dequeue it
		BST_Node<T>* node = q.Front();
		outFile << node->getData();
		std::cout << node->getData();
		operationsBST += 3;
		q.deQueue();

		// enQueue left child
		if (node->getLeft() != NULL)
			q.enQueue(node->getLeft());

		// enQueue right child
		if (node->getRight() != NULL)
			q.enQueue(node->getRight());
	}
}


/*
inPrintData
prints data by infix traversal order
pre: BST_Node* root
post: tree data printed in infix order
return: void
*/
template <class T>
void BinarySearchTree<T>::inPrintData(BST_Node<T>* node) {
	// if node exists
	if (node) {
		// left, root, right
		inPrintData(node->getLeft());
		std::cout << node->getData();
		operationsBST += 2;
		inPrintData(node->getRight());
		operationsBST++;
	}
}


/*
prePrintData
prints data by prefix traversal order
pre: BST_Node* root
post: tree data printed in prefix order
return: void
*/
template <class T>
void BinarySearchTree<T>::prePrintData(BST_Node<T>* node) {
	// if node exists
	if (node) {
		// root, left, right
		std::cout << node->getData();
		operationsBST++;
		prePrintData(node->getLeft());
		operationsBST++;
		prePrintData(node->getRight());
		operationsBST++;
	}
}


/*
postPrintData
prints data by postfix traversal order
pre: BST_Node* root
post: tree data printed in postfix order
return: void
*/
template <class T>
void BinarySearchTree<T>::postPrintData(BST_Node<T>* node) {
	// if node exists
	if (node) {
		// left, right, root
		postPrintData(node->getLeft());
		postPrintData(node->getRight());
		std::cout << node->getData();
		operationsBST += 3;
	}
}


/*
breadthFirstPrint
prints data by breadth first traversal order
pre: ofstream, BST_Node* root
post: tree data printed in breadth first order
return: void
*/
template <class T>
void BinarySearchTree<T>::breadthFirstPrint(BST_Node<T>* root) {
	if (root == NULL) { exit(1); }
	// create empty Queue
	Queue<BST_Node<T>*> q;
	operationsBST++;
	// enQueue root
	q.enQueue(root);

	while (q.isEmpty() == false) {
		// print front data then dequeue it
		BST_Node<T>* node = q.Front();
		std::cout << node->getData();
		operationsBST += 2;
		q.deQueue();

		// enQueue left child
		if (node->getLeft() != NULL)
			q.enQueue(node->getLeft());

		// enQueue right child
		if (node->getRight() != NULL)
			q.enQueue(node->getRight());
	}
}

/*
emptyTree
destroys BST structure
pre: ofstream, BST_Node* root
post: BST is deleted
return: bool
*/
template <class T>
bool BinarySearchTree<T>::emptyTree(BST_Node<T>* node) {
	if (node) {
		BST_Node<T>* curNode = node;
		BST_Node<T>* leftNode = node->getLeft();
		BST_Node<T>* rightNode = node->getRight();
		delete (curNode);
		operationsBST += 4;
		if (curNode) {
			count--;
			operationsBST++;
		}
		else
		{
			std::cout << "Underflow" << std::endl;
			operationsBST++;
			return false;
		}
		// recursion
		emptyTree(leftNode);
		emptyTree(rightNode);
		root = NULL;
		operationsBST += 2;;
		return true;
	}
	else {
		operationsBST++;
		return false;
	}
}


/*
minValue
finds the node that contains smallest data
pre: BST_Node*
post: return BST_Node* with smallest data value
return: BST_Node
*/
template <class T>
BST_Node<T>* BinarySearchTree<T>::minValue(BST_Node<T>* node)
{
	BST_Node<T>* current = node;
	operationsBST++;
	// loop down to find the leftmost leaf
	while (current->getLeft() != NULL)
		current = current->getLeft();
	operationsBST++;
	return current;
}


/*
deleteNode
deletes node specified by data
pre: BST_Node*
post: node with specified data is deleted
return: BST_Node*
*/
template <class T>
BST_Node<T>* BinarySearchTree<T>::deleteNode(BST_Node<T>* root, T d)
{
	if (root == NULL)
		return root;
	operationsBST++;

	// if the data to be deleted is smaller than the root's data, then in left subtree 
	if (d < root->getData())
		root->setLeft(deleteNode(root->getLeft(), d));

	// if the data to be deleted is greater than the root's data, then in right subtree 
	else if (d > root->getData())
		root->setRight(deleteNode(root->getRight(), d));

	// if key is same as root's data, then This is the node to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->getLeft() == NULL)
		{
			BST_Node<T>* temp = root->getRight();
			delete root;
			count--;
			operationsBST += 4;
			return temp;
		}
		else if (root->getRight() == NULL)
		{
			BST_Node<T>* temp = root->getLeft();
			delete root;
			count--;
			operationsBST += 4;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest in the right subtree) 
		BST_Node<T>* temp = minValue(root->getRight());
		operationsBST++;

		// Copy the inorder successor's content to this node 
		root->setData(temp->getData());

		// Delete the inorder successor 
		root->setRight(deleteNode(root->getRight(), temp->getData()));
	}
	operationsBST++;
	return root;
}


/*
~BinarySearchTree
destructor
pre:
data:
post: calls empty data to destroy tree
return:
*/
template <class T>
BinarySearchTree<T>::~BinarySearchTree() {
	emptyTree(root);
	operationsBST++;
}