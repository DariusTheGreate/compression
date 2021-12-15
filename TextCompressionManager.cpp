#include "TextCompressionManager.h"

void TextManager::WriteBit(int bit)
{
    if (bit)
        bit_buffer |= (1 << current_bit);

    current_bit++;
    if (current_bit == 8)
    {
        fwrite(&bit_buffer, 1, 1, f);
        current_bit = 0;
        bit_buffer = 0;
    }
}

void TextManager::write_to_file(const std::string& out, const std::vector<Code>& cd) {
    for (size_t i = 0; i < cd.size(); ++i) {

        for (size_t j = 0; j < cd[i].get_code().size(); ++j) {

            WriteBit(cd[i].get_code()[j]);
        }
    }
}

void TextManager::write_to_file_decompression(const std::string& out, const std::string& content)
{
    return;
}

std::string TextManager::read_line() {
    std::stringstream strStream;
    strStream << stream.rdbuf();
    std::string str = strStream.str();
    return str;
}

std::string TextManager::build_string() {
    return read_line();
}

bool TextManager::check_stream() {
    if (this->stream.good()) {
        return true;
    }
    return false;
}

bool TextManager::is_eof() {
    if (this->stream.eof()) {
        return true;
    }
    return false;
}

bool TextManager::is_fail() {
    if (this->stream.fail()) {
        return true;
    }
    return false;
}

bool TextManager::is_bad() {
    if (this->stream.bad()) {
        return true;
    }
    return false;
}

void TextManager::reset_flags() {
    this->stream.clear();
}

void TextManager::handle_fail_error(const std::string& file_path_in) {
    if (this->is_fail()) {
        std::cerr << "Read/write error while opening '" << file_path_in << "'." << std::endl;
        this->close();
    }
}

void TextManager::handle_bad_error(const std::string& file_path_in) {
    if (this->is_bad()) {
        std::cerr << "Logical error while opening '" << file_path_in << "'." << std::endl;
        this->close();
    }
}

void TextManager::close() {
    this->stream.close();
}
