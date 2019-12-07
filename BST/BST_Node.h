#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

#include <iostream>

template <class T>
class BST_Node {
protected:
	static int operationsBST;
	T data;
	BST_Node<T> *left;
	BST_Node<T> *right;
public:
	BST_Node();
	BST_Node(T);
	T getData();
	void setData(T);
	int getOperations();
	BST_Node<T> *getLeft();
	BST_Node<T> *getRight();
	void setLeft(BST_Node<T> *);
	void setRight(BST_Node<T> *);
};

template <class T>
int BST_Node<T>::operationsBST = 0;

template <class T>
BST_Node<T>::BST_Node() {
	operationsBST += 3;
	data = 0;
	left = NULL;
	right = NULL;
}



template <class T>
BST_Node<T>::BST_Node(T d) {
	operationsBST += 3;
	data = d;
	left = NULL;
	right = NULL;
}


/*
getData
returns value of data
pre:
post: return data
return: Template
*/
template <class T>
T BST_Node<T>::getData() {
	operationsBST++;
	return data;
}


/*
setData
sets data variable
pre: Template
post: sets data
return: void
*/
template <class T>
void BST_Node<T>::setData(T d) {
	operationsBST++;
	data = d;
}

/*
getOperation
returns operation
pre :
post : returns operation
return : int
*/
template <class T>
int BST_Node<T>::getOperations() {
	return operationsBST;
}


/*
getLeft
returns value of left pointer
pre:
post: return left
return: BST_Node*
*/
template <class T>
BST_Node<T>* BST_Node<T>::getLeft() {
	operationsBST++;
	return left;
}


/*
getRight
returns value of right pointer
pre:
post: return right
return: BST_Node*
*/
template <class T>
BST_Node<T>* BST_Node<T>::getRight() {
	operationsBST++;
	return right;
}


/*
setLeft
sets value of left node
pre: Template
post: sets leftNode
return: void
*/
template <class T>
void BST_Node<T>::setLeft(BST_Node<T> *leftNode) {
	operationsBST++;
	left = leftNode;
}


/*
setLeft
sets value of right node
pre: Template
post: sets rightNode
return: void
*/
template <class T>
void BST_Node<T>::setRight(BST_Node<T> *rightNode) {
	operationsBST++;
	right = rightNode;
}