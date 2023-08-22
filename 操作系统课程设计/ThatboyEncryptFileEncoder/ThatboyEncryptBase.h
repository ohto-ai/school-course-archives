#pragma once
#include "CRC.h"
#include "MD5.h"
#include <fstream>
#include <vector>

namespace thatboy
{
	// ���Ͷ���
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
	
	// Ĭ��CRC����
	constexpr CRC32::CRC32_TYPE defaultCrcType = CRC32::CRC32_TYPE::eMPEG2;

	// �ϳ���
	inline constexpr WORD makeWORD(BYTE a, BYTE b)
	{
		return (((WORD)(a)) | ((WORD)(b) << 8));
	}
	// �ϳ�˫��
	inline constexpr DWORD makeDWORD(WORD a, WORD b)
	{
		return (((DWORD)(a)) | ((DWORD)(b) << 16));
	}
	// �ϳ�˫��
	inline constexpr DWORD makeDWORD(BYTE a, BYTE b, BYTE c, BYTE d)
	{
		return makeDWORD(makeWORD(a, b), makeWORD(c, d));
	}

	// ���ݿ�
	struct Chunk
	{
		DWORD dataLength = 0;	// ���ݳ���
		DWORD typeCode = 0;		// ����
		DWORD crcCode = 0;		// CRCУ���롾typeCode+data��

	public:
		/******** �ӿ� ********/
		// �ļ�д��
		virtual std::ostream& write(std::ostream&)const;
		// �ļ���ȡ
		virtual std::istream& read(std::istream&);
		// У��CRC
		virtual bool checkCrcCode(BYTE crcEncodeType)const;
		// �������
		virtual void doFigure(BYTE crcEncodeType);
	};

	// ������
	struct SignatureDomain
	{
		enum class ENCRYPT_ATTRIBUTE :BYTE
		{
			NORMAL = 0
			, PASSWORD = 1		// ��Ҫ����
			, DEVICEBIND = 2	// �豸��
		};
		DWORD magicNumber = makeDWORD('T', 'E', 'F', 255);
		DWORD version = makeDWORD(0, 0, 0, 1);
		DWORD chunkCount = 0;												// ���������С
		DWORD oriFileSize = 0;												// ԭʼ�ļ���С
		DWORD deviceIDCrc = 0;												// ���豸IDCRC
		DWORD RXORCode = 0;													// ������־
		BYTE passwordMD5[32] = { NULL };									// ����MD5
		BYTE attributeMark = static_cast<BYTE>(ENCRYPT_ATTRIBUTE::NORMAL);	// ���Ա�־
		BYTE reserve[3] = { NULL };											// ����λ��
		BYTE oriFileName[260] = { NULL };									// ԭʼ�ļ���
	};
}
