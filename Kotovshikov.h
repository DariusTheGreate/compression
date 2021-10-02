#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>

class Symbol{
public:	
	Symbol(char symbol_in, char* code_in) : symbol(symbol_in), code(code_in){

	}

	char get_symbol(){
		return symbol;
	}

	std::string get_code(){
		return code;
	}

	std::string* get_code_ptr(){
		return &code;
	}

private:
	std::string code;
	char symbol;
};

class SymbolUnit{
public:
	SymbolUnit(const Symbol& symbol_in){
		symbols.emplace_back(symbol_in);		
	}

	void compose(const SymbolUnit& symbols_in){
		for(size_t i = 0; i < symbols_in.symbols.size(); ++i){
			symbols.push_back(symbols_in.symbols[i]);
		}
	}

	void update_codes(const short& i){
		for(auto& s: symbols){
			char* code_init = i == 0 ? (char*)"0" : (char*)"1";
			*(s.get_code_ptr()) += code_init;
		}
	}

	Symbol get_symbol(const int& i){
		return symbols[i];
	}

	void print_symbols(){
		std::cout << "state -> ";
		for(auto& s: symbols){
			std::cout << s.get_symbol() << "/" << s.get_code() << " ";
		}
		std::cout << "\n";
	}

private:
	std::vector<Symbol> symbols;
};

struct Kotovshikov{
	std::vector<SymbolUnit> state;
	
	Kotovshikov(const std::string& str){
		size_t top = str.size() %2 == 0 ? str.size() : str.size() - 1; 
		for(size_t i = 0; i < top; ++i){
			char* code_init = i%2 ? (char*)"0" : (char*)"1";
			state.emplace_back(SymbolUnit(Symbol(str[i], code_init)));
		}

		if(top == str.size() - 1){
			state.emplace_back(SymbolUnit(Symbol(str[top], "1")));
		}
	}

	void compress(){
		size_t pair_count = 0;
		for(size_t i = 2; i < state.size(); i+=2){
			state[i-2].compose(state[i-1]);
			pair_count++;
		}

		size_t d = 1;
		
		size_t counter = 1;
		while(d < pair_count*2-1){
			state[0].update_codes(1);
			state[0+1+d].update_codes(0);
			state[0].compose(state[0+1+d]);
			counter++;
			d+=2;
		}
		
		//for(size_t i = 0; i < state.size(); ++i){
		state[0].print_symbols();
		state[state.size()-1].print_symbols();
	}
};
