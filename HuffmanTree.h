#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "Code.h"

#include "Node.h"

#include <iostream>

class HuffmanTree
{
public:
	HuffmanTree(const size_t& alphabet_len) noexcept : head(new Node("h")) {
		build_skeleton(std::move(alphabet_len - 3));
	}

	Code push(std::string symbol);
	
	void print() const;
	void printer(Node* temp) const;

private:
	void build_skeleton(const size_t& skeleton_len);
	void push_skeleton();

private:

	Node* head;

};

#endif
