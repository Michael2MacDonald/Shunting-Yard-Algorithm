#include <iostream>

#include "bintree.h"

template class BinNode<char>;

template<typename T>
BinNode<T>::BinNode(T* data) {
	this->left = nullptr;
	this->right = nullptr;
	this->data = data;
}

template<typename T>
BinNode<T>::~BinNode() {
	// Delete data (Call deconstructor, etc)
	//delete this->data;
	//delete this->left;
	//delete this->right;
}

template<typename T>
int BinNode<T>::size() {
    return _size(this);
}

template<typename T>
int BinNode<T>::_size(BinNode<T>* i) { // i = index
    int r = 0;
    if (i->getRight()) {
        r += _size(i->getRight());
    }
    
    if (i->getLeft()) {
        r += _size(i->getLeft());
    }
    return r;
}


template<typename T>
void BinNode<T>::print(int l) { // i = index, l = level (distance from root)
	if (this->right) this->right->print(l+1);

	for (int j=0; j<l; j++) std::cout << "   |";
	std::cout << *this->getData() << '\n';
	//std::cout << "[" << harr+i << " : " << &harr[i] << "] " << harr[i] << '\n';
	
	if (this->left) this->left->print(l+1);
}


template<typename T>
BinNode<T>* BinNode<T>::getLeft() {
	return this->left;
}

template<typename T>
void BinNode<T>::setLeft(BinNode<T>* node) {
	this->left = node;
}

template<typename T>
BinNode<T>* BinNode<T>::getRight() {
    return this->right;
}

template<typename T>
void BinNode<T>::setRight(BinNode<T>* node) {
    this->right = node;
}

template<typename T>
T* BinNode<T>::getData() {
	return this->data;
}


/////////////////////////////
/////////// LIST ////////////
/////////////////////////////
/**
template<typename NT>
BinTree<NT>::BinTree(BinNode<NT>* node) {
    this->start = node;
}

template<typename NT>
BinTree<NT>::BinTree(NT* data) {
    this->start = new BinNode<NT>(data);
}

/\**template<typename NT>
BinNode<NT>* BinTree<NT>::getNode(int i) {
    BinNode<NT>* node = this->start;
    for (int j=0; j<i; j++) {
        if (node->getNext() == nullptr) {
            // error
            return nullptr;
        } else {
            node = node->getNext();
        }
    }
    return node;
}*\/

template<typename NT>
BinNode<NT>* BinTree<NT>::getRoot() {
    return this->root;
}

//template<typename NT>
//BinNode<NT>* BinTree<NT>::getEnd() {
//    BinNode<NT> *node = this->start;
//    while(1) {
//        if (node->getNext() == nullptr) {
//            return node;
//        } else { node = node->getNext(); }
//    }
//}

template<typename NT>
int BinTree<NT>::size() {
    return _size(root);
	/\**int i = 1;
    BinNode<NT> *node = this->start;
    while(1) {
        if (node->getNext() == nullptr) {
            return i;
        } else {
            node = node->getNext();
            i++;
        }
    }*\/
}

template<typename NT>
int BinTree<NT>::_size(BinNode<NT>* i) { // i = index, l = level (distance from root)
	int r = 0;
	if (i->getRight()) {
		r += _size(i->getRight());
	}
	
	if (i->getLeft()) {
		r += _size(i->getLeft(i));
	}
	return r;
}

template<typename NT>
BinNode<NT>* BinTree<NT>::operator[](int i) {
    return this->getNode(i);
}


template<typename NT>
void BinTree<NT>::addNode(BinNode<NT>* node) {
    // Check if the given node is already part of a list
    // This does not work in the node is at the end of a list
    // We need to implement a 'previous' or 'start' varuable so the entire list can be found from any node
    if (node->getNext() != nullptr) return;
    
    // Check if the list is empty
    if (this->start == nullptr) {
        this->start = node; // Make the node the first node
    } else {
        BinNode<NT>* end = this->getEnd(); // get the last node
        end->setNext(node); // append the node to the last node
    }
}
*/
/**template<typename NT>
void BinTree<NT>::delNode(int i) {
    // Get the node to delete
    BinNode<NT>* node = this->getNode(i);
    
    // Check if the node is the start node
    if (i == 0) this->start = node->getNext(); // set new start
    // Set the previous node's 'next' to this node's 'next' to remove this node from the chain
    else this->getNode(i-1)->setNext( node->getNext() );
    
    delete node; // delete!!!!
} */
