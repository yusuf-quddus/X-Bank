#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

template <class T>
class LinkNode
{
protected:
	static int linkNodeOps;
	T data;
	LinkNode<T>* next;
public:
	LinkNode(T);
	void setData(T);
	T getData();
	LinkNode<T>* getNext();
	void setNext(LinkNode<T>*);
	int getOperations();
};

template <class T>
int LinkNode<T>::linkNodeOps = 0;

template <class T>
LinkNode<T>::LinkNode(T d) {
	data = d;
	linkNodeOps++;
}

/*************************************************************
getData
returns data value
pre:
post: returns data value
return: <T>
*************************************************************/
template <class T>
T LinkNode<T>::getData() {
	return data;
	linkNodeOps++;
}


/*************************************************************
setData
changes data value
pre: <T>
post: changes data value to given data value (d)
return: void
*************************************************************/
template <class T>
void LinkNode<T>::setData(T d) {
	data = d;
	linkNodeOps++;
}


/*************************************************************
getNext
returns next value
pre:
post: returns next value
return: <T>*
*************************************************************/
template <class T>
LinkNode<T>* LinkNode<T>::getNext() {
	return next;
	linkNodeOps++;
}



/*************************************************************
setNext
changes next value
pre: <T>*
post: changes next value to given next value (n)
return: void
*************************************************************/
template <class T>
void LinkNode<T>::setNext(LinkNode<T>* n) {
	next = n;
	linkNodeOps++;

}

// int getOperations();
// pre: receives nothing
// pos:  nothing
// returns the number of operations in linkNode
template<class T>
int LinkNode<T>::getOperations() {
	linkNodeOps++;
	return linkNodeOps;
}