#ifndef _HUFFMAN_
#define _HUFFMAN_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

#include "ISymbol.h"
#include "Node.h"
#include "HuffmanTree.h"

#include "CompressionAlgorithm.h"

class HuffmanSymbol : public ISymbol {
public:
	HuffmanSymbol(char symbol_in, const char* code_in) : ISymbol(symbol_in), code(code_in) {}

private:
	Code code;
};

class HuffmanSymbolUnit {
public:
	HuffmanSymbolUnit(const HuffmanSymbol& symbol_in) {
		symbols.emplace_back(symbol_in);
	}

private:
	std::vector<HuffmanSymbol> symbols;
};

class HuffmanCompressor : CompressionAlgorithm
{
public:
	HuffmanCompressor() = default;
	HuffmanCompressor(const std::string& text) noexcept {
		std::cout << "\nTEXT IN: " << text << "\n";
		build_codes(std::move(get_alphabet(text)));
	}

	std::vector<Code> compress(const std::string& text_to_compress);
	std::string&& decompress(const std::string& text);

	void print_codes() const;

private:
	std::string get_alphabet(const std::string& text);
	void build_codes(const std::string& sorted_alphabet);
	std::vector<std::pair<char, int>> sort(const std::map<char, int>& M);

	std::map<char, Code> codes;
};

#endif
