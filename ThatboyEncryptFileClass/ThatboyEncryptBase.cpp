#include "ThatboyEncryptBase.h"

std::ostream& thatboy::Chunk::write(std::ostream& os)const
{
	os.write((LPCSTR)&dataLength, sizeof(dataLength));
	os.write((LPCSTR)&typeCode, sizeof(typeCode));
	os.write((LPCSTR)&crcCode, sizeof(crcCode));
	return os;
}

std::istream& thatboy::Chunk::read(std::istream& is)
{
	is.read((LPSTR)&dataLength, sizeof(dataLength));
	is.read((LPSTR)&typeCode, sizeof(typeCode));
	is.read((LPSTR)&crcCode, sizeof(crcCode));
	return is;
}

void thatboy::Chunk::doFigure(BYTE crcType)
{
	Chunk::dataLength = 0;
	Chunk::typeCode = makeDWORD('T', 'E', 'N', 'D');
	CRC32 crc = CRC32(CRC32::CRC32_TYPE(crcType));
	Chunk::crcCode = crc.crcCompute((BYTE_CPTR)&typeCode, dataLength + sizeof(DWORD));
}


bool thatboy::Chunk::checkCrcCode(BYTE crcEncodeType)const
{
	Chunk NChunk(*this);
	NChunk.doFigure(crcEncodeType);
	return NChunk.crcCode == crcCode;
}