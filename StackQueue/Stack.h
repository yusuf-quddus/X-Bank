#pragma once

#include <iostream>
#include "LinkNode.h"
#include "LinkList.h"

template <class T>
class Stack : public List<T> {
protected:
	LinkNode<T> *top;
public:
	Stack();
	Stack(T);
	bool push(T);
	bool pop();
	T peek();
	bool isEmpty();
	bool empty();
	~Stack();
};

template <class T>
Stack<T>::Stack() {
	top = NULL;
	this->count = 0;
}

template <class T>
Stack<T>::Stack(T data) : List<T>(data) {
	this->createList(data);
	top = this->head;
	this->count = 1;
}

/*************************************************************
push
adds the given value to the stack
pre:
data - a template data value
post: adds the given value to the stack
return: bool
*************************************************************/
template <class T>
bool Stack<T>::push(T data) {
	if (this->head == NULL) {
		if (this->createList(data)) {
			top = this->head;
			return true;
		}
	}
	else {
		if (this->addDataFront(data)) {
			top = this->head;
			return true;
		}
	}
	return false;
}

/*************************************************************
pop
deletes the top value from the stack
pre:
post: deletes the top value from the stack
return: bool
*************************************************************/
template <class T>
bool Stack<T>::pop() {
	if (top == '\0') {
		return false;
	}
	else
	{
		this->delFirst();
		top = this->head;
		return true;

	}
}

/*************************************************************
peek
returns the data at the top of the stack
pre:
post: returns the data at the top of the stack
return: <T>
*************************************************************/
template <class T>
T Stack<T>::peek() {
	if (top)
		return top->getData();
}

/*************************************************************
isEmpty
returns true if the stack is empty
pre:
post: returns true if the stack is empty
return: bool
*************************************************************/
template <class T>
bool Stack<T>::isEmpty() {
	if (top == NULL)
		return true;
	return false;
}

/*************************************************************
empty
empties the stack
pre:
post: empties the stack
return: void
*************************************************************/
template <class T>
bool Stack<T>::empty() {
	this->head = top;
	if (this->emptyList())
		return true;
	else
	{
		return false;
	}
}

template <class T>
Stack<T> ::~Stack()
{
	empty();
}