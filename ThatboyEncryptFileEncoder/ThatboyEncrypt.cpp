#include "pch.h"
#include "ThatboyEncrypt.h"

std::function<bool(int, int)> thatboy::EncryptFileDoModal::callBackSetProcessBarRange;
std::function<bool(int)> thatboy::EncryptFileDoModal::callBackSetProcessBarPos;
std::function<bool(std::string)> thatboy::EncryptFileDoModal::callBackStatusUpdate;

thatboy::EncryptFileDoModal::EncryptErrorCode thatboy::EncryptFileDoModal::Encrypt(
	std::string file				// 输入文件路径
	, std::string encryptFileName	// 输出文件路径
	, std::string password			// 密码=""
	, std::string deviceSerial		// 设备序列号=""
	, DWORD chunkDataSize			// 块大小=defaultChunkDataSize
	, CRC32::CRC32_TYPE crcType		// CRC校验类型=eMPEG2
	, bool flushChunkWrite			// 强制刷新输出块
)
{
	using namespace std;
#define callBackSetProcessBarRange(a,b) if(callBackSetProcessBarRange) if(!callBackSetProcessBarRange(a,b)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackSetProcessBarPos(a) if(callBackSetProcessBarPos) if(!callBackSetProcessBarPos(a)) return EncryptErrorCode::ENCRYPT_TERMINOL;
#define callBackStatusUpdate(s) if(callBackStatusUpdate) if(!callBackStatusUpdate(s)) return EncryptErrorCode::ENCRYPT_TERMINOL;

	callBackStatusUpdate("加密准备中...");
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
	/********************** 文件署名域 **************************/
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

	// 密码MD5摘要 设备的CRC校验
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD) {
		callBackStatusUpdate("生成密码摘要信息...");
		_memccpy(signature.passwordMD5, md5(password).c_str(), '\0', 32);
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		pwdCRC = crc.crcCompute((BYTE_CPTR)password.c_str(), password.size());
	}
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		callBackStatusUpdate("绑定设备...");
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		signature.deviceIDCrc = crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size());
	}

	// 文件名写入
	callBackStatusUpdate("处理原始文件名...");
	char fileNameNoExt[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath_s(file.c_str(), nullptr, 0, nullptr, 0, fileNameNoExt, MAX_PATH, ext, MAX_PATH);
	sprintf_s((LPSTR)signature.oriFileName, MAX_PATH, "%s%s", fileNameNoExt, ext);
	for (size_t i = strlen((LPSTR)signature.oriFileName) + 1; i < sizeof(signature.oriFileName); i++)
		signature.oriFileName[i] = rand() % 256;
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;

	callBackStatusUpdate("正在处理文件内容...");
	// 分块写入
	ifstream ifs(file, ios::binary, _SH_DENYWR);
	ofstream ofs(encryptFileName, ios::binary, _SH_DENYRW);

	if (!ifs.is_open() || !ofs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	/********************** 文件署名域 **************************/
	ofs.write((LPCSTR)&signature, sizeof(signature));
	/********************** 文件头块 **************************/
	thdrChunk.doFigure(static_cast<BYTE>(crcType));
	thdrChunk.write(ofs);
	ofs.flush();
	callBackStatusUpdate("已写入署名域和文件头...");
	/********************** 数据块 **************************/
	std::vector<BYTE> fileContentBuff(chunkDataSize);
	DWORD curXORCode = XORCode ^ signature.RXORCode ^ pwdCRC;

	callBackStatusUpdate("正在处理数据块，请耐心等待...");
	for (size_t i = 0; i < signature.chunkCount; i++)
	{
		size_t fileContentSize;
		string chunkBuff;

		fileContentBuff.resize(chunkDataSize);
		ifs.read((LPSTR)fileContentBuff.data(), chunkDataSize);
		fileContentSize = static_cast<size_t>(ifs.gcount());
		fileContentBuff.resize(fileContentSize);
		/*********** 加密 ***********/
		if (!Base64::encode(fileContentBuff, chunkBuff))
			return EncryptErrorCode::ENCRYPT_BASE64ERROR;

		tdatChunk.compressData.assign(chunkBuff.begin(), chunkBuff.end());

		/************ 混淆 ***********/
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
	callBackStatusUpdate("文件数据加密完成。");
	ifs.close();
	/********************** 文件尾块 **************************/
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

	callBackStatusUpdate("解密准备中...");
	callBackSetProcessBarPos(0);

	SignatureDomain signature;
	THDR_Chunk thdrChunk;
	TEND_Chunk tendChunk;
	TDAT_Chunk tdatChunk;

	DWORD pwdCRC = 0;
	/********************** 文件署名域 **************************/
	ifstream ifs(encryptFileName, ios::binary, _SH_DENYWR);
	if (!ifs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	ifs.read((LPSTR)&signature, sizeof(signature));

	// 检测文件类型和版本
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return EncryptErrorCode::ENCRYPT_FILETYPEERROR;
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH;

	auto chunkCountToProcessPos = [&signature](int x)->int
	{
		return x * 100 / signature.chunkCount;
	};
	callBackSetProcessBarRange(0, chunkCountToProcessPos(signature.chunkCount));

	// 密码MD5摘要 设备的CRC校验
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
	{
		callBackStatusUpdate("验证密码摘要信息...");
		if (password.empty())
			return EncryptErrorCode::ENCRYPT_NEEDPASSWORD;
		if (memcmp(md5(password).c_str(), signature.passwordMD5, 32))
			return EncryptErrorCode::ENCRYPT_PASSWORDNOTMATCH;

		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		pwdCRC = crc.crcCompute((BYTE_CPTR)password.c_str(), password.size());
	}
	if (signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		callBackStatusUpdate("验证设备...");
		if (deviceSerial.empty())
			return EncryptErrorCode::ENCRYPT_NEEDDEVICE;
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		if (signature.deviceIDCrc != crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size()))
			return EncryptErrorCode::ENCRYPT_DEVICENOTMATCH;
	}

	// 文件名
	callBackStatusUpdate("解析原始文件名...");
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;
	if (file.empty())
		file = (LPCSTR)signature.oriFileName;

	callBackStatusUpdate("正在处理文件内容...");
	/********************** 文件头块 **************************/
	thdrChunk.read(ifs);
	if (!thdrChunk.checkCrcCode(thdrChunk.crcEncodeType))
		return EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE;
	/********************** 数据块 **************************/
	// 分块写入
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

	callBackStatusUpdate("正在处理数据块，请耐心等待...");
	int curChunkPtr = 0;
	while (getChunkType(ifs) == TDAT_Chunk::dataChunkType)
	{
		DWORD thisChunkType = getChunkType(ifs);
		if (thisChunkType == TEND_Chunk::endChunkType)
			break;
		else if (thisChunkType == TEND_Chunk::endChunkType)
			return EncryptErrorCode::ENCRYPT_ERRORCHUNK;
		else if (thisChunkType != TDAT_Chunk::dataChunkType)
			return EncryptErrorCode::ENCRYPT_UNKNOWCHUNK;

		tdatChunk.read(ifs);

		// CRC校验失败
		if (!tdatChunk.checkCrcCode(thdrChunk.crcEncodeType))
			return EncryptErrorCode::ENCRYPT_CRCCHECKFAILURE;
		/*********** 解密 ***********/
		string codeData(tdatChunk.compressData.begin(), tdatChunk.compressData.end());

		/************ 反混淆 ***********/
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
	callBackStatusUpdate("文件数据解密完成。");
	ofs.close();
	ifs.close();

	return EncryptErrorCode::ENCRYPT_SUCCESS;
}

thatboy::EncryptFileDoModal::EncryptErrorCode thatboy::EncryptFileDoModal::Verify(std::string encryptFileName, std::string password, std::string deviceSerial)
{
	using namespace std;

	SignatureDomain signature;
	/********************** 文件署名域 **************************/
	ifstream ifs(encryptFileName, ios::binary);
	if (!ifs.is_open())
		return EncryptErrorCode::ENCRYPT_FILEOPENERROR;

	ifs.read((LPSTR)&signature, sizeof(signature));
	ifs.close();

	// 检测文件类型和版本
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return EncryptErrorCode::ENCRYPT_FILETYPEERROR;
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return EncryptErrorCode::ENCRYPT_VERSIONNOTMATCH;

	// 密码MD5摘要 设备的CRC校验
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
	/********************** 文件署名域 **************************/
	ifstream ifs(encryptFileName, ios::binary);
	if (!ifs.is_open())
		return "";
	ifs.read((LPSTR)&signature, sizeof(signature));
	ifs.close();
	if (signature.magicNumber != makeDWORD('T', 'E', 'F', 255))
		return "";
	if (signature.version != makeDWORD(0, 0, 0, 1))
		return "";
	// 文件名
	for (size_t i = 0; i < sizeof(signature.oriFileName) / 4; i++)
		((DWORD_PTR)signature.oriFileName)[i] ^= signature.magicNumber ^ XORCode ^ signature.RXORCode;

	return (LPCSTR)signature.oriFileName;
}