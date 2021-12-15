#include "Huffman.h"


std::string HuffmanCompressor::get_alphabet(const std::string& text) {
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

	for (auto kv : occurance) {
		std::cout << kv.first << " " << kv.second << "\n";
	}
	
	std::cout << res << "\n";

	res += '\0';
	return res;
}

void HuffmanCompressor::build_codes(const std::string& sorted_alphabet) {
	std::cout << "alphabet -> " << sorted_alphabet << "\n";
	HuffmanTree huffman(sorted_alphabet.size());
	
	for (size_t i = 0; i < sorted_alphabet.size() - 1; ++i) {
		std::string to_push = "";
		to_push += sorted_alphabet.c_str()[i];
		Code code = huffman.push(to_push);
		codes[to_push.c_str()[0]] = code;
	}

	print_codes();
}

std::vector<std::pair<char, int>> HuffmanCompressor::sort(const std::map<char, int>& M)
{
	std::vector<std::pair<char, int> > A;

	for (auto& it : M) {
		A.push_back(it);
	}

	std::sort(A.begin(), A.end(), [](std::pair<char, int>& a, std::pair<char, int>& b) {
		return a.second > b.second;
	});

	return A;
}

std::vector<Code> HuffmanCompressor::compress(const std::string& text_to_compress) {
	std::vector<Code> res;
	
	for (size_t i = 0; i < text_to_compress.size(); ++i) {
		//res = res + codes[text_to_compress[i]].get_str_code();
		res.push_back(codes[text_to_compress[i]]);
	}

	return res;
}

std::string&& HuffmanCompressor::decompress(const std::string& text)
{
	return "not implemented yet\n";
}

void HuffmanCompressor::print_codes() const
{
	std::cout << "codes printer\n";
	for (auto i: codes) {
		std::cout << i.first << " " << i.second.get_str_code() << " ";
	}
	std::cout << "\n";
}
