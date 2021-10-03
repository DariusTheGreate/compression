#ifndef _LZW_
#define _LZW_

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include "ISymbol.h"

class LzwSymbol : public ISymbol{
public:
	LzwSymbol(char symbol_in) : ISymbol(symbol_in) {}
};


class LzwSymbolUnit{
public:
	LzwSymbolUnit(const LzwSymbol& symbol_in){

	}

	void append_symbol(const LzwSymbol& symbol_in){
		symbols.emplace_back(symbol_in);
	}

	void print_symbols(){
		std::cout << "state -> ";
		for(auto& s: symbols){
			std::cout << s.get_symbol() << " ";
		}
		std::cout << "\n";
	}

private:
	std::vector<LzwSymbol> symbols;
};


class LZWCompressor{
public:
	LZWCompressor() = default;

	LZWCompressor(const std::string& text) {
		build_alphabet(std::move(get_occurance(text)));
	}

	void compress(const std::string& str){
		std::cout << "string is: " << str << "\n";
		std::string w = "";
		w += str[0];
		std::vector<int> res_code;
		for(size_t i = 1; i < str.size(); ++i){
			std::string prev = w;
			w += str[i];
			if(state.find(w) == state.end()){
				res_code.push_back(state[prev]);
				state[w] = state_code++;
				w = "";
				i--;
			}
		}
		res_code.push_back(state[w]);
		std::cout << "alphabet is: \n";
		for(auto s: state){
			std::cout << "\t" << s.first << " " << s.second << "\n";
		}

		std::cout << "\n";
		for(size_t i = 0; i < res_code.size(); ++i){
			std::cout << res_code[i] << " ";
		}

		std::cout << "\n";
	}

private:
	
	std::string get_occurance(const std::string& text) {
		std::map<char, int> occurances;
		for (size_t i = 0; i < text.size(); ++i) {
			occurances[(char)text[i]]++;
		}
		std::string res = "";
		for (auto& o : occurances) {
			res += o.first;
		}
		res += "\0";

		return res;
	}

	void build_alphabet(const std::string& alphabet) {
		for (size_t i = 0; i < alphabet.size(); ++i) {
			std::string s = "";
			s += alphabet[i];
			state[s] = state_code++;
			//std::cout << s << " " << state[s] << "\n";
		}
	}

	std::map<std::string, int> state;
	size_t state_code = 0;
};


class LZWDecompressor{
public:
	LZWDecompressor(const std::string& text) {
		build_alphabet(text);
	}

	void decompress(const std::vector<std::string>& coded_str){
		std::string pos = "";
		pos += coded_str[0];
		for(size_t i = 1; i < coded_str.size(); ++i){

		}
	}

private:

	void build_alphabet(const std::string& alphabet) {
		for (size_t i = 0; i < alphabet.size(); ++i) {
			std::string s = "";
			s += alphabet[i];
			state[s] = state_code++;
			//std::cout << s << " " << state[s] << "\n";
		}
	}


	std::map<std::string, std::string> state;
	size_t state_code = 0;
};

#endif
