#pragma once
#include "ThatboyEncryptBase.h"

namespace thatboy
{

	/********************************** 文件头 **********************************/
	class THDR_Chunk final
		: public Chunk
	{
	public:
		THDR_Chunk();

		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
		bool checkCrcCode(BYTE crcEncodeType = defaultCrcType)const;
		void doFigure(BYTE crcEncodeType = defaultCrcType);


		BYTE crcEncodeType;		// CRC校验类型
		BYTE reserve[3];		// 保留
	};

	/********************************** 文件尾 **********************************/
	class TEND_Chunk final
		: public Chunk
	{
	public:
		TEND_Chunk();
		bool checkCrcCode(BYTE crcEncodeType = defaultCrcType)const;
		void doFigure(BYTE crcEncodeType = defaultCrcType);

	protected:
	};

	/********************************** 数据块 **********************************/
	class TDAT_Chunk 
		: public Chunk
	{
	public:
		TDAT_Chunk();

		std::ostream& write(std::ostream&)const;
		std::istream& read(std::istream&);
		bool checkCrcCode(BYTE crcEncodeType = defaultCrcType)const;
		void doFigure(BYTE crcEncodeType = defaultCrcType);

		std::vector<BYTE> compressData;// zib压缩数据
	};


}
