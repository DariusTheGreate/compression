#ifndef _HUFFMAN_TREE_
#define _HUFFMAN_TREE_

#include "Code.h"

#include "Node.h"

#include <iostream>
/// <summary>
/// need to add some locking in order to maintain sabety of nodes buffer
/// </summary>
class HuffmanTree
{
public:
	HuffmanTree(const size_t& alphabet_len) noexcept : head(new Node("h")), buffer(reinterpret_cast<Node*>(new char[sizeof(Node) * (alphabet_len*2)])) {
		build_skeleton(std::move(alphabet_len - 3));
	}

	~HuffmanTree();
	
	Code push(const std::string& symbol);
	void print() const;

private:
	void printer(Node* temp) const;
	void build_skeleton(const size_t& skeleton_len);
	void push_skeleton();

private:
	//HEAP "OPTIMISATION". Its, bassicly, allocator buffer. 
	Node* buffer = nullptr;
	size_t buffer_offset = 0;
	Node* head = nullptr;
};

#endif
