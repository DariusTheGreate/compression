#ifndef _CODE_
#define _CODE_

#include <string>
#include <bitset>

class Code{
public:
	Code() = default;

	Code(const char* str_code) : code(str_code) {} 
	
	Code operator +(const Code& code_in);

	void append_at_the_end(const std::bitset<8>& str) {
		code.to_string() += str.to_string();
	}

	std::string get_str_code() const;

	std::bitset<4> get_code() const;

private:
	std::bitset<4> code;
};

#endif
