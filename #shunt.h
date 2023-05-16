#ifndef SHUNT_H
#define SHUNT_H

#include "basic.h"

template class Stack<char>;
template class Queue<char>;


char* shunt(char *str) {
	Queue<char> queue;// = new Queue();
	Stack<char> stack;// = new Stack();
	for (int i=0; str[i]!='\0'; i++) { // Not '\0'
		if ( str[i] >= 48 && str[i] <= 57 ) { // Is ascii number
			std::cout << "1\n";
			queue.enqueue(str[i]); // Add values to queue
		} else if (str[i] == 94) { // Push ascii caret '^' to stack
			std::cout << "2\n";
			//continue;
			// while (the top of the stack isn't a left parenthesis):
			//     pop o2 from the operator stack into the output queue
			//std::cout << (*(stack.peek())) << " peak\n";
			while (1) if (*(stack.peek()))!=40 && stack.size()) { std::cout << stack.size() << " Size\n"; queue.enqueue(stack.pop()); }
			// push o1 onto the operator stack
			stack.push(str[i]);
			std::cout << str[i] << '\n';
		} else if (str[i] == 40) { // Is ascii left '(' parenthesis
			std::cout << "3\n";
			stack.push(str[i]); // Push to stack
		} else if (str[i] == 41) { // Is ascii right ')' parenthesis
			std::cout << "4\n";
			for (;(*(stack.peek()))!=40;i++) { // While operator is not a left parenthesis
				if (!(*(stack.peek()))) return nullptr; // === ERROR: Mismatched parentheses ===
				else if ((*(stack.peek())) == 94) queue.enqueue(stack.pop()); // Pop operator to queue
				else return nullptr; // === ERROR: There is some invalid char in stack
			}
			/*delete*/ stack.pop(); // Discard left parenthesis once it has been reached
		} else { continue; } // Ignore other characters
	} // Done: End of input string

	return nullptr;
	
	while (stack.size()) { // Pop the remaining operators into the queue
		char *c = stack.pop();
		// There should be no left over parentheses
		if (*c == 41) { delete c; return nullptr; } // === ERROR: Mismatched parentheses ===
		else queue.enqueue(c);
	}
	
	// Output result
	char *result = new char[queue.size()+1]; // Create array to hold output
	for (int i=0; queue.size(); i++) {
		char *p = queue.dequeue(); // Output queue to array
		result[i] = *p;
		delete p;
	}
	return result; // Return array
}



#endif /** SHUNT_H */