/***************
 哈夫曼编码实现
 作者：that boy
 日期：2019/2/2
 **************/
#pragma once
#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <algorithm>
#include <Windows.h>

class Huffman
{
	using BYTE = std::uint8_t;
	using WORD = std::uint16_t;
	using DWORD = std::uint32_t;
	Huffman() = delete;
protected:
	struct HuffmanCodeData
	{
		static constexpr DWORD MAGIC_NUMBER = MAKELONG(MAKEWORD('H', 'F'), MAKEWORD('C', 'D'));	// 标准魔数
		static constexpr DWORD BasicSize = sizeof(DWORD) * 5;
		bool ReadHead(const BYTE * Code)
		{
			MagicNumber = ((DWORD*)Code)[0];
			if (MagicNumber != MAGIC_NUMBER)
				return false;
			HFSize		= ((DWORD*)Code)[1];
			R2VSize		= ((DWORD*)Code)[2];
			CodeBits	= ((DWORD*)Code)[3];
			TextSize	= ((DWORD*)Code)[4];
			return true;
		}
		bool WriteHead(BYTE * Code)const
		{
			((DWORD*)Code)[0] = MagicNumber;
			((DWORD*)Code)[1] = HFSize;
			((DWORD*)Code)[2] = R2VSize;
			((DWORD*)Code)[3] = CodeBits;
			((DWORD*)Code)[4] = TextSize;
			return true;
		}
		bool ReadHead(FILE * CodeFile)
		{
			fpos_t pos;
			fgetpos(CodeFile, &pos);

			fread(&MagicNumber, sizeof(DWORD), 1, CodeFile);
			if (MagicNumber != MAGIC_NUMBER)
			{
				fsetpos(CodeFile, &pos);
				return false;
			}
			fread(&HFSize,		sizeof(DWORD), 1, CodeFile);
			fread(&R2VSize,		sizeof(DWORD), 1, CodeFile);
			fread(&CodeBits,	sizeof(DWORD), 1, CodeFile);
			fread(&TextSize,	sizeof(DWORD), 1, CodeFile);

			return true;
		}
		bool WriteHead(FILE * CodeFile)const
		{
			fwrite(&MagicNumber, sizeof(DWORD), 1, CodeFile);
			if (MagicNumber != MAGIC_NUMBER)
				return false;
			fwrite(&HFSize,		sizeof(DWORD), 1, CodeFile);
			fwrite(&R2VSize,	sizeof(DWORD), 1, CodeFile);
			fwrite(&CodeBits,	sizeof(DWORD), 1, CodeFile);
			fwrite(&TextSize,	sizeof(DWORD), 1, CodeFile);
			return true;
		}
		DWORD MagicNumber = MAGIC_NUMBER;	// 魔数
		DWORD HFSize;		// 完整编码长度
		DWORD R2VSize;		// 映射表长度
		DWORD CodeBits;		// 编码内容位数
		DWORD TextSize;		// 原文长度
		BYTE* RankToValue;
		BYTE* Code;
	};
	struct FreInfo
	{
		size_t Frequency;	// 频数
		BYTE Value;			// 值
		bool operator <(const FreInfo & f2)
		{
			return Frequency > f2.Frequency;
		}

	};

	static size_t WriteHuffmanBits(BYTE *, size_t, BYTE);			// 向指定位置写入哈夫曼树节点编码，返回写入位数	
	static size_t ReadHuffmanBits(const BYTE *, size_t, BYTE &);	// 从指定位置读取哈夫曼树节点编码，返回读取位数
	static size_t CountBinaryOn(const BYTE *, size_t);				// 统计二进制置1的数量

public:
	static size_t CountEncodeBuffSize(const BYTE *, size_t);		// 统计编码长度
	static size_t CountDecodeBuffSize(const BYTE *);				// 统计解码长度

	static size_t CountDecodeBuffSize(FILE *);						// 统计解码长度

	static size_t Encode(const BYTE*, size_t, BYTE *, size_t);		// 编码	
	static size_t Decode(const BYTE*, BYTE *, size_t);				// 解码

	static size_t Decode(FILE* , BYTE *, size_t);					// 解码
};
#endif // !HUFFMAN_H