#include "Code.h"

Code Code::operator +(const Code& code_in) {
	return Code(std::move(std::string(code + code_in.code).c_str()));
}

std::string Code::get_code() {
	return code;
}