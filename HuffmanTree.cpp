#include "HuffmanTree.h"

Code HuffmanTree::push(std::string symbol) {
	Node* temp = head;
	std::string code_res = "";
	while (temp->left != nullptr && temp->right != nullptr) {
		temp = temp->right;
		code_res += '1';
	}
	if (temp->left == nullptr) {
		temp->left = new Node(symbol);
		code_res += '0';
		std::cout << symbol << " -> " << code_res << "\n";
	}

	else if (temp->right == nullptr && temp->left != nullptr) {
		temp->right = new Node(symbol);
		code_res += '1';
		std::cout << symbol << " -> " << code_res << "\n";
	}

	return Code(code_res.c_str());
}

void HuffmanTree::print() const {
	printer(head);
}

void HuffmanTree::printer(Node* temp) const {
	if (temp == nullptr)
		return;
	std::cout << temp->symbol << "\n";
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

	temp->right = new Node("*");

}