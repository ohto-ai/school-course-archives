// Base64.cpp : 定义静态库的函数。
//
#include "pch.h"
#include "Base64.h"

bool thatboy::Base64::encode(const std::vector<unsigned char>& dataIn, std::string& strOut)
{
	static constexpr char EncodeMap[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	size_t nInLen = dataIn.size();
	size_t numOrig24BitValues = nInLen / 3;	// <24Bit>
	bool havePadding = (nInLen != numOrig24BitValues * 3);			// 3n+1..2
	bool havePadding2 = (nInLen != numOrig24BitValues * 3 + 1);		// 3n+1
	size_t numResultBytes = 4 * (numOrig24BitValues + havePadding);
	strOut.clear();
	strOut.reserve(numResultBytes + 1);
	// 处理整组
	for (size_t i = 0; i < numOrig24BitValues; ++i)
	{
		strOut.append(1, EncodeMap[(dataIn[3 * i] >> 2) & 0B00111111]);
		strOut.append(1, EncodeMap[((dataIn[3 * i] << 4) & 0B00110000) | ((dataIn[3 * i + 1] >> 4) & 0B00001111)]);
		strOut.append(1, EncodeMap[((dataIn[3 * i + 1] << 2) & 0B00111100) | ((dataIn[3 * i + 2] >> 6) & 0B00000011)]);
		strOut.append(1, EncodeMap[dataIn[3 * i + 2] & 0B00111111]);
	}
	// 处理最后不完整组
	if (havePadding)
	{
		strOut.append(1, EncodeMap[(dataIn[3 * numOrig24BitValues] >> 2) & 0B00111111]);
		if (!havePadding2)
		{
			strOut.append(1, EncodeMap[((dataIn[3 * numOrig24BitValues] << 4) & 0B00110000)]);
			strOut.append(1, '=');
		}
		else
		{
			strOut.append(1, EncodeMap[((dataIn[3 * numOrig24BitValues] << 4) & 0B00110000) | ((dataIn[3 * numOrig24BitValues + 1] >> 4) & 0B00001111)]);
			strOut.append(1, EncodeMap[((dataIn[3 * numOrig24BitValues + 1] << 2) & 0B00111100)]);
		}
		strOut.append(1, '=');
	}

	return true;
}

bool thatboy::Base64::decode(const std::string& strIn, std::vector<unsigned char>& dataOut, bool ifCheckInputValid)
{
	static constexpr unsigned char DecodeMap[256] = {
		0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 62, 0XFF, 63, 0XFF, 0XFF
		, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 0XFF, 0XFF, 0XFF, 0, 0XFF, 0XFF
		, 0XFF, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
		, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 26, 27, 28,  29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40
		, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
		, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF
	};

	size_t nInlen = strIn.length();
	if (nInlen < 4 || nInlen % 4 != 0)
		return false;
	// 检查错误
	if (ifCheckInputValid)
		for (auto& ch : strIn)
			if (DecodeMap[static_cast<unsigned char>(ch)] == 0XFF)
				return false;

	size_t nOutLen = (nInlen * 3) / 4;
	dataOut.resize(nOutLen, 0XFF);
	size_t nLoopLen = nOutLen / 3;
	for (size_t i = 0; i < nLoopLen; ++i)
	{
		dataOut[i * 3] = ((DecodeMap[strIn[i * 4]] << 2) & 0xFC) | ((DecodeMap[strIn[i * 4 + 1]] >> 4) & 0x03);
		dataOut[i * 3 + 1] = ((DecodeMap[strIn[i * 4 + 1]] << 4) & 0xF0) | ((DecodeMap[strIn[i * 4 + 2]] >> 2) & 0x0F);
		dataOut[i * 3 + 2] = ((DecodeMap[strIn[i * 4 + 2]] << 6) & 0xC0) | (DecodeMap[strIn[i * 4 + 3]] & 0x3F);
	}

	if (strIn[nInlen - 1] == '=')
	{
		nOutLen--;
		if (strIn[nInlen - 2] == '=')
			nOutLen--;
	}
	dataOut.resize(nOutLen);
	return true;
}
