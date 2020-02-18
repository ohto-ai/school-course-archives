#pragma once

#ifndef _BASE64_H_
#define _BASE64_H_

#include <string>
#include <vector>

namespace thatboy
{
	namespace Base64
	{
		bool encode(const std::vector<unsigned char>&, std::string&);
		bool decode(const std::string&, std::vector<unsigned char>&, bool ifCheckInputValid = false);
		inline size_t getEncodeSize(const std::vector<unsigned char>& dataIn) {
			return ((dataIn.size() - 1) / 3 + 1) * 4;
		}
		inline size_t getEncodeSize(size_t dataSize) {
			return ((dataSize - 1) / 3 + 1) * 4;
		}
		inline size_t getDecodeSize(std::string& strIn)
		{
			return strIn.length() / 3 * 4 + (strIn[strIn.length() - 1] == '=' ? 1 : 0) - (strIn[strIn.length() - 2] == '=' ? 1 : 0);
		}
	};
}

#endif // !_BASE64_H_