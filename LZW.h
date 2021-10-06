#ifndef _LZW_
#define _LZW_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "ISymbol.h"


class LzwSymbol : public ISymbol{
public:
	LzwSymbol(char symbol_in) noexcept : ISymbol(symbol_in) {}
	LzwSymbol(const LzwSymbol& symbol_in) noexcept : ISymbol(symbol_in.get_symbol()) {}
};


class LzwSymbolUnit{
public:
	LzwSymbolUnit(const LzwSymbol& symbol_in) noexcept;
	LzwSymbolUnit(const std::string& str) noexcept;
	LzwSymbolUnit(const LzwSymbolUnit& unit_in);
	LzwSymbolUnit(const char symbol_in[1]) noexcept;
	LzwSymbolUnit(LzwSymbolUnit&& unit_in) noexcept;

	LzwSymbolUnit& operator =(const char symbol_in[1]) noexcept;
	LzwSymbolUnit& operator =(const LzwSymbolUnit& unit_in) noexcept;
	LzwSymbolUnit& operator =(LzwSymbolUnit&& unit_in) noexcept;
	LzwSymbolUnit& operator +=(const char& unit_in) noexcept;

	bool operator <(const LzwSymbolUnit& unit_in) const noexcept;

	std::string build_string_from_symbols() const noexcept;
	std::vector<LzwSymbol> get_symbols() const noexcept;
	void append_symbol(const LzwSymbol& symbol_in) noexcept;
	void print_symbols() const noexcept;

private:
	std::vector<LzwSymbol> symbols;
};


class LZWCompressor{
public:
	LZWCompressor() noexcept = default;
	LZWCompressor(const std::string& text) noexcept;

	std::string compress(const std::string& str) noexcept;

private:
	std::string get_occurance(const std::string& text) noexcept;
	void build_alphabet(const std::string& alphabet) noexcept;

private:
	std::map<LzwSymbolUnit, int> state;
	size_t state_code = 0;
};


class LZWDecompressor{
public:
	LZWDecompressor(const std::string& text) noexcept{
		build_alphabet(text);
	}

	void decompress(const std::vector<std::string>& coded_str);

private:
	void build_alphabet(const std::string& alphabet) noexcept;

private:
	std::map<std::string, std::string> state;
	size_t state_code = 0;
};

#endif
