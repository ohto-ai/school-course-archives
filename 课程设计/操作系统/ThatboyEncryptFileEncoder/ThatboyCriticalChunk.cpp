
#include "pch.h"
#include "ThatboyCriticalChunk.h"

/********************************** THDR **********************************/

thatboy::THDR_Chunk::THDR_Chunk()
{
	Chunk::dataLength = sizeof(crcEncodeType) + sizeof(reserve);
	Chunk::typeCode = hdrChunkType;
	Chunk::crcCode = 0;
	crcEncodeType = static_cast<BYTE>(CRC32::CRC32_TYPE::eMPEG2);
	reserve[0] = reserve[1] = reserve[2] = 0;
}

std::ostream& thatboy::THDR_Chunk::write(std::ostream& os)const
{
	Chunk::write(os);
	os.write((LPCSTR)&crcEncodeType, sizeof(crcEncodeType));
	os.write((LPCSTR)reserve, sizeof(reserve));
	return os;
}

std::istream& thatboy::THDR_Chunk::read(std::istream& is)
{
	Chunk::read(is);
	is.read((LPSTR)&crcEncodeType, sizeof(crcEncodeType));
	is.read((LPSTR)reserve, sizeof(reserve));
	return is;
}

bool thatboy::THDR_Chunk::checkCrcCode(BYTE crcEncodeType) const
{
	THDR_Chunk NChunk(*this);
	NChunk.doFigure(crcEncodeType);
	return NChunk.crcCode == crcCode;
}

void thatboy::THDR_Chunk::doFigure(BYTE crcType)
{
	Chunk::dataLength = sizeof(crcEncodeType) + sizeof(reserve);
	Chunk::typeCode = hdrChunkType;
	crcEncodeType = static_cast<BYTE>(CRC32::CRC32_TYPE(crcType));
	reserve[0] = reserve[1] = reserve[2] = 0;

	CRC32 crc = CRC32(CRC32::CRC32_TYPE(crcEncodeType));
	BYTE crcBuff[sizeof(crcEncodeType) + sizeof(reserve) + sizeof(DWORD)];

	memcpy(crcBuff, (LPCSTR)&typeCode, sizeof(typeCode));
	memcpy(crcBuff+ sizeof(typeCode), (LPCSTR)&crcEncodeType, sizeof(crcEncodeType));
	memcpy(crcBuff + sizeof(typeCode) + sizeof(crcEncodeType), reserve, sizeof(reserve));

	Chunk::crcCode = crc.crcCompute(crcBuff, dataLength + sizeof(DWORD));
}

/********************************** TEND **********************************/

thatboy::TEND_Chunk::TEND_Chunk()
{
	Chunk::dataLength = 0;
	Chunk::typeCode = endChunkType;
	Chunk::crcCode = 0;
}

bool thatboy::TEND_Chunk::checkCrcCode(BYTE crcEncodeType) const
{
	TEND_Chunk NChunk(*this);
	NChunk.doFigure(crcEncodeType);
	return NChunk.crcCode == crcCode;
}

void thatboy::TEND_Chunk::doFigure(BYTE crcType)
{
	Chunk::dataLength = 0;
	Chunk::typeCode = endChunkType;

	CRC32 crc = CRC32(CRC32::CRC32_TYPE(crcType));

	Chunk::crcCode = crc.crcCompute((BYTE_CPTR)&typeCode, dataLength + sizeof(DWORD));
}

/********************************** TDAT **********************************/

thatboy::TDAT_Chunk::TDAT_Chunk()
{
	Chunk::dataLength = 0;
	Chunk::typeCode = dataChunkType;
	Chunk::crcCode = 0;
}

std::ostream& thatboy::TDAT_Chunk::write(std::ostream&os) const
{
	Chunk::write(os);
	return os.write((LPCSTR)compressData.data(), dataLength);
}

std::istream& thatboy::TDAT_Chunk::read(std::istream&is)
{
	Chunk::read(is);
	compressData.resize(dataLength / sizeof(BYTE));
	return is.read((LPSTR)compressData.data(), dataLength);
}

bool thatboy::TDAT_Chunk::checkCrcCode(BYTE crcEncodeType) const
{
	TDAT_Chunk NChunk(*this);
	NChunk.doFigure(crcEncodeType);
	return NChunk.crcCode == crcCode;
}

void thatboy::TDAT_Chunk::doFigure(BYTE crcType)
{
	Chunk::dataLength = sizeof(BYTE) * compressData.size();
	Chunk::typeCode = dataChunkType;

	CRC32 crc = CRC32(CRC32::CRC32_TYPE(crcType));
	BYTE* crcBuff = new BYTE[dataLength + sizeof(DWORD)];

	memcpy(crcBuff, (LPCSTR)&typeCode, sizeof(typeCode));
	memcpy(crcBuff + sizeof(typeCode), (LPCSTR)compressData.data(), dataLength);
	Chunk::crcCode = crc.crcCompute(crcBuff, dataLength + sizeof(DWORD));
	delete[]crcBuff;
}
