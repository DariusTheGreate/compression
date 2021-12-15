#ifndef _KOTOVSHIKOV_
#define _KOTOVSHIKOV_

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

#include "ISymbol.h"
#include "Code.h"
#include "RadixSort.h"
#include "CompressionAlgorithm.h"

#define abstract	

class KotovshikovSymbol : public ISymbol {
public:
	KotovshikovSymbol(char symbol_in, const char* code_in) : ISymbol(symbol_in), code(code_in) {}

	Code get_code();

	void set_code(const Code& code_in);

private:
	Code code;
};

class KotovshikovSymbolUnit {
public:
	KotovshikovSymbolUnit(const KotovshikovSymbol& symbol_in) {
		symbols.emplace_back(symbol_in);
	}

	void compose(const KotovshikovSymbolUnit& symbols_in);

	KotovshikovSymbol get_symbol(const int& i);

	void update_codes(const short& i);

	void print_symbols();

	std::vector<KotovshikovSymbol> get_codes() const;

private:
	std::vector<KotovshikovSymbol> symbols;
};

class KotovshikovCompressor : CompressionAlgorithm {
public:
	KotovshikovCompressor() = default;

	KotovshikovCompressor(const std::string& text) {
		std::cout << "\nSIZE IN " << (text.size() * sizeof(std::string::value_type)) << " \n";
		build_state(std::move(sort_symbols(text)));
		build_codes();
		//compress(text);
	}

	std::vector<Code> compress(const std::string& text);
	std::string&& decompress(const std::string& text);

private:
	std::string sort_symbols(const std::string& text);

	bool cmp(std::pair<char, int>& a, std::pair<char, int>& b);

	std::vector<std::pair<char, int>> sort(const std::map<char, int>& M);

	void build_state(const std::string& alphabet);

	void build_codes();

	std::vector<KotovshikovSymbolUnit> state;

	std::map<char, Code> codes;
};

#endif