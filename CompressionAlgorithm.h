#ifndef _COPMRESSION_ALGORITHM_
#define _COPMRESSION_ALGORITHM_

#include <string>
#include <vector>

class Code;

class CompressionAlgorithm
{
public:
	CompressionAlgorithm() = default;

	CompressionAlgorithm(const std::string& str);

	virtual std::vector<Code> compress(const std::string& str) = 0;
	virtual std::string&& decompress(const std::string& str) = 0;
};

#endif
