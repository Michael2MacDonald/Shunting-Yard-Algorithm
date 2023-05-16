#ifndef BINTREE_H
#define BINTREE_H


template<typename T> class BinNode {
private:
	BinNode* left;
	BinNode* right;
	T* data;
	
	int _size(BinNode<T>* i);
	
public:
	// Create node ('next' will equal 'nullptr')
	BinNode(T*); // Create node with provided data
	BinNode() { this->left = nullptr; this->right = nullptr; this->data = nullptr; } // hack (for stack, queue, and list) to create placeholder object
	~BinNode(); // Destroy node and node data
	
	int size();
	void print(int l=0);
	
	BinNode* getLeft(); // Get pointer of left node
	void setLeft(BinNode*); // Set the 'left' pointer of node
	
	BinNode* getRight(); // Get pointer of right node
	void setRight(BinNode*); // Set the 'right' pointer of node

	T* getData(); // Get void pointer to node data
};

/**
template<typename NT> class BinTree {
private:
	BinNode<NT>* root;
	int _size(BinNode<NT>*);

public:
	BinTree(BinNode<NT>*); // Create list and set start node
	BinTree(NT*); // Create List and create new start node with provided data
	~BinTree(); // Delete list and all nodes
	
	//BinNode<NT>* getLeft(BinNode<NT>*);
	//BinNode<NT>* getRight(BinNode<NT>*);
//	BinNode<NT>* getNode(int); // Get node pointer by index
	BinNode<NT>* getRoot(); // Get node pointer for the start node
	//BinNode<NT>* getEnd(); // Get node pointer for the end node
	
	int size(); // get size
	
	// TODO: Convert to bintree
	/\**void addLeft(NT) {
		
	}
	void addRight(NT) {
		
	}
	void addLeft(BinNode<NT>*) {
		
	}
	void addRight(BinNode<NT>* ) {
		
	}*\/
	//void addNode(BinNode<NT>*);
	//void delNode(int i);
	
	// Overloading [] operator to access elements in array style
	BinNode<NT>* operator[](int);  
};
*/


#endif /** END: BINTREE_H */