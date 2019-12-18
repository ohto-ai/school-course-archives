#include "ThatboyEncrypt.h"

bool thatboy::EncryptFileStream::Encrypt(std::string file, std::string encryptFileName, std::string password, std::string deviceSerial)
{
	using namespace std;

	EncryptFileStream encryptFile;
	size_t fileSize = [](std::string file) {
		ifstream ifs(file, ios::binary);
		size_t fileSize;
		ifs.seekg(0, ios::end);
		fileSize = ifs.tellg();
		ifs.seekg(0);
		ifs.close();
		return fileSize;
	}(file);
	size_t chunkCount = (fileSize - 1) / ChunkDataSize + 1;

	/********************** 文件署名域 **************************/
	ZeroMemory(&encryptFile, sizeof(encryptFile));
	encryptFile.signature.attributeMark = static_cast<BYTE>(password.empty() ? SignatureDomain::ENCRYPT_ATTRIBUTE::NORMAL : SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
		| static_cast<BYTE>(deviceSerial.empty() ? SignatureDomain::ENCRYPT_ATTRIBUTE::NORMAL : SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND);
	encryptFile.signature.magicNumber = makeDWORD('T', 'E', 'F', 255);
	encryptFile.signature.oriFileSize = fileSize;
	encryptFile.signature.version = makeDWORD(0, 0, 0, 1);
	encryptFile.signature.chunkTotalSize = 0;
	encryptFile.signature.RXORCode = makeDWORD(rand() % 256, rand() % 256, rand() % 256, rand() % 256);

	// 密码MD5摘要 设备的CRC校验
	if (encryptFile.signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD)
		memccpy(encryptFile.signature.passwordMD5, md5(password).c_str(), '\0', 32);
	if (encryptFile.signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		encryptFile.signature.deviceIDCrc = crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size());
	}

	// 文件名写入
	char fileNameNoExt[MAX_PATH];
	char ext[MAX_PATH];
	_splitpath(file.c_str(), nullptr, nullptr, fileNameNoExt, ext);
	sprintf((LPSTR)encryptFile.signature.oriFileName, "%s%s", fileNameNoExt, ext);
	for (size_t i = strlen((LPSTR)encryptFile.signature.oriFileName)+1; i < sizeof(encryptFile.signature.oriFileName); i++)
		encryptFile.signature.oriFileName[i] = rand() % 256;
	for (size_t i = 0; i < sizeof(encryptFile.signature.oriFileName) / 4; i++)
		((DWORD_PTR)encryptFile.signature.oriFileName)[i] ^= encryptFile.signature.magicNumber ^ XORCode ^ encryptFile.signature.RXORCode;

	/********************** 文件头块 **************************/
	encryptFile.thdrChunk.doFigure();
	/********************** 文件尾块 **************************/
	encryptFile.tendChunk.doFigure();
	/********************** 数据块 **************************/
	// 分块写入
	ifstream ifs(file, ios::binary);
	std::vector<BYTE> fileContentBuff(ChunkDataSize);
	for (size_t i = 0; i < chunkCount; i++)
	{
		size_t fileContentSize;
		string chunkBuff;

		ifs.read((LPSTR)fileContentBuff.data(), ChunkDataSize);
		fileContentSize = ifs.gcount();
		fileContentBuff.resize(fileContentSize);
		/*********** 加密 ***********/
		Base64::encode(fileContentBuff, chunkBuff);

		encryptFile.dataChunk.push_back(TDAT_Chunk());
		TDAT_Chunk& thisChunk = encryptFile.dataChunk.back();
		thisChunk.compressData.assign(chunkBuff.begin(), chunkBuff.end());

		/************ 混淆 ***********/
		for (size_t i = 0; i < thisChunk.compressData.size()/4; i++)
			((DWORD_PTR)thisChunk.compressData.data())[i] ^= XORCode ^ encryptFile.signature.RXORCode;
		for (size_t i = (thisChunk.compressData.size() / 4) * 4; i < thisChunk.compressData.size(); i++)
			thisChunk.compressData[i] ^= (XORCode ^ encryptFile.signature.RXORCode) && (0XFF << (i % 4 - 1) * 8);


		thisChunk.doFigure(encryptFile.thdrChunk.crcEncodeType);
		encryptFile.signature.chunkTotalSize += thisChunk.dataLength + sizeof(thisChunk.crcCode) + sizeof(thisChunk.dataLength) + sizeof(thisChunk.typeCode);
	}
	ifs.close();

	/********************** 写入文件 **************************/
	ofstream ofs(encryptFileName, ios::binary);
	ofs.write((LPCSTR)&encryptFile.signature, sizeof(encryptFile.signature));
	encryptFile.thdrChunk.write(ofs);
	for (auto& dataChunk : encryptFile.dataChunk)
		dataChunk.write(ofs);
	encryptFile.tendChunk.write(ofs);
	ofs.close();

	return true;
}

bool thatboy::EncryptFileStream::Decrypt(std::string encryptFileName, std::string file, std::string password, std::string deviceSerial)
{
	using namespace std;

	EncryptFileStream encryptFile;
	/********************** 文件署名域 **************************/
	ifstream ifs(encryptFileName, ios::binary);

	ifs.read((LPSTR)&encryptFile.signature, sizeof(encryptFile.signature));

	// 密码MD5摘要 设备的CRC校验
	if (encryptFile.signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::PASSWORD
		&& memcmp(md5(password).c_str(), encryptFile.signature.passwordMD5, 32))
		return false;
	if (encryptFile.signature.attributeMark & (BYTE)SignatureDomain::ENCRYPT_ATTRIBUTE::DEVICEBIND)
	{
		CRC32 crc(CRC32::CRC32_TYPE::eMPEG2);
		if (encryptFile.signature.deviceIDCrc != crc.crcCompute((BYTE_CPTR)deviceSerial.c_str(), deviceSerial.size()))
			return false;
	}

	// 文件名
	for (size_t i = 0; i < sizeof(encryptFile.signature.oriFileName) / 4; i++)
		((DWORD_PTR)encryptFile.signature.oriFileName)[i] ^= encryptFile.signature.magicNumber ^ XORCode ^ encryptFile.signature.RXORCode;
	if (file.empty())
		file = (LPCSTR)encryptFile.signature.oriFileName;

	/********************** 文件头块 **************************/
	encryptFile.thdrChunk.read(ifs);
	/********************** 数据块 **************************/
	// 分块写入
	ofstream ofs(file, ios::binary);
	vector<BYTE> fileContentBuff;
	DWORD dataChunkType = makeDWORD('T', 'D', 'A', 'T');
	auto getChunkType = [](ifstream& ifs)
	{
		DWORD chunkType;
		ifs.seekg(4, ios::cur);
		ifs.read((LPTSTR)&chunkType, sizeof(chunkType));
		ifs.seekg(-8, ios::cur);
		return chunkType;
	};
	while (getChunkType(ifs)== dataChunkType)
	{
		encryptFile.dataChunk.push_back(TDAT_Chunk());
		auto& dataChunk = encryptFile.dataChunk.back();
		dataChunk.read(ifs);

		// CRC校验失败
		if (!dataChunk.checkCrcCode(encryptFile.thdrChunk.crcEncodeType))
			return false;
		/*********** 解密 ***********/
		string codeData(dataChunk.compressData.begin(), dataChunk.compressData.end());

		/************ 反混淆 ***********/
		for (size_t i = 0; i < codeData.size() / 4; i++)
			((DWORD_PTR)codeData.data())[i] ^= XORCode ^ encryptFile.signature.RXORCode;
		for (size_t i = (codeData.size() / 4) * 4; i < codeData.size(); i++)
			codeData[i] ^= (XORCode ^ encryptFile.signature.RXORCode) && (0XFF << (i % 4 - 1) * 8);


		Base64::decode(codeData, fileContentBuff);
		ofs.write((LPCSTR)fileContentBuff.data(), fileContentBuff.size());
	}
	ofs.close();
	ifs.close();

	return true;
}
