#pragma once

#include "ThatboyCriticalChunk.h"
#include "Base64.h"
#include "USBMassStorageDeviceSerial.h"
#include <functional>

namespace thatboy
{
	namespace EncryptFileDoModal
	{
		enum EncryptErrorCode
		{
			ENCRYPT_SUCCESS				// 成功
			, ENCRYPT_TERMINOL			// 终止
			, ENCRYPT_FILEOPENERROR		// 文件打开错误
			, ENCRYPT_FILETYPEERROR		// 文件类型错误
			, ENCRYPT_VERSIONNOTMATCH	// 版本不匹配
			, ENCRYPT_PASSWORDNOTMATCH	// 密码不匹配
			, ENCRYPT_DEVICENOTMATCH	// 设备不匹配
			, ENCRYPT_NEEDPASSWORD		// 需要密码
			, ENCRYPT_NEEDDEVICE		// 需要设备
			, ENCRYPT_CRCCHECKFAILURE 	// CRC校验失败
			, ENCRYPT_BASE64ERROR		// Base64解码错误
			, ENCRYPT_ERRORCHUNK	 	// 错误区块
			, ENCRYPT_UNKNOWCHUNK	 	// 未知区块
			, ENCRYPT_UNKNOWERROR		// 未知错误
		};
		constexpr size_t defaultChunkDataSize = 3 * 4 * 256;	// 方便base64编码，同时4字节对齐
		constexpr DWORD XORCode = 0B101010101010101010101010;

		// 返回false表示终止加密/解密
		extern std::function<bool(int, int)> callBackSetProcessBarRange;
		extern std::function<bool(int)> callBackSetProcessBarPos;
		extern std::function<bool(std::string)> callBackStatusUpdate;

		EncryptErrorCode Encrypt(
			std::string file
			, std::string encryptFile
			, std::string password = ""
			, std::string deviceSerial = ""
			, DWORD chunkDataSize = defaultChunkDataSize
			, CRC32::CRC32_TYPE crcType = CRC32::CRC32_TYPE::eMPEG2
			, bool flushChunkWrite = true
		);
		EncryptErrorCode Decrypt(
			std::string encryptFile
			, std::string file = ""
			, std::string password = ""
			, std::string deviceSerial = ""
			, bool flushChunkWrite = true
		);
		EncryptErrorCode Verify(
			std::string encryptFile
			, std::string password = ""
			, std::string deviceSerial = "");
		std::string getEncryptFileOriginalFilename(std::string encryptFile);
	};
}
