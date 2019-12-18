#pragma once
#include "CRC.h"
#include "MD5.h"
#include <fstream>
#include <vector>

namespace thatboy
{
	// 类型定义
	using BYTE = uint8_t;
	using WORD = uint16_t;
	using DWORD = uint32_t;
	using BYTE_PTR = BYTE*;
	using BYTE_CPTR = const BYTE*;
	using WORD_PTR = WORD*;
	using WORD_CPTR = const WORD*;
	using DWORD_PTR = DWORD*;
	using DWORD_CPTR = const DWORD*;
	using LPCSTR = const char*;
	using LPSTR = char*;
	
	// 默认CRC类型
	constexpr CRC32::CRC32_TYPE defaultCrcType = CRC32::CRC32_TYPE::eMPEG2;

	// 合成字
	inline WORD makeWORD(BYTE a, BYTE b)
	{
		return (((WORD)(a)) | ((WORD)(b) << 8));
	}
	// 合成双字
	inline DWORD makeDWORD(WORD a, WORD b)
	{
		return (((DWORD)(a)) | ((DWORD)(b) << 16));
	}
	// 合成双字
	inline DWORD makeDWORD(BYTE a, BYTE b, BYTE c, BYTE d)
	{
		return makeDWORD(makeWORD(a, b), makeWORD(c, d));
	}

	// 数据块
	struct Chunk
	{
		DWORD dataLength;	// 数据长度
		DWORD typeCode;		// 类型
		DWORD crcCode;		// CRC校验码【typeCode+data】

	public:
		/******** 接口 ********/
		// 文件写入
		virtual std::ostream& write(std::ostream&)const;
		// 文件读取
		virtual std::istream& read(std::istream&);
		// 校验CRC
		virtual bool checkCrcCode(BYTE crcEncodeType = defaultCrcType)const;
		// 完成设置
		virtual void doFigure(BYTE crcEncodeType = defaultCrcType);
	};

	// 署名域
	struct SignatureDomain
	{
		enum class ENCRYPT_ATTRIBUTE :BYTE
		{
			NORMAL = 0
			, PASSWORD = 1		// 需要密码
			, DEVICEBIND = 2	// 设备绑定
		};
		DWORD magicNumber = makeDWORD('T', 'E', 'F', 255);
		DWORD version = makeDWORD(0, 0, 0, 1);
		DWORD chunkTotalSize = 0;				// 所有区块大小
		DWORD oriFileSize = 0;					// 原始文件大小
		DWORD deviceIDCrc;						// 绑定设备IDCRC
		DWORD RXORCode;							// 混淆标志
		BYTE passwordMD5[32];					// 密码MD5
		BYTE attributeMark;						// 属性标志
		BYTE reserve[3];						// 保留位置
		BYTE oriFileName[260];					// 原始文件名	// 被magicNumber加密
	};
	constexpr size_t size = sizeof(SignatureDomain);
}
