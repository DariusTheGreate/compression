#ifndef _CODE_
#define _CODE_

#include <string>

class Code{
public:
	Code(const char* str_code) : code(str_code) {} 
	
	Code operator +(const Code& code_in);

	std::string get_code();

private:
	std::string code;
};

#endif
