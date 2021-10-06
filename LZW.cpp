#include "LZW.h"

LzwSymbolUnit::LzwSymbolUnit(const LzwSymbol& symbol_in) noexcept {
	symbols.emplace_back(symbol_in);
}

LzwSymbolUnit::LzwSymbolUnit(const std::string& str) noexcept {
	for (size_t i = 0; i < str.size(); ++i) {
		symbols.emplace_back(std::move(LzwSymbol(str[i])));
	}
}

LzwSymbolUnit::LzwSymbolUnit(const LzwSymbolUnit& unit_in) {
	const auto symbols_in = unit_in.get_symbols();

	for (size_t i = 0; i < symbols_in.size(); ++i) {
		symbols.emplace_back(std::move(LzwSymbol(symbols_in[i])));
	}
}

LzwSymbolUnit::LzwSymbolUnit(const char symbol_in[1]) noexcept {
	symbols.emplace_back(symbol_in[0]);
}

LzwSymbolUnit& LzwSymbolUnit::operator =(const char symbol_in[1]) noexcept {
	symbols.emplace_back(symbol_in[0]);
	return *this;
}

LzwSymbolUnit::LzwSymbolUnit(LzwSymbolUnit&& unit_in) noexcept {
	symbols = std::move(unit_in.get_symbols());
}

LzwSymbolUnit& LzwSymbolUnit::operator =(const LzwSymbolUnit& unit_in) noexcept {
	const auto symbols_in = unit_in.get_symbols();

	for (size_t i = 0; i < symbols_in.size(); ++i) {
		symbols.emplace_back(std::move(LzwSymbol(symbols_in[i])));
	}
	return *this;
}

LzwSymbolUnit& LzwSymbolUnit::operator =(LzwSymbolUnit&& unit_in) noexcept {
	if (this != &unit_in) {
		symbols = std::move(unit_in.get_symbols());
	}
	return *this;
}

std::vector<LzwSymbol> LzwSymbolUnit::get_symbols() const noexcept
{
	return symbols;
}

void LzwSymbolUnit::append_symbol(const LzwSymbol& symbol_in) noexcept {
	symbols.emplace_back(symbol_in);
}

void LzwSymbolUnit::print_symbols() const noexcept {
	std::cout << "state -> ";
	for (auto& s : symbols) {
		std::cout << s.get_symbol() << " ";
	}
	std::cout << "\n";
}

std::string LzwSymbolUnit::build_string_from_symbols() const noexcept {
	std::string res = "";
	for (size_t i = 0; i < symbols.size(); ++i) {
		res += symbols[i].get_symbol();
	}

	return res;
}

bool LzwSymbolUnit::operator <(const LzwSymbolUnit& unit_in) const noexcept {
	std::string own = std::move(build_string_from_symbols());
	std::string input = std::move(unit_in.build_string_from_symbols());
	return own < input;
}

LzwSymbolUnit& LzwSymbolUnit::operator +=(const char& unit_in) noexcept {
	symbols.emplace_back(unit_in);
	return *this;
}

LZWCompressor::LZWCompressor(const std::string& text) noexcept {
	build_alphabet(std::move(get_occurance(text)));
	compress(text);
}

std::string LZWCompressor::compress(const std::string& str) noexcept {
	std::cout << "string is: " << str << "\n";
	auto w = std::string("");
	w += str[0];
	std::vector<int> res_code;
	for (size_t i = 1; i < str.size(); ++i) {
		auto prev = w;
		w += str[i];
		if (state.find(w) == state.end()) {
			res_code.push_back(state[prev]);
			state[w] = state_code++;
			w = std::string("");
			i--;
		}
	}

	res_code.push_back(state[w]);
	std::cout << "alphabet is: \n";

	std::cout << "\n";
	for (size_t i = 0; i < res_code.size(); ++i) {
		std::cout << res_code[i] << " ";
	}

	std::cout << "\n";
	return "";
}

std::string LZWCompressor::get_occurance(const std::string& text) noexcept {
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

void LZWCompressor::build_alphabet(const std::string& alphabet) noexcept {
	for (size_t i = 0; i < alphabet.size(); ++i) {
		std::string s = "";
		s += alphabet[i];
		state[s] = state_code++;
		std::cout << s << " " << state[s] << "\n";
	}
}


void LZWDecompressor::decompress(const std::vector<std::string>& coded_str) {
	/*std::string pos = "";
	pos += coded_str[0];
	for (size_t i = 1; i < coded_str.size(); ++i) {

	}*/
}

void LZWDecompressor::build_alphabet(const std::string& alphabet) noexcept {
	/*for (size_t i = 0; i < alphabet.size(); ++i) {
		std::string s = "";
		s += alphabet[i];
		state[s] = state_code++;
		//std::cout << s << " " << state[s] << "\n";
	}*/
}
