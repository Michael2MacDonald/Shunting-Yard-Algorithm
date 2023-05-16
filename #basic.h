#ifndef BASIC_H
#define BASIC_H

#include "list.h"

template class Node<char>;
template class List<char>;

template<typename T>
class Stack {
private:
	List<t> *_stack = new List<T>();
	
public:
	
	int size() { return _stack->size()-1; }
	
	void push(T c) { T *cp = new T(c);  _stack->addNode(new Node<T>(cp)); }
	T pop() {
		if (_stack->getEnd() != _stack->getStart()) {
			T d = *(_stack->getEnd()->getData()); // Get data from end node
			int t = _stack->size(); // Get index of end node
			_stack->delNode(t-1); // Delete end node
			return d;
		} else return '\0';
	}
	T peek() { if (_stack->getEnd() != _stack->getStart()) return *(_stack->getEnd()->getData()); else return '\0'; }

};


class Queue {
private:
	List<char> *_queue = new List<char>(new char('\0'));
	
public:
	
	int size() { return _queue->size()-1;}
	
	void enqueue(T *c) { T *cp = new char(c);  _queue->addNode(new Node<T*>(cp));}
	T* dequeue() {
		if (_queue->getEnd() != _queue->getStart()) {
			T *d = _queue->getNode(1)->getData();
			_queue->delNode(1);
			return d;
		} else return '\0';
	}
};





#endif /** END: BASIC_H */