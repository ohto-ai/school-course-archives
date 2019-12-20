#include "pch.h"
#include "CRC.h"

template <typename TYPE>
void thatboy::CRC<TYPE>::crcInit(void)
{
	TYPE remainder;
	TYPE dividend;
	int bit;
	/* 执行二进制长除法，一次一位。 */
	for (dividend = 0; dividend < 256; dividend++)
	{
		/* 初始化其余部分。  */
		remainder = dividend << (m_width - 8);
		/* 用多项式进行移位和异或运算。   */
		for (bit = 0; bit < 8; bit++)
		{
			/* 尝试分割当前数据位。  */
			if (remainder & m_topbit)
			{
				remainder = (remainder << 1) ^ m_polynomial;
			}
			else
			{
				remainder = remainder << 1;
			}
		}
		/* 保存结果 */
		crcTable[dividend] = remainder;
	}
}

thatboy::CRC8::CRC8(CRC8_TYPE type)
{
	switch (type)
	{
	case CRC8_TYPE::eCRC8:
		m_polynomial = 0x07;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eAUTOSAR:
		m_polynomial = 0x2f;
		m_initial_remainder = 0xff;
		m_final_xor_value = 0xff;
		break;
	case CRC8_TYPE::eCDMA2000:
		m_polynomial = 0x9b;
		m_initial_remainder = 0xFF;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eDARC:
		m_polynomial = 0x39;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eDVB_S2:
		m_polynomial = 0xd5;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eEBU:
	case CRC8_TYPE::eAES:
		m_polynomial = 0x1d;
		m_initial_remainder = 0xFF;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eGSM_A:
		m_polynomial = 0x1d;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eGSM_B:
		m_polynomial = 0x49;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0xFF;
		break;
	case CRC8_TYPE::eI_CODE:
		m_polynomial = 0x1d;
		m_initial_remainder = 0xFD;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eITU:
		m_polynomial = 0x07;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x55;
		break;
	case CRC8_TYPE::eLTE:
		m_polynomial = 0x9b;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eMAXIM:
		m_polynomial = 0x31;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eOPENSAFETY:
		m_polynomial = 0x2f;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eROHC:
		m_polynomial = 0x07;
		m_initial_remainder = 0xff;
		m_final_xor_value = 0x00;
		break;
	case CRC8_TYPE::eSAE_J1850:
		m_polynomial = 0x1d;
		m_initial_remainder = 0xff;
		m_final_xor_value = 0xff;
		break;
	case CRC8_TYPE::eWCDMA:
		m_polynomial = 0x9b;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	default:
		m_polynomial = 0x07;
		m_initial_remainder = 0x00;
		m_final_xor_value = 0x00;
		break;
	}
	crcInit();
}

thatboy::CRC16::CRC16(CRC16_TYPE type)
{
	switch (type)
	{
	case CRC16_TYPE::eCCITT_FALSE:
	case CRC16_TYPE::eMCRF4XX:
		m_polynomial = 0x1021;
		m_initial_remainder = 0xFFFF;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eIBM:
	case CRC16_TYPE::eARC:
	case CRC16_TYPE::eLHA:
	case CRC16_TYPE::eBUYPASS:
	case CRC16_TYPE::eVERIFONE:
	case CRC16_TYPE::eUMTS:
		m_polynomial = 0x8005;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eSPI_FUJITSU:
		m_polynomial = 0x1021;
		m_initial_remainder = 0x1d0f;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eCCITT:
	case CRC16_TYPE::eKERMIT:
	case CRC16_TYPE::eXMODEM:
	case CRC16_TYPE::eZMODEM:
	case CRC16_TYPE::eACORN:
	case CRC16_TYPE::eLTE:
		m_polynomial = 0x1021;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eCDMA2000:
		m_polynomial = 0xc867;
		m_initial_remainder = 0xffff;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eCMS:
	case CRC16_TYPE::eMODBUS:
		m_polynomial = 0x8005;
		m_initial_remainder = 0xffff;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eDDS_110:
		m_polynomial = 0x8005;
		m_initial_remainder = 0x800d;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eDECT_R:
		m_polynomial = 0x0589;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0001;
		break;
	case CRC16_TYPE::eDECT_X:
		m_polynomial = 0x0589;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eDNP:
	case CRC16_TYPE::eEN_13757:
		m_polynomial = 0x3d65;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eGENIBUS:
	case CRC16_TYPE::eEPC:
	case CRC16_TYPE::eDARC:
	case CRC16_TYPE::eI_CODE:
	case CRC16_TYPE::eX_25:
	case CRC16_TYPE::eCRC_B:
	case CRC16_TYPE::eISO_HDLC:
	case CRC16_TYPE::eIBM_SDLC:
		m_polynomial = 0x1021;
		m_initial_remainder = 0xffff;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eGSM:
		m_polynomial = 0x1021;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eLJ1200:
		m_polynomial = 0x6f63;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eMAXIM:
		m_polynomial = 0x8005;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eOPENSAFETY_A:
		m_polynomial = 0x5935;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eOPENSAFETY_B:
		m_polynomial = 0x755b;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::ePROFIBUS:
	case CRC16_TYPE::eIEC_61158_2:
		m_polynomial = 0x1dcf;
		m_initial_remainder = 0xffff;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eRIELLO:
		m_polynomial = 0x1021;
		m_initial_remainder = 0xb2aa;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eT10_DIF:
		m_polynomial = 0x8bb7;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eTELEDISK:
		m_polynomial = 0xa097;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eTMS37157:
		m_polynomial = 0x1021;
		m_initial_remainder = 0x89ec;
		m_final_xor_value = 0x0000;
		break;
	case CRC16_TYPE::eUSB:
		m_polynomial = 0x8005;
		m_initial_remainder = 0xffff;
		m_final_xor_value = 0xffff;
		break;
	case CRC16_TYPE::eCRC_A:
		m_polynomial = 0x1021;
		m_initial_remainder = 0xc6c6;
		m_final_xor_value = 0x0000;
		break;
	default:
		m_polynomial = 0x8005;
		m_initial_remainder = 0x0000;
		m_final_xor_value = 0x0000;
		break;
	}
	crcInit();
}

thatboy::CRC32::CRC32(CRC32_TYPE type)
{
	switch (type)
	{
	case CRC32_TYPE::eADCCP:
	case CRC32_TYPE::ePKZIP:
	case CRC32_TYPE::eCRC32:
	case CRC32_TYPE::eBZIP2:
	case CRC32_TYPE::eAAL5:
	case CRC32_TYPE::eDECT_B:
	case CRC32_TYPE::eB_CRC32:
		m_polynomial = 0x04c11db7;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	case CRC32_TYPE::eAUTOSAR:
		m_polynomial = 0xf4acfb13;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	case CRC32_TYPE::eCRC32C:
		m_polynomial = 0x1edc6f41;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	case CRC32_TYPE::eCRC32D:
		m_polynomial = 0xa833982b;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	case CRC32_TYPE::eMPEG2:
	case CRC32_TYPE::eJAMCRC:
		m_polynomial = 0x04c11db7;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0x00000000;
		break;
	case CRC32_TYPE::ePOSIX:
	case CRC32_TYPE::eCKSUM:
		m_polynomial = 0x04c11db7;
		m_initial_remainder = 0x00000000;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	case CRC32_TYPE::eCRC32Q:
		m_polynomial = 0x814141ab;
		m_initial_remainder = 0x00000000;
		m_final_xor_value = 0x00000000;
		break;
	case CRC32_TYPE::eXFER:
		m_polynomial = 0x000000af;
		m_initial_remainder = 0x00000000;
		m_final_xor_value = 0x00000000;
		break;
	default:
		m_polynomial = 0x04C11DB7;
		m_initial_remainder = 0xFFFFFFFF;
		m_final_xor_value = 0xFFFFFFFF;
		break;
	}
	crcInit();
}