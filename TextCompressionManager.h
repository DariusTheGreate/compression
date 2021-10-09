#ifndef _TEXT_COMPRESSION_MANAGER_
#define _TEXT_COMPRESSION_MANAGER_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "Code.h"

template<typename Algo>
class TextCompressionManager{
public:
	TextCompressionManager(const std::string& file_path_in) : file_path(file_path_in), stream{file_path_in} {
		handle_fail_error(file_path_in);
		handle_bad_error(file_path_in);
        stream.open(file_path.c_str());
        auto str = build_string();
        algo = Algo(str);
        fopen_s(&f, "output.txt", "w+");

        write_to_file("output.txt", algo.compress(str));//baaddtt!
	}

	std::string read_line();

    void write_to_file(const std::string& out, const std::vector<Code>& cd);

	bool check_stream();
	bool is_eof();
	bool is_fail();
	bool is_bad();
	void reset_flags();
	void close();

private:
	std::string build_string();
	
	void handle_fail_error(const std::string& file_path_in);
	void handle_bad_error(const std::string& file_path_in);

	std::ifstream stream;
	std::string file_path;
    Algo algo;

    int current_bit = 0;
    unsigned char bit_buffer;

    FILE* f;
        
    void WriteBit(int bit)
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
};

template<typename Algo>
void TextCompressionManager<Algo>::write_to_file(const std::string& out, const std::vector<Code>& cd) {
    /*using namespace std;
    //cout << cd.get_code() << "\n";
    ofstream ofs(out); // write as txt
    if (ofs) {
        // easy way, use the stream insertion operator
        for (size_t i = 0; i < cd.size(); ++i) {
            ofs << cd[i].get_code() << endl;
        }

        // using fstream::write()
        //string s = cd.get_code().to_string();
        //ofs.write(s.c_str(), s.length());
    }*/

    for (size_t i = 0; i < cd.size(); ++i) {
        
        for (size_t j = 0; j < cd[i].get_code().size(); ++j) {
            
            WriteBit(cd[i].get_code()[j]);
        }
    }
}

template<typename Algo>
std::string TextCompressionManager<Algo>::read_line() {
    //std::string line;
    //std::getline(this->stream, line);
    //return line;
    std::stringstream strStream;
    strStream << stream.rdbuf();
    std::string str = strStream.str();
    return str;
}

template<typename Algo>
std::string TextCompressionManager<Algo>::build_string() {
    return read_line();
}

template<typename Algo>
bool TextCompressionManager<Algo>::check_stream() {
    if (this->stream.good()) {
        return true;
    }
    return false;
}

template<typename Algo>
bool TextCompressionManager<Algo>::is_eof() {
    if (this->stream.eof()) {
        return true;
    }
    return false;
}

template<typename Algo>
bool TextCompressionManager<Algo>::is_fail() {
    if (this->stream.fail()) {
        return true;
    }
    return false;
}

template<typename Algo>
bool TextCompressionManager<Algo>::is_bad() {
    if (this->stream.bad()) {
        return true;
    }
    return false;
}

template<typename Algo>
void TextCompressionManager<Algo>::reset_flags() {
    this->stream.clear();
}

template<typename Algo>
void TextCompressionManager<Algo>::handle_fail_error(const std::string& file_path_in) {
    if (this->is_fail()) {
        std::cerr << "Read/write error while opening '" << file_path_in << "'." << std::endl;
        this->close();
    }
}

template<typename Algo>
void TextCompressionManager<Algo>::handle_bad_error(const std::string& file_path_in) {
    if (this->is_bad()) {
        std::cerr << "Logical error while opening '" << file_path_in << "'." << std::endl;
        this->close();
    }
}

template<typename Algo>
void TextCompressionManager<Algo>::close() {
    this->stream.close();
}

#endif
