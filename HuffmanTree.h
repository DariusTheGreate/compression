#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "Code.h"

#include "Node.h"

#include <iostream>

class HuffmanTree
{
public:
	HuffmanTree(const size_t& alphabet_len) noexcept : head(new Node("h")), buffer(reinterpret_cast<Node*>(new char[sizeof(Node) * (alphabet_len*2)])) {
		build_skeleton(std::move(alphabet_len - 3));

	}

	~HuffmanTree() {
		for (size_t i = 0; i < buffer_offset; ++i) {
			buffer[i].~Node();
			//std::cout << "node destroyed\n";
		}

		char* buffer_to_delete = reinterpret_cast<char*>(buffer);
		delete[] buffer_to_delete;
		delete head;
	}

	Code push(std::string symbol);
	
	void print() const;
	void printer(Node* temp) const;

private:
	void build_skeleton(const size_t& skeleton_len);
	void push_skeleton();

private:
	Node* buffer = nullptr;
	size_t buffer_offset = 0;
	Node* head;

};

#endif
