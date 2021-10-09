#include <iostream>

#include "Kotovshikov.h"
#include "LZW.h"
#include "TextCompressionManager.h"
#include "RadixSort.h"

#include "Huffman.h"

#pragma warning(disable : 4996)

int main(){
	int i = 0;
	for (i;  i < 1; i++) {
		{
			//TextCompressionManager<HuffmanCompressor> man("data.txt");
			std::cout << "\n\n\n\n\n";
			//TextCompressionManager<LZWCompressor> man2("data.txt");
			//std::cout << "\n\n\n\n\n";
			TextCompressionManager<KotovshikovCompressor> man3("data.txt");
			
		}
	}
	
	std::cout << "\n----\n";
	return 0;
}
