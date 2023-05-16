#ifndef SHUNT_H
#define SHUNT_H

#include "basic.h"


char* shunt(char *str) {
	Queue queue;// = new Queue();
	Stack stack;// = new Stack();
	for (int i=0; str[i]; i++) { // Not '\0'
		if ( str[i] >= 48 && str[i] <= 57 ) { // Is ascii number
			queue.enqueue(str[i]); // Add values to queue
		} else if (str[i] == 94) { // Push ascii caret '^' to stack
			// while (the top of the stack isn't a left parenthesis):
			//     pop o2 from the operator stack into the output queue
			while (stack.peek()!=40 && stack.size()) queue.enqueue(stack.pop());
			// push o1 onto the operator stack
			stack.push(str[i]);
		} else if (str[i] == 40) { // Is ascii left '(' parenthesis
			stack.push(str[i]); // Push to stack
		} else if (str[i] == 41) { // Is ascii right ')' parenthesis
			for (;stack.peek()!=40;i++) { // While operator is not a left parenthesis
				if (!stack.peek()) return nullptr; // === ERROR: Mismatched parentheses ===
				else if (stack.peek() == 94) queue.enqueue(stack.pop()); // Pop operator to queue
				else return nullptr; // === ERROR: There is some invalid char in stack
			}
			stack.pop(); // Discard left parenthesis once it ha> been reached
		} else { continue; } // Ignore other characters
	} // Done: End of input string
		
	while (stack.size()) { // Pop the remaining operators into the queue
		char c = stack.pop();
		// There should be no left over parentheses
		if (c == 41) return nullptr; // === ERROR: Mismatched parentheses ===
		else queue.enqueue(c);
	}
	
	// Output result
	char *result = new char[queue.size()+1]; // Create array to hold output
	for (int i=0; queue.size(); i++) result[i] = queue.dequeue(); // Output queue to array
	return result; // Return array
}



#endif /** SHUNT_H */