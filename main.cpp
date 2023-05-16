#include <iostream>
#include <cstring>
#include <cctype> // tolower

#include "basic.h"
#include "list.h"
#include "bintree.h"
#include "shunt.h"

template class Stack<BinNode<char>>;


char* toin(BinNode<char>*);
char* topost(BinNode<char>*);
char* topre(BinNode<char>*);


int main() {

	std::cout << "\n==========\nTry testing using the commands:\n'conv pre ((1^2)^(3^4))^5^6'\n'conv in ((1^2)^(3^4))^5^6'\nor 'conv post ((1^2)^(3^4))^5^6'\n";
	
	while(1) {
		char input[10] = {}; // zero-init the entire array
		std::cout << "===============\nType A Command:\n";
		std::cin >> input;
		
		// to lower case
		for (int i = 0; i < std::strlen(input); i++) {
			input[i] = std::tolower(input[i]);
		}
		
		if (!strcmp(input, "ep")) { // Expression to Postfix
			char exp[101] = {'\0'};
			std::cout << "Please type your expression using parentheses, single digit numbers, and carets:\n";
			std::cin >> exp;
			//for (int i=0; exp[i]!='\0'; i++) std::cout << exp[i];
			char *out = shunt(exp);
			
			if (out == nullptr) { std::cout << "=== ERROR: Invalid expression ===\n"; continue; }
			std::cout << "Result: ";
			for (int i=0; out[i]; i++) std::cout << out[i];
			std::cout << '\n';
			delete[] out;
		} else if (!strcmp(input, "conv")) {
			char type[10] = {'\0'};
			std::cout << "Please select an output type for your expression (in | post | pre):\n";
			std::cin >> type;
			
			char exp[101] = {'\0'};
			std::cout << "Please type your expression using parentheses, single digit numbers, and carets:\n";
			std::cin >> exp;
			for (int i=0; exp[i]!='\0'; i++) std::cout << exp[i]; std::cout << '\n';
			
			std::cout << "===\n";
			
			char *post = shunt(exp); // Convert input to postfix
			if (post == nullptr) { std::cout << "=== ERROR: Invalid expression ===\n"; continue; }
			std::cout << "Postfix: ";
			for (int i=0; post[i]!='\0'; i++) std::cout << post[i];  std::cout << '\n';
			
			// Convert postfix to bintreeOP
			if (post[0]<48 || post[0]>75) return 0; // ERROR
			Stack<BinNode<char>> *stack = new Stack<BinNode<char>>();
			for (int i=0; post[i]; i++) {
				if (post[i] >= 48 && post[i] <= 57) // If char is number
					stack->push(new BinNode<char>(new char(post[i])));
				else if (post[i] == 94) { // If char is operator
					BinNode<char> *tmp2 = stack->pop(); // Fetch top item in stack
					BinNode<char> *tmp1 = stack->pop(); // Fetch second to top item in stack
					BinNode<char> *tmp0 = new BinNode<char>(new char(post[i])); // Create new item with operator
					tmp0->setLeft(tmp1); // Append fetched item to new item
					tmp0->setRight(tmp2); // Append other fetched item to new item
					stack->push(tmp0); // Push new item to stack
				}
			}
			BinNode<char>* tree = stack->pop();
			std::cout << "Expression Tree:\n";
			tree->print();
			//continue;
			
			char *out;
			
			// Convert bintree to requested type
			if (!strcmp(type, "in")) {
				out = toin(tree);
			} else if (!strcmp(type, "post")) {
				out = topost(tree);
			} else if (!strcmp(type, "pre")) {
				out = topre(tree);
			} else { std::cout << "=== ERROR: Invalid expression type ===\n" << type; continue; }
			
			//if (out == nullptr) { std::cout << "=== ERROR: Invalid expression ===\n"; continue; }
			std::cout << "Result: ";
			for (int i=0; out[i]; i++) std::cout << out[i];
			std::cout << '\n';
			delete[] out;
		} else if (!strcmp(input, "quit") || !strcmp(input, "exit") || !strcmp(input, "q")) {
			return 0;
		} else { std::cout << "ERROR: Incorrect Command\n"; }
	}


	
}

char* _toin(BinNode<char>* n) {
	// If this node is a number, it is the last node and can be just be returned
	if (*n->getData() >= 48 && *n->getData() <= 57) {
		char* out = (char*)calloc(sizeof(char), 2);
		*out = *n->getData();
		for (int i=0;i<strlen(out); i++) std::cout << out[i]; std::cout << '\n';
		return out; // Create new char because it will be deleted by the calling function instance and we don't want to delete the tree itself 
		//return new char(*n->getData());
	}
	
	// Else, if this node is an operator:
	// - Call this function on the left and right nodes (recursively)
	// - They will return a string containing a number or the expression of the entire tree below that node
	// - Combine them into the required format (in, out, pre)
	// - Add parenthisieas around that format
	char* l; char* r;
	if (n->getLeft())
		l = _toin(n->getLeft());
	if (n->getRight())
		r = _toin(n->getRight());
	
	std::cout << "Left: "; for (int i=0; i<strlen(l); i++) std::cout << l[i]; std::cout << '\n';
	std::cout << "Right: "; for (int i=0; i<strlen(r); i++) std::cout << r[i]; std::cout << '\n';
	
	int ll = strlen(l);
	int rl = strlen(r);
	char* out = (char*)calloc(sizeof(char), ll+rl+4);
	out[0] = '(';
//	out[strlen(out)] = '(';
	strcat(out, l); delete[] l; // left
	out[strlen(out)] = *n->getData(); // in
	strcat(out, r); delete[] r; // right
	out[strlen(out)] = ')';
	return out;
}

char* toin(BinNode<char>* pp) {
	return _toin(pp);
}


char* _topost(BinNode<char>* n) {
	// If this node is a number, it is the last node and can be just be returned
	if (*n->getData() >= 48 && *n->getData() <= 57) {
		char* out = (char*)calloc(sizeof(char), 2);
		*out = *n->getData();
		//for (int i=0;i<strlen(out); i++) std::cout << out[i]; std::cout << '\n';
		return out; // Create new char because it will be deleted by the calling function instance and we don't want to delete the tree itself 
		//return new char(*n->getData());
	}
	
	// Else, if this node is an operator:
	// - Call this function on the left and right nodes (recursively)
	// - They will return a string containing a number or the expression of the entire tree below that node
	// - Combine them into the required format (in, out, pre)
	// - Add parenthisieas around that format
	char* l; char* r;
	if (n->getLeft())
		l = _topost(n->getLeft());
	if (n->getRight())
		r = _topost(n->getRight());
	
	//std::cout << "Left: "; for (int i=0; i<strlen(l); i++) std::cout << l[i]; std::cout << '\n';
	//std::cout << "Right: "; for (int i=0; i<strlen(r); i++) std::cout << r[i]; std::cout << '\n';
	
	int ll = strlen(l);
	int rl = strlen(r);
	char* out = (char*)calloc(sizeof(char), ll+rl+4);
//	out[0] = '(';
//	out[strlen(out)] = '(';
	strcat(out, l); delete[] l; // left
	strcat(out, r); delete[] r; // right
	out[strlen(out)] = *n->getData(); // post
//	out[strlen(out)] = ')';
	return out;
}

char* topost(BinNode<char>* pp) {
	return _topost(pp);
}


char* _topre(BinNode<char>* n) {
	// If this node is a number, it is the last node and can be just be returned
	if (*n->getData() >= 48 && *n->getData() <= 57) {
		char* out = (char*)calloc(sizeof(char), 2);
		*out = *n->getData();
		//for (int i=0;i<strlen(out); i++) std::cout << out[i]; std::cout << '\n';
		return out; // Create new char because it will be deleted by the calling function instance and we don't want to delete the tree itself 
		//return new char(*n->getData());
	}
	
	// Else, if this node is an operator:
	// - Call this function on the left and right nodes (recursively)
	// - They will return a string containing a number or the expression of the entire tree below that node
	// - Combine them into the required format (in, out, pre)
	// - Add parenthisieas around that format
	char* l; char* r;
	if (n->getLeft())
		l = _topre(n->getLeft());
	if (n->getRight())
		r = _topre(n->getRight());
	
	//std::cout << "Left: "; for (int i=0; i<strlen(l); i++) std::cout << l[i]; std::cout << '\n';
	//std::cout << "Right: "; for (int i=0; i<strlen(r); i++) std::cout << r[i]; std::cout << '\n';
	
	int ll = strlen(l);
	int rl = strlen(r);
	char* out = (char*)calloc(sizeof(char), ll+rl+4);
//	out[0] = '(';
//	out[strlen(out)] = '(';
	out[strlen(out)] = *n->getData(); // pre
	strcat(out, l); delete[] l; // left
	strcat(out, r); delete[] r; // right
//	out[strlen(out)] = ')';
	return out;
}

char* topre(BinNode<char>* pp) {
	return _topre(pp);
}




