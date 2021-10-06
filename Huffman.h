#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "Node.h"
#include "HuffmanTree.h"

class HuffmanCompressor
{
public:
	HuffmanCompressor() noexcept = default;
	HuffmanCompressor(const std::string& text) noexcept {
		build_codes(std::move(get_alphabet(text)));
	}

	std::string compress(const std::string& text_to_compress);

private:
	
	std::string get_alphabet(const std::string& text);

	void build_codes(const std::string& sorted_alphabet);

	std::vector<std::pair<char, int>> sort(const std::map<char, int>& M);

	std::map<char, int> codes;

};

#endif
