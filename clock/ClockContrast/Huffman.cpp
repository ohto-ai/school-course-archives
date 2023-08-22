#include "pch.h"
#include "Huffman.h"

// 写入一次哈弗曼编码
size_t Huffman::WriteHuffmanBits(BYTE * Buff, size_t BitPos, BYTE Rank)
{
	size_t OnPos = BitPos + Rank;	// 需要写入1的位置
	size_t OnPtr = OnPos >> 3;
	size_t OnOff = OnPos % 8;
	Buff[OnPtr] |= (1 << OnOff);	// 在偏移位置置1
	return (size_t)(Rank + 1);
}

// 读取一次的哈弗曼编码
size_t Huffman::ReadHuffmanBits(const BYTE * Code, size_t BitPos, BYTE & Rank)
{
	size_t OnPos = BitPos;
	size_t OnPtr = OnPos >> 3;
	size_t OnOff = OnPos % 8;

	if ((Code[OnPtr] >> OnOff) != 0) // 在当前字节有完整编码
	{
		for (size_t i = (size_t)OnOff; i < 8; ++i)
		{
			if ((Code[OnPtr] & (1 << i)) != 0)// 找到1
			{
				Rank = BYTE(i - OnOff);
				return (size_t)(Rank + 1);
			}
		}
	}
	else// 编码跨字节
	{
		size_t ValPtr;
		for (ValPtr = (size_t)(OnPtr + 1); Code[ValPtr] == 0; ++ValPtr);	// 找到有1的字节

		for (size_t i = 0; i < 8; ++i)
		{
			if ((Code[ValPtr] & (1 << i)) != 0)// 找到1
			{
				Rank = (BYTE)(((ValPtr - OnPtr) << 3) - OnOff + i);
				return (size_t)(Rank + 1);
			}
		}
	}
	return 0;	// Error
}

// 统计编码长度
size_t Huffman::CountEncodeBuffSize(const BYTE * Data, size_t DataSize)
{
	HuffmanCodeData HFCode = { NULL };
	FreInfo FrequencyList[256];	// 频数表
	BYTE ValueToRank[256];		// 值映射到序
	BYTE RankToValue[256];		// 序映射到值


	// 初始化频数表
	for (size_t i = 0; i < 256; ++i)
	{
		FrequencyList[i].Value = (BYTE)i;
		FrequencyList[i].Frequency = 0;
	}

	// 统计频数和和总数据种类
	for (size_t i = 0; i < DataSize; ++i)
	{
		if (FrequencyList[Data[i]].Frequency++ == 0) // 比较为0，然后频数加1
			++HFCode.R2VSize;
	}

	// 排序频数
	std::sort(FrequencyList, FrequencyList + 256);

	// 记录Value和Rank关系
	for (size_t i = 0; i < HFCode.R2VSize; ++i)
	{
		RankToValue[i] = FrequencyList[i].Value;		// 记录序号到值的转换关系
		ValueToRank[FrequencyList[i].Value] = (BYTE)i;	// 记录值到序号的转换关系
	}

	// 计算长度
	for (size_t i = 0; i < DataSize; ++i)
	{
		HFCode.CodeBits += (size_t)(ValueToRank[Data[i]] + 1);
	}
	HFCode.HFSize = ((HFCode.CodeBits + 7) >> 3) + HFCode.R2VSize + HuffmanCodeData::BasicSize;

	// 完整编码长度
	return (size_t)(HFCode.HFSize);
}

// 统计解码长度
size_t Huffman::CountDecodeBuffSize(const BYTE * Code)
{
	HuffmanCodeData HFCode = { NULL };
	if (HFCode.ReadHead(Code))
		return HFCode.TextSize;
	else
		return 0;
}

// 统计解码长度
size_t Huffman::CountDecodeBuffSize(FILE * Code)
{
	HuffmanCodeData HFCode = { NULL };
	fpos_t pos;
	fgetpos(Code, &pos);
	if (HFCode.ReadHead(Code))
	{
		fsetpos(Code, &pos);
		return HFCode.TextSize;
	}
	else
		return 0;

}

// 统计二进制置1的数量
size_t Huffman::CountBinaryOn(const BYTE * BinaryData, size_t BinaryBits)
{
	size_t Bytes = (BinaryBits >> 3);	// 完整字节数
	size_t Bits = BinaryBits & 0B111;	// 结尾不完整字节位数
	size_t BuffSize = 0;
	for (size_t i = 0; i < Bytes; ++i) // 逐字节计算
	{
		BYTE Num = BinaryData[i];
		if (Num == 0)
			continue;
		else
			do
			{
				++BuffSize;
			}
		while (Num &= Num - 1);
	}
	for (size_t i = 0; i < Bits; ++i)
	{
		if ((BinaryData[Bytes] & (1 << i)) != 0)
			++BuffSize;
	}
	return BuffSize;
}

size_t Huffman::Encode(const BYTE * Data, size_t DataSize, BYTE * CodeBuff, size_t BuffSize)
{
	HuffmanCodeData HFCode = { NULL };
	FreInfo FrequencyList[256];	// 频数表
	BYTE ValueToRank[256];		// 值映射到序
	BYTE RankToValue[256];		// 序映射到值

	// 初始化频数表
	for (size_t i = 0; i < 256; ++i)
	{
		FrequencyList[i].Value = (BYTE)i;
		FrequencyList[i].Frequency = 0;
	}

	// 统计频数和和总数据种类
	for (size_t i = 0; i < DataSize; ++i)
	{
		if (FrequencyList[Data[i]].Frequency++ == 0) // 比较为0，然后频数加1
			++HFCode.R2VSize;
	}

	// 排序频数
	std::sort(FrequencyList, FrequencyList + 256);

	// 记录Value和Rank关系
	for (size_t i = 0; i < HFCode.R2VSize; ++i)
	{
		RankToValue[i] = FrequencyList[i].Value;		// 记录序号到值的转换关系
		ValueToRank[FrequencyList[i].Value] = (BYTE)i;	// 记录值到序号的转换关系
	}
	
	// 计算长度
	for (size_t i = 0; i < DataSize; ++i)
	{
		HFCode.CodeBits += (size_t)(ValueToRank[Data[i]] + 1);
	}

	// 完整编码长度
	HFCode.HFSize = (DWORD)(((HFCode.CodeBits + 7) >> 3) + HFCode.R2VSize + HuffmanCodeData::BasicSize);

	if (BuffSize < HFCode.HFSize)
		return 0;

	HFCode.MagicNumber = HuffmanCodeData::MAGIC_NUMBER;	// 魔数
	HFCode.TextSize = (DWORD)DataSize;		// 原始数据长度
	HFCode.RankToValue = RankToValue;

	memset(CodeBuff, 0, HFCode.HFSize);	// 所有位 置0

	// 写入头数据
	HFCode.WriteHead(CodeBuff);

	// 写入映射表
	for (size_t i = 0; i < HFCode.R2VSize; ++i)
	{
		CodeBuff[HuffmanCodeData::BasicSize + i] = HFCode.RankToValue[i];
	}
	
	// 写入编码内容
	for (size_t DataPtr = 0, BitPos = ((HuffmanCodeData::BasicSize + HFCode.R2VSize) << 3); DataPtr < DataSize; ++DataPtr)
	{
		BitPos += WriteHuffmanBits(CodeBuff, BitPos, ValueToRank[Data[DataPtr]]);
	}

	return HFCode.HFSize;
}

size_t Huffman::Decode(const BYTE * Code, BYTE * Buff, size_t BuffSize)
{
	HuffmanCodeData HFCode = { NULL };
	BYTE RankToValue[256];		// 序映射到值
	size_t BitPos = 0;			// 位索引

	// 读取头数据
	if (!HFCode.ReadHead(Code) || BuffSize < HFCode.TextSize)
		return 0;

	// 读取映射表
	for (size_t i = 0; i < HFCode.R2VSize; ++i)
	{
		RankToValue[i] = Code[HuffmanCodeData::BasicSize + i];
	}

	BYTE Rank;
	size_t BuffPtr;
	Code += HuffmanCodeData::BasicSize + HFCode.R2VSize;	// 偏移指针地址
	for (BuffPtr = 0; BitPos < HFCode.CodeBits &&BuffPtr < BuffSize; ++BuffPtr)
	{
		BitPos += ReadHuffmanBits(Code, BitPos, Rank);
		Buff[BuffPtr] = RankToValue[Rank];
	}
	return BuffPtr;
}

size_t Huffman::Decode(FILE * CodeFile, BYTE * Buff, size_t BuffSize)
{
	HuffmanCodeData HFCode = { NULL };
	BYTE RankToValue[256];		// 序映射到值
	size_t BitPos = 0;			// 位索引

	// 读取头数据
	fpos_t pos;
	fgetpos(CodeFile, &pos);
	if (!HFCode.ReadHead(CodeFile) || BuffSize < HFCode.TextSize)
		return 0;
	fsetpos(CodeFile, &pos);
	BYTE * CodeBeg = new BYTE[HFCode.HFSize];
	fread(CodeBeg, sizeof(BYTE), HFCode.HFSize, CodeFile);

	BYTE * Code = CodeBeg;

	// 读取映射表
	for (size_t i = 0; i < HFCode.R2VSize; ++i)
	{
		RankToValue[i] = Code[HuffmanCodeData::BasicSize + i];
	}

	BYTE Rank;
	size_t BuffPtr;
	Code += HuffmanCodeData::BasicSize + HFCode.R2VSize;	// 偏移指针地址
	for (BuffPtr = 0; BitPos < HFCode.CodeBits &&BuffPtr < BuffSize; ++BuffPtr)
	{
		BitPos += ReadHuffmanBits(Code, BitPos, Rank);
		Buff[BuffPtr] = RankToValue[Rank];
	}
	delete []CodeBeg;
	return BuffPtr;
}
