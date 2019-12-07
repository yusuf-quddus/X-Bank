#pragma once

// Yusuf Quddus
// Nathan Wong
// Amber Low
// Renan Hiramatsu

template <class T, class K>
class HashNode {
private:
	K key;
	T value;
	HashNode *next;
public:
	HashNode(T);
	HashNode(T, K);
	K getKey();
	T getValue();
	void setValue(T);
	void setNext(HashNode*);
	HashNode* getNext();
};



/*******************************************
Constructor
*******************************************/
template <class T, class K>
HashNode<T, K>::HashNode(T val) {
	value = val;
	next = NULL;
}



/*******************************************
Constructor
*******************************************/
template <class T, class K>
HashNode<T, K>::HashNode(T k, K v) {
	key = v;
	value = k;
	next = NULL;
}



/*******************************************
getKey
returns the key of node

pre:
post: returns key
return: Template variable K
*******************************************/
template <class T, class K>
K HashNode<T, K>::getKey() {
	return key;
}



/*******************************************
getValue
returns the value of node

pre:
post: returns value
return: Template variable T
*******************************************/
template <class T, class K>
T HashNode<T, K>::getValue() {
	return value;
}



/*******************************************
setValue
sets the value of node

pre: Template variable T
post: set key
return:
*******************************************/
template <class T, class K>
void HashNode<T, K>::setValue(T v) {
	value = v;
}



/*******************************************
setNext
sets the key of next node

pre: HashNode* T
post: set Next
return:
*******************************************/
template <class T, class K>
void HashNode<T, K>::setNext(HashNode* n) {
	next = n;
}



/*******************************************
setNext
sets the key of next node

pre: HashNode* T
post: set Next
return:
*******************************************/
template <class T, class K>
HashNode<T, K>* HashNode<T, K>::getNext() {
	return next;
}
