#include "Code.h"

Code Code::operator +(const Code& code_in) {
	return Code(std::move(std::string(code.to_string() + code_in.get_str_code()).c_str()));
}

std::string Code::get_str_code() const {
	return code.to_string();
}

std::bitset<4> Code::get_code() const
{
	return code;
}
