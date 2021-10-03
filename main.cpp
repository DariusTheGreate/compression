#include <iostream>

#include "Kotovshikov.h"
#include "LZW.h"
#include "TextCompressionManager.h"

#pragma warning(disable : 4996)

int main(){

	TextCompressionManager<KotovshikovCompressor> man("data.txt");

	std::cout << "\n----+" << "\n";
	return 0;
}
