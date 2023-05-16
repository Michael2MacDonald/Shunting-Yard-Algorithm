#ifndef SHUNT_H
#define SHUNT_H

#include "basic.h"

template class Stack<char>;
template class Queue<char>;


char* shunt(char *str) {
	Queue<char> *queue = new Queue<char>();
	Stack<char> *stack = new Stack<char>();
	for (int i=0; str[i]; i++) { // Not '\0'
		//std::cout << str[i] << '\n';
		if ( str[i] >= 48 && str[i] <= 57 ) { // Is ascii number
			//std::cout << "Added Number to Queue\n";
			queue->enqueue(str[i]); // Add values to queue
		} else if (str[i] == 94) { // Push ascii caret '^' to stack
			// while (the top of the stack isn't a left parenthesis):
			//     pop o2 from the operator stack into the output queue
			while (stack->peek() && *stack->peek()!=40 && stack->size()) queue->enqueue(stack->pop());
			// push o1 onto the operator stack
			stack->push(str[i]);
			//std::cout << "Added operator to Stack\n";
		} else if (str[i] == 40) { // Is ascii left '(' parenthesis
			stack->push(str[i]); // Push to stack
			//std::cout << "Added ( to Stack\n";
		} else if (str[i] == 41) { // Is ascii right ')' parenthesis
			while (stack->peek() && *stack->peek()!=40) { // While operator is not a left parenthesis
				if ( !*stack->peek() ) return nullptr; // === ERROR: Mismatched parentheses ===
				else if ( stack->peek() && *stack->peek() == 94 ) { /*std::cout <<"Moved operator "<<*stack->peek()<<" from Stack to Queue\n";*/ queue->enqueue(stack->pop()); } // Pop operator to queue
				else return nullptr; // === ERROR: There is some invalid char in stack
			}
			//std::cout << "Removed "<<*stack->pop()<<" from Stack\n";
			delete stack->pop(); // Discard left parenthesis once it has been reached
		} else { continue; } // Ignore other characters
	} // Done: End of input string
	
	//std::cout << "remaining: " << stack->size() << '\n';
	while (stack->size()) { // Pop the remaining operators into the queue
		char *c = stack->pop();
		// There should be no left over parentheses
		if (*c == 40) { delete c; return nullptr; } // === ERROR: Mismatched parentheses ===
		else { queue->enqueue(c); /*std::cout << "popped: " << *c << '\n';*/ }
	}
	
	// Output result
	char *result = new char[queue->size()+1]; // Create array to hold output
	for (int i=0; i<queue->size()+1; i++) result[i] = 0;
	for (int i=0; queue->size(); i++) {
		char *p = queue->dequeue(); // Output queue to array
		result[i] = *p;
		delete p;
	}
	delete stack;
	delete queue;
	return result; // Return array
}



#endif /** SHUNT_H */