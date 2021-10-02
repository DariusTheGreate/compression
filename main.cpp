#include <iostream>
#include "Kotovshikov.h"

int main(){
	Kotovshikov state("abcdefghk");
	state.compress();
	std::cout << "----" << "\n";
	return 0;
}