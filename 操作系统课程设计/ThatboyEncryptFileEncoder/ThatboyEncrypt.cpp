
#include "pch.h"
#include "ThatboyEncrypt.h"

std::function<bool(int, int)> thatboy::EncryptFileDoModal::callBackSetProcessBarRange;
std::function<bool(int)> thatboy::EncryptFileDoModal::callBackSetProcessBarPos;
std::function<bool(std::string)> thatboy::EncryptFileDoModal::callBackStatusUpdate;


thatboy::EncryptFileDoModal::EncryptErrorCode thatboy::EncryptFileDoModal::Encrypt(
	std::string file				// �����ļ�·��
	, std::string encryptFileName	// ����ļ�·��
	, std::string password			// ����=""
	, std::string deviceSerial		// �豸���к�=""
	, DWORD chunkDataSize			// ���С=defaultChunkDataSize
	, CRC32::CRC32_TYPE crcType		// CRCУ������=eMPEG2
	, bool flushChunkWrite			// ǿ��ˢ�������
)	
{
	using namespace std;
#define callBackSetProcessBarRange(a,b) if(callBackSetProcessBarRange) if(!callBackSetProcessBarRange(a,b)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackSetProcessBarPos(a) if(callBackSetProcessBarPos) if(!callBackSetProcessBarPos(a)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackStatusUpdate(s) if(callBackStatusUpdate) if(!callBackStatusUpdate(s)) return EncryptErrorCode::ENCRYPT_TERMINOL;

	callBackStatusUpdate("����׼����...");
	callBackSetProcessBarPos(0);

	SignatureDomain signature;
	THDR_Chunk thdrChunk;
	TEND_Chunk tendChunk;
	TDAT_Chunk tdatChunk;


	DWORD pwdCRC = 0;
	size_t fileSize = [](std::string file) {
		ifstream ifs(file, ios::binary);
		size_t fileSize;
		ifs.seekg(0, ios::end);
		fileSize = static_cast<size_t>(ifs.tellg());
		ifs.seekg(0);
		ifs.close();
		return fileSize;
	}(file);
	/********************** �ļ������� **************************/
	signature.attributeMark = static_cast<BYTE>(password.empty() ? SignatureDomain::ENCRYPT_ATTRIBUTE::NORMAL : SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
		| static_cast<BYTE>(deviceSerial.empty() ? SignatureDomain::ENCRYPT_ATTRIBUTE::NORMAL : SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND);
	signature.magicNumber = makeDWORD('T', 'E', 'F', 255);
	signature.oriFileSize = fileSize;
	signature.version = makeDWORD(0, 0, 0, 1);
	signature.chunkCount = (fileSize - 1) / chunkDataSize + 1;
	signature.RXORCode = makeDWORD(rand() % 256, rand() % 256, rand() % 256, rand() % 256);

	auto chunkCountToProcessPos = [&signature](int x)->int
	{
		return x * 100 / signature.chunkCount;
	};

	callBackSetProcessBarRange(0, chunkCountToProcessPos(signature.chunkCount));

	// ����MD5ժҪ �豸��CRCУ��
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD) {
		callBackStatusUpdate("��������ժҪ��Ϣ...");
		_memccpy(signature.passwordMD5, md5(password).c_str(), '\0', 32);
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		pwdCRC= crc.crcCompute((BYTE_CPTR)password.c_str(), password.size());
	}
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		callBackStatusUpdate("���豸...");
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		signature.deviceIDCrc = crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size());
	}

	// �ļ���д��
	callBackStatusUpdate("����ԭʼ�ļ���...");
	char fileNameNoExt[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath_s(file.c_str(), nullptr, 0, nullptr, 0, fileNameNoExt, MAX_PATH, ext, MAX_PATH);
	sprintf_s((LPSTR)signature.oriFileName, MAX_PATH, "%s%s", fileNameNoExt, ext);
	for (size_t i = strlen((LPSTR)signature.oriFileName)+1; i < sizeof(signature.oriFileName); i++)
		signature.oriFileName[i] = rand() % 256;
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;


	callBackStatusUpdate("���ڴ����ļ�����...");
	// �ֿ�д��
	ifstream ifs(file, ios::binary, _SH_DENYWR);
	ofstream ofs(encryptFileName, ios::binary, _SH_DENYRW);

	if (!ifs.is_open() || !ofs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	/********************** �ļ������� **************************/
	ofs.write((LPCSTR)&signature, sizeof(signature));
	/********************** �ļ�ͷ�� **************************/
	thdrChunk.doFigure(static_cast<BYTE>(crcType));
	thdrChunk.write(ofs);
	ofs.flush();
	callBackStatusUpdate("��д����������ļ�ͷ...");
	/********************** ���ݿ� **************************/
	std::vector<BYTE> fileContentBuff(chunkDataSize);
	DWORD curXORCode = XORCode ^ signature.RXORCode ^ pwdCRC;


	callBackStatusUpdate("���ڴ������ݿ飬�����ĵȴ�...");
	for (size_t i = 0; i < signature.chunkCount; i++)
	{
		size_t fileContentSize;
		string chunkBuff;

		fileContentBuff.resize(chunkDataSize);
		ifs.read((LPSTR)fileContentBuff.data(), chunkDataSize);
		fileContentSize = static_cast<size_t>(ifs.gcount());
		fileContentBuff.resize(fileContentSize);
		/*********** ���� ***********/
		if (!Base64::encode(fileContentBuff, chunkBuff))
			return EncryptErrorCode::ENCRYPT_BASE64ERROR;

		tdatChunk.compressData.assign(chunkBuff.begin(), chunkBuff.end());

		/************ ���� ***********/
		for (size_t i = 0; i < tdatChunk.compressData.size() / 4; i++)
			((DWORD_PTR)tdatChunk.compressData.data())[i] ^= curXORCode;
		for (size_t i = (tdatChunk.compressData.size() / 4) * 4; i < tdatChunk.compressData.size(); i++)
			tdatChunk.compressData[i] ^= curXORCode && (0XFF << (i % 4 - 1) * 8);

		tdatChunk.doFigure(thdrChunk.crcEncodeType);
		tdatChunk.write(ofs);
		if (flushChunkWrite)
			ofs.flush();

		callBackSetProcessBarPos(chunkCountToProcessPos(i + 1));
	}
	callBackSetProcessBarPos(chunkCountToProcessPos(signature.chunkCount));
	callBackStatusUpdate("�ļ����ݼ�����ɡ�");
	ifs.close();
	/********************** �ļ�β�� **************************/
	tendChunk.doFigure(thdrChunk.crcEncodeType);
	tendChunk.write(ofs);
	ofs.close();

	return EncryptErrorCode::ENCRYPT_SUCCESS;


#undef callBackSetProcessBarRange
#undef callBackSetProcessBarPos
#undef callBackStatusUpdate
}

thatboy::EncryptFileDoModal::EncryptErrorCode thatboy::EncryptFileDoModal::Decrypt(
	std::string encryptFileName
	, std::string file
	, std::string password
	, std::string deviceSerial
	, bool flushChunkWrite
)
{
	using namespace std;

#define callBackSetProcessBarRange(a,b) if(callBackSetProcessBarRange) if(!callBackSetProcessBarRange(a,b)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackSetProcessBarPos(a) if(callBackSetProcessBarPos) if(!callBackSetProcessBarPos(a)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackStatusUpdate(s) if(callBackStatusUpdate) if(!callBackStatusUpdate(s)) return EncryptErrorCode::ENCRYPT_TERMINOL;

	callBackStatusUpdate("����׼����...");
	callBackSetProcessBarPos(0);

	SignatureDomain signature;
	THDR_Chunk thdrChunk;
	TEND_Chunk tendChunk;
	TDAT_Chunk tdatChunk;

	DWORD pwdCRC = 0;
	/********************** �ļ������� **************************/
	ifstream ifs(encryptFileName, ios::binary, _SH_DENYWR);
	if (!ifs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	ifs.read((LPSTR)&signature, sizeof(signature));

	// ����ļ����ͺͰ汾
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return EncryptErrorCode::ENCRYPT_FILETYPEERROR;
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH;

	auto chunkCountToProcessPos = [&signature](int x)->int
	{
		return x * 100 / signature.chunkCount;
	};
	callBackSetProcessBarRange(0, chunkCountToProcessPos(signature.chunkCount));

	// ����MD5ժҪ �豸��CRCУ��
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
	{
		callBackStatusUpdate("��֤����ժҪ��Ϣ...");
		if (password.empty())
			return EncryptErrorCode::ENCRYPT_NEEDPASSWORD;
		if (memcmp(md5(password).c_str(), signature.passwordMD5, 32))
			return EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH;

		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		pwdCRC = crc.crcCompute((BYTE_CPTR)password.c_str(), password.size());
	}
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		callBackStatusUpdate("��֤�豸...");
		if (deviceSerial.empty())
			return EncryptErrorCode::ENCRYPT_NEEDDEVICE;
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		if (signature.deviceIDCrc != crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size()))
			return EncryptErrorCode::ENCRYPT_DEVICENOTMATCH;
	}

	// �ļ���
	callBackStatusUpdate("����ԭʼ�ļ���...");
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;
	if (file.empty())
		file = (LPCSTR)signature.oriFileName;

	callBackStatusUpdate("���ڴ����ļ�����...");
	/********************** �ļ�ͷ�� **************************/
	thdrChunk.read(ifs);
	if (!thdrChunk.checkCrcCode(thdrChunk.crcEncodeType))
		return EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE;
	/********************** ���ݿ� **************************/
	// �ֿ�д��
	ofstream ofs(file, ios::binary, _SH_DENYRW);
	if (!ofs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;
	vector<BYTE> fileContentBuff;
	auto getChunkType = [](ifstream& ifs)
	{
		DWORD chunkType;
		ifs.seekg(4, ios::cur);
		ifs.read((LPTSTR)&chunkType, sizeof(chunkType));
		ifs.seekg(-8, ios::cur);
		return chunkType;
	};
	DWORD curXORCode = XORCode ^ signature.RXORCode ^ pwdCRC;

	callBackStatusUpdate("���ڴ������ݿ飬�����ĵȴ�...");
	int curChunkPtr = 0;
	while (getChunkType(ifs)== TDAT_Chunk::dataChunkType)
	{
		DWORD thisChunkType = getChunkType(ifs);
		if (thisChunkType == TEND_Chunk::endChunkType)
			break;
		else if (thisChunkType == TEND_Chunk::endChunkType)
			return EncryptErrorCode::ENCRYPT_ERRORCHUNK;
		else if (thisChunkType != TDAT_Chunk::dataChunkType)
			return EncryptErrorCode::ENCRYPT_UNKNOWCHUNK;

		tdatChunk.read(ifs);

		// CRCУ��ʧ��
		if (!tdatChunk.checkCrcCode(thdrChunk.crcEncodeType))
			return EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE;
		/*********** ���� ***********/
		string codeData(tdatChunk.compressData.begin(), tdatChunk.compressData.end());

		/************ ������ ***********/
		for (size_t i = 0; i < codeData.size() / 4; i++)
			((DWORD_PTR)codeData.data())[i] ^= curXORCode;
		for (size_t i = (codeData.size() / 4) * 4; i < codeData.size(); i++)
			codeData[i] ^= curXORCode && (0XFF << (i % 4 - 1) * 8);

		if (!Base64::decode(codeData, fileContentBuff))
			return EncryptErrorCode::ENCRYPT_BASE64ERROR;
		ofs.write((LPCSTR)fileContentBuff.data(), fileContentBuff.size());

		if (flushChunkWrite)
			ofs.flush();
		callBackSetProcessBarPos(chunkCountToProcessPos(++curChunkPtr));
	}callBackSetProcessBarPos(chunkCountToProcessPos(signature.chunkCount));
	callBackStatusUpdate("�ļ����ݽ�����ɡ�");
	ofs.close();
	ifs.close();

	return EncryptErrorCode::ENCRYPT_SUCCESS;
}

thatboy::EncryptFileDoModal::EncryptErrorCode thatboy::EncryptFileDoModal::Verify(std::string encryptFileName, std::string password, std::string deviceSerial)
{
	using namespace std;

	SignatureDomain signature;
	/********************** �ļ������� **************************/
	ifstream ifs(encryptFileName, ios::binary);
	if (!ifs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	ifs.read((LPSTR)&signature, sizeof(signature));
	ifs.close();

	// ����ļ����ͺͰ汾
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return EncryptErrorCode::ENCRYPT_FILETYPEERROR;
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH;

	// ����MD5ժҪ �豸��CRCУ��
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
	{
		if (password.empty())
			return EncryptErrorCode::ENCRYPT_NEEDPASSWORD;
		if (memcmp(md5(password).c_str(), signature.passwordMD5, 32))
			return EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH;
	}
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		if (deviceSerial.empty())
			return EncryptErrorCode::ENCRYPT_NEEDDEVICE;
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		if (signature.deviceIDCrc != crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size()))
			return EncryptErrorCode::ENCRYPT_DEVICENOTMATCH;
	}
	return EncryptErrorCode::ENCRYPT_SUCCESS;

#undef callBackSetProcessBarRange
#undef callBackSetProcessBarPos
#undef callBackStatusUpdate
}

std::string thatboy::EncryptFileDoModal::getEncryptFileOriginalFilename(std::string encryptFileName)
{
	using namespace std;

	SignatureDomain signature;
	/********************** �ļ������� **************************/
	ifstream ifs(encryptFileName, ios::binary);
	if (!ifs.is_open())
		return "";
	ifs.read((LPSTR)&signature, sizeof(signature));
	ifs.close();
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return "";
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return "";
	// �ļ���
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;

	return (LPCSTR)signature.oriFileName;
}
