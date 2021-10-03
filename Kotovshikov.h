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

#define abstract	

class KotovshikovSymbol : public ISymbol{
public:	
	KotovshikovSymbol(char symbol_in, const char* code_in) : ISymbol(symbol_in), code(code_in) {}

	Code get_code(){
		return code;
	}

	void set_code(const Code& code_in){
		code = code_in;
	}

private:
	Code code;
};

class KotovshikovSymbolUnit{
public:
	KotovshikovSymbolUnit(const KotovshikovSymbol& symbol_in){
		symbols.emplace_back(symbol_in);		
	}
	
	void compose(const KotovshikovSymbolUnit& symbols_in){
		for(size_t i = 0; i < symbols_in.symbols.size(); ++i){
			symbols.push_back(symbols_in.symbols[i]);
		}
	}

	KotovshikovSymbolUnit get_symbol(const int& i){
		return symbols[i];
	}

	void update_codes(const short& i){
		for(auto& s: symbols){
			char* code_init = i == 0 ? (char*)"0" : (char*)"1";
			//*(s.get_code_ptr()) += code_init;
			s.set_code(s.get_code() + Code(code_init));
		}
	}

	void print_symbols(){
		std::cout << "state -> ";
		for(auto& s: symbols){
			std::cout << s.get_symbol() << "/" << s.get_code().get_code() << " ";
		}
		std::cout << "\n";
	}
private:
	std::vector<KotovshikovSymbol> symbols;
};

class KotovshikovCompressor{
public:	
	KotovshikovCompressor() = default;
	
	KotovshikovCompressor(const std::string& text) {
		build_state(std::move(sort_symbols(text)));
		build_codes();
	}

	std::string compress();

private:
	std::string sort_symbols(const std::string& text) {

		std::cout << text << "\n";
		std::map<char, int> occurance;

		int c = 0;

		for (size_t i = 0; i < text.size(); ++i) {
			occurance[(int)text[i]]++;
		}

		auto vec = sort(occurance);

		std::string res = "";

		for (size_t i = 0; i < vec.size(); ++i) {
			if (vec[i].second > 0)
				res += vec[i].first;//std::cout << vec[i].first << " ";
		}
		res += '\0';
		//RadixSort<AlphabetArr, 256> sorter(&arr);
		std::cout << res << "\n";
		return res;
	}

	bool cmp(std::pair<char, int>& a, std::pair<char, int>& b)
	{
		return a.first < b.first;
	}

	std::vector<std::pair<char, int>> sort(const std::map<char, int>& M)
	{

		std::vector<std::pair<char, int> > A;

		for (auto& it : M) {
			A.push_back(it);
		}

		std::sort(A.begin(), A.end(), [] (std::pair<char, int>& a, std::pair<char, int>& b) {
				return a.first < b.first;
		});

		return A;
	}

	void build_state(const std::string& alphabet) {
		size_t top = alphabet.size() % 2 == 0 ? alphabet.size() : alphabet.size() - 1;
		for (size_t i = 0; i < top; ++i) {
			char* code_init = i % 2 ? (char*)"0" : (char*)"1";
			state.emplace_back(KotovshikovSymbolUnit(KotovshikovSymbol(alphabet[i], code_init)));
		}

		if (top == alphabet.size() - 1) {
			state.emplace_back(KotovshikovSymbolUnit(KotovshikovSymbol(alphabet[top], "1")));
		}
	}

	void build_codes() {
		size_t pair_count = 0;
		for (size_t i = 2; i < state.size(); i += 2) {
			state[i - 2].compose(state[i - 1]);
			pair_count++;
		}

		size_t d = 1;

		size_t counter = 1;
		while (d < pair_count * 2 - 1) {
			state[0].update_codes(1);
			state[0 + 1 + d].update_codes(0);
			state[0].compose(state[0 + 1 + d]);
			counter++;
			d += 2;
		}

		state[0].print_symbols();
		state[state.size() - 1].print_symbols();
	}

	std::vector<KotovshikovSymbolUnit> state;

};

#endif
