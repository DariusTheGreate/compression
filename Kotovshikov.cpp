#include "Kotovshikov.h"

Code KotovshikovSymbol::get_code() {
	return code;
}

void KotovshikovSymbol::set_code(const Code& code_in) {
	code = code_in;
}


void KotovshikovSymbolUnit::compose(const KotovshikovSymbolUnit& symbols_in) {
	for (size_t i = 0; i < symbols_in.symbols.size(); ++i) {
		symbols.push_back(symbols_in.symbols[i]);
	}
}

KotovshikovSymbol KotovshikovSymbolUnit::get_symbol(const int& i) {
	return symbols[i];
}

void KotovshikovSymbolUnit::print_symbols() {
	std::cout << "state -> ";
	for (auto& s : symbols) {
		std::cout << s.get_symbol() << "/" << s.get_code().get_str_code() << " ";
	}
	std::cout << "\n";
}

std::vector<KotovshikovSymbol> KotovshikovSymbolUnit::get_codes() const
{
	return symbols;
}

void KotovshikovSymbolUnit::update_codes(const short& i) {
	for (auto& s : symbols) {
		char* code_init = i == 0 ? (char*)"0" : (char*)"1";
		s.set_code(s.get_code() + Code(code_init));
	}
}


std::vector<Code> KotovshikovCompressor::compress(const std::string& text) {
	std::vector<Code> res;

	for (size_t i = 0; i < text.size(); ++i) {
		//res = res + codes[text_to_compress[i]].get_str_code();
		res.push_back(codes[text[i]]);
	}
	//std::cout << res;
	//std::cout << "SIZE IS " << sizeof(res) << "\n";

	return res;
}

std::string&& KotovshikovCompressor::decompress(const std::string& text)
{
	return "not implemented yet\n";
}

std::string KotovshikovCompressor::sort_symbols(const std::string& text) {

	//std::cout << text << "\n";
	std::map<char, int> occurance;

	int c = 0;

	for (size_t i = 0; i < text.size(); ++i) {
		occurance[(int)text[i]]++;
	}

	auto vec = sort(occurance);

	std::string res = "";

	for (size_t i = 0; i < vec.size(); ++i) {
		if (vec[i].second > 0)
			res += vec[i].first;
	}
	res += '\0';
	//std::cout << res << "\n";
	return res;
}

bool KotovshikovCompressor::cmp(std::pair<char, int>& a, std::pair<char, int>& b)
{
	return a.first < b.first;
}

std::vector<std::pair<char, int>> KotovshikovCompressor::sort(const std::map<char, int>& M)
{

	std::vector<std::pair<char, int> > A;

	for (auto& it : M) {
		A.push_back(it);
	}

	std::sort(A.begin(), A.end(), [](std::pair<char, int>& a, std::pair<char, int>& b) {
		return a.first > b.first;
		});

	return A;
}

void KotovshikovCompressor::build_state(const std::string& alphabet) {
	size_t top = alphabet.size() % 2 == 0 ? alphabet.size() : alphabet.size() - 1;
	for (size_t i = 0; i < top; ++i) {
		char* code_init = i % 2 ? (char*)"0" : (char*)"1";
		state.emplace_back(KotovshikovSymbolUnit(KotovshikovSymbol(alphabet[i], code_init)));
	}

	if (top == alphabet.size() - 1) {
		state.emplace_back(KotovshikovSymbolUnit(KotovshikovSymbol(alphabet[top], "1")));
	}
}

void KotovshikovCompressor::build_codes() {
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

	state[0].update_codes(1);

	auto first_partition_codes = state[0].get_codes();
	auto second_partition_codes = state[state.size() - 2].get_codes();

	for (auto& i : first_partition_codes) {
		codes[i.get_symbol()] = i.get_code();
	}

	for (auto& i : second_partition_codes) {
		codes[i.get_symbol()] = i.get_code();
	}

	for (auto& i : codes) {
		std::cout << i.first << " " << i.second.get_code() << "\n";
	}
}