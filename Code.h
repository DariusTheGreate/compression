#ifndef _CODE_
#define _CODE_

#include <string>

class Code{
public:
	Code(const char* str_code) : code(str_code) {} 
	
	Code operator +(const Code& code_in){
		auto str = std::string(code + code_in.code);
		return Code(str.c_str());
	}

	std::string get_code(){
		return code;
	}

private:
	std::string code;
};

#endif
