#pragma once
#include "ThatboyEncryptBase.h"

namespace thatboy
{

	/********************************** 文件头 **********************************/
	class THDR_Chunk final
		: public Chunk
	{
	public:
		static constexpr DWORD hdrChunkType = makeDWORD('T', 'H', 'D', 'R');
		THDR_Chunk();

		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
		bool checkCrcCode(BYTE crcEncodeType)const;
		void doFigure(BYTE crcEncodeType);


		BYTE crcEncodeType;		// CRC校验类型
		BYTE reserve[3];		// 保留zhaiyao
	};

	/********************************** 文件尾 **********************************/
	class TEND_Chunk final
		: public Chunk
	{
	public:
		static constexpr DWORD endChunkType = makeDWORD('T', 'E', 'N', 'D');
		TEND_Chunk();
		bool checkCrcCode(BYTE crcEncodeType)const;
		void doFigure(BYTE crcEncodeType);

	protected:
	};

	/********************************** 数据块 **********************************/
	class TDAT_Chunk 
		: public Chunk
	{
	public:
		static constexpr DWORD dataChunkType = makeDWORD('T', 'D', 'A', 'T');
		TDAT_Chunk();

		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
		bool checkCrcCode(BYTE crcEncodeType)const;
		void doFigure(BYTE crcEncodeType);

		std::vector<BYTE> compressData;// zib压缩数据
	};


}
