#ifndef BASIC_H
#define BASIC_H

#include <iostream>

#include "list.h"
#include "bintree.h"

template class Node<char>;
template class List<char>;

template class Node<BinNode<char>>;
template class List<BinNode<char>>;

class _Stack {
private:
	List<char> *_stack = new List<char>(new char('\0'));
	
public:
	
	int size() { return _stack->size()-1; }
	
	void push(char c) { char *cp = new char(c);  _stack->addNode(new Node<char>(cp)); }
	char pop() {
		if (_stack->getEnd() != _stack->getStart()) {
			char d = *(_stack->getEnd()->getData()); // Get data from end node
			int t = _stack->size(); // Get index of end node
			_stack->delNode(t-1); // Delete end node
			return d;
		} else return '\0';
	}
	char peek() { if (_stack->getEnd() != _stack->getStart()) return *(_stack->getEnd()->getData()); else return '\0'; }

};


class _Queue {
private:
	List<char> *_queue = new List<char>(new char('\0'));
	
public:
	
	int size() { return _queue->size()-1;}
	
	void enqueue(char c) { char *cp = new char(c);  _queue->addNode(new Node<char>(cp));}
	char dequeue() {
		if (_queue->getEnd() != _queue->getStart()) {
			char d = *(_queue->getNode(1)->getData());
			_queue->delNode(1);
			return d;
		} else return '\0';
	}
};


template<typename T>
class Stack {
private:
	List<T> *_stack = new List<T>(new T());
	
public:
	
	int size() { return _stack->size()-1; }
	
	void push(T* p) { _stack->addNode(new Node<T>(p)); }
	void push(T d) { T* p = new T(d); _stack->addNode(new Node<T>(p)); }
	T* pop() {
		if (_stack->getEnd() != _stack->getStart()) {
			T* p = _stack->getEnd()->getData(); // Get data from end node
			int t = _stack->size()-1; // Get index of end node
			_stack->delNode(t); // Delete end node
			return p;
		} else return nullptr;
	}
	T* peek() { if (_stack->getEnd() != _stack->getStart()) return _stack->getEnd()->getData(); else return nullptr; }

};

template<typename T>
class Queue {
private:
	List<T> *_queue = new List<T>(new T());
	
public:
	
	int size() { return _queue->size()-1;}
	
	void enqueue(T* p) { _queue->addNode(new Node<T>(p)); }
	void enqueue(T d) { T* p = new T(d);  _queue->addNode(new Node<T>(p)); }
	T* dequeue() {
		if (_queue->getEnd() != _queue->getStart()) {
			T* p = _queue->getNode(1)->getData();
			_queue->delNode(1);
			return p;
		} else return nullptr;
	}
};





#endif /** END: BASIC_H */