#include "HuffmanTree.h"


HuffmanTree::~HuffmanTree() {
	for (size_t i = 0; i < buffer_offset; ++i) {
		buffer[i].~Node();
	}

	char* buffer_to_delete = reinterpret_cast<char*>(buffer);
	delete[] buffer_to_delete;
	delete head;
}

Code HuffmanTree::push(const std::string& symbol) {
	Node* temp = head;
	std::string code_res = "";
	while (temp->left != nullptr && temp->right != nullptr) {
		temp = temp->right;
		code_res += '1';
	}
	if (temp->left == nullptr) {
		temp->left = new(buffer + buffer_offset++) Node(symbol);
		code_res += '0';
		//std::cout << symbol << " -> " << code_res << "\n";
	}

	else if (temp->right == nullptr && temp->left != nullptr) {
		temp->right = new(buffer + buffer_offset++) Node(symbol);
		code_res += '1';
		//std::cout << symbol << " -> " << code_res << "\n";
	}

	//std::cout << "buffer -> " << buffer_offset << "\n";
	return Code(code_res.c_str());
}

void HuffmanTree::print() const {
	printer(head);
}

void HuffmanTree::printer(Node* temp) const {
	if (temp == nullptr)
		return;
	//std::cout << temp->symbol << "\n";
	printer(temp->left);
	printer(temp->right);
}

void HuffmanTree::build_skeleton(const size_t& skeleton_len) {
	for (size_t i = 0; i < skeleton_len; ++i) {
		push_skeleton();
	}
}

void HuffmanTree::push_skeleton() {
	Node* temp = head;

	while (temp->right != nullptr) {
		temp = temp->right;
	}
	//std::cout << buffer_offset << "\n";
	temp->right = new(buffer + buffer_offset++) Node("*");

}