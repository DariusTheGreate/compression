#ifndef _NODE_
#define _NODE_

#include <string>
#include <iostream>

class Node
{
public:
	
	Node() : symbol(" "), left(nullptr), right(nullptr) {
	}

	Node(const std::string& symbol_in) : symbol(symbol_in), left(nullptr), right(nullptr) {
	}



	Node* left;
	Node* right;
public:
	std::string symbol;
};

#endif
