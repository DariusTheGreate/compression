#ifndef _TEXT_COMPRESSION_MANAGER_
#define _TEXT_COMPRESSION_MANAGER_

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "Code.h"
#include "CompressionAlgorithm.h"

class TextManager {
public:
    std::string read_line();

    void write_to_file(const std::string& out, const std::vector<Code>& cd);

    void write_to_file_decompression(const std::string& out, const std::string& content);

    void WriteBit(int bit);

    bool check_stream();
    bool is_eof();
    bool is_fail();
    bool is_bad();
    void reset_flags();
    void close();

    std::string build_string();

    void handle_fail_error(const std::string& file_path_in);
    void handle_bad_error(const std::string& file_path_in);

    std::ifstream stream;
    std::string file_path;

    int current_bit = 0;
    unsigned char bit_buffer;

    FILE* f;
};

class TextCompressionManager : public TextManager{
public:
	TextCompressionManager(CompressionAlgorithm* compressor_in, const std::string& file_path_in) {
        file_path = file_path_in;
		handle_fail_error(file_path_in);
		handle_bad_error(file_path_in);
        stream.open(file_path.c_str());
        auto str = build_string();
        compressor = compressor_in;
        fopen_s(&f, "output.txt", "w+");
        write_to_file("output.txt", compressor -> compress(str));//baaddtt!
	}

private:
    CompressionAlgorithm* compressor = nullptr;
};

class TextDecompressionManager : public TextManager {
public:
    TextDecompressionManager(CompressionAlgorithm* compressor_in, const std::string& file_path_in) {
        file_path = file_path_in;
        handle_fail_error(file_path_in);
        handle_bad_error(file_path_in);
        stream.open(file_path.c_str());
        auto str = build_string();
        compressor = compressor_in;
        fopen_s(&f, "output.txt", "w+");
        write_to_file_decompression("output.txt", compressor->decompress(str));//baaddtt!
    }
private:
    CompressionAlgorithm* compressor = nullptr;
};

#endif
