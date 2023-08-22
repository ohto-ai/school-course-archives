#pragma once

#include "ThatboyCriticalChunk.h"
#include "Base64.h"
#include "USBMassStorageDeviceSerial.h"
#include <functional>

namespace thatboy
{
	namespace EncryptFileDoModal
	{
		enum class EncryptErrorCode
		{
			ENCRYPT_SUCCESS				// �ɹ�
			, ENCRYPT_TERMINOL			// ��ֹ
			, ENCRYPT_FILEOPENERROR		// �ļ��򿪴���
			, ENCRYPT_FILETYPEERROR		// �ļ����ʹ���
			, ENCRYPT_VERSIONNOTMATCH	// �汾��ƥ��
			, ENCRYPT_PASSWORDNOTMATCH	// ���벻ƥ��
			, ENCRYPT_DEVICENOTMATCH	// �豸��ƥ��
			, ENCRYPT_NEEDPASSWORD		// ��Ҫ����
			, ENCRYPT_NEEDDEVICE		// ��Ҫ�豸
			, ENCRYPT_CRCCHECKFAILURE 	// CRCУ��ʧ��
			, ENCRYPT_BASE64ERROR		// Base64�������
			, ENCRYPT_ERRORCHUNK	 	// ��������
			, ENCRYPT_UNKNOWCHUNK	 	// δ֪����
			, ENCRYPT_UNKNOWERROR		// δ֪����
		};

		constexpr size_t defaultChunkDataSize = 3 * 4 * 256;	// ����base64���룬ͬʱ4�ֽڶ���
		constexpr DWORD XORCode = 0B101010101010101010101010;

		// ����false��ʾ��ֹ����/����
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
