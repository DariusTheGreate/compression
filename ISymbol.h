#ifndef _ISYMBOL_
#define _ISYMBOL_

class ISymbol{
public:
	ISymbol(char symbol_in){
		symbol = symbol_in;
	}

	char get_symbol(){
		return symbol;
	}

private:
	char symbol;
};

#endif
