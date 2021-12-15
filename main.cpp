#include <iostream>

#include "Kotovshikov.h"
#include "LZW.h"
#include "TextCompressionManager.h"
#include "RadixSort.h"

#include "Huffman.h"

#pragma warning(disable : 4996)

void HuffmanTreeShowCase() {
	HuffmanTree htr(4);
	auto code = htr.push("a");
	auto code2 = htr.push("b");
	auto code3 = htr.push("c");
	auto code4 = htr.push("d");
}

void KotovshikovCompressorShowCase() {
	KotovshikovCompressor kc("aaabbbbbbbbbssssaaaaassbbrr");
}

int main(){
	int i = 0;
	KotovshikovCompressorShowCase();
	for (i;  i < 1; i++) {
		{
			HuffmanCompressor hc;
			CompressionAlgorithm* hptr = (CompressionAlgorithm*)&hc;//PIZDEC PIZDEC PIZDEC PIZDEC PIZDEC PIZDEC
			TextCompressionManager man(hptr, "data.txt");
			//std::cout << "\n\n\n\n\n";
			//TextCompressionManager<LZWCompressor> man2("data.txt");
			//std::cout << "\n\n\n\n\n";
			//TextCompressionManager<KotovshikovCompressor> man3("data.txt");
		}
	}
	
	std::cout << "\n----\n";
	return 0;
}
