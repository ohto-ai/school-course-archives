#pragma once
#include <vector>
#include <list>
#include <opencv2/opencv.hpp>

namespace thatboy
{
	/* ������ɫ������ */
	struct ColorCube
	{
	protected:
		using BYTE = uchar;
		using ColorType = cv::Vec3b;
	public:
		ColorCube(const ColorCube&) = default;
		ColorCube(ColorCube&&)noexcept = default;
		ColorCube()noexcept = default;

		ColorCube(BYTE b_begin, BYTE g_begin, BYTE r_begin
			, BYTE b_end, BYTE g_end, BYTE r_end)
			: bBegin(b_begin), bEnd(b_end)
			, gBegin(g_begin), gEnd(g_end)
			, rBegin(r_begin), rEnd(r_end)
		{
#ifdef _DEBUG
			if (bBegin > bEnd
				|| gBegin > gEnd
				|| rBegin > rEnd)
				throw std::bad_exception();
#endif // 

		}
		ColorCube(ColorType beg, ColorType end)
			: ColorCube(beg[0], end[0], beg[1], end[1], beg[2], end[2])
		{}

		inline bool operator < (const ColorCube& cube)const
		{
			return size < cube.size;
		}

	protected:
		// ����
		bool doSplitCube(int channel);
		bool splitBrotherCube();
		void reshapeCube();		// ȷ���ռ��С
		void calacCubeColor();	// ȡƽ��ֵ��Ϊ�ÿռ�Ĵ�����ɫ
	protected:
		// ��Ա
		ColorType cubeColor = ColorType(255, 255, 255);
		size_t size = 0;
		BYTE rBegin, rEnd;
		BYTE gBegin, gEnd;
		BYTE bBegin, bEnd;
	public:
		static void loadImage(const cv::Mat srcImage);
		static void splitCube(size_t cubeNumber = 256);
		static void write8bIndexBmp(std::string fileName);

		// ӳ�䷽��
		static inline const ColorType& mapping(const ColorType& color)	// ӳ��ɫ��
		{
#ifdef _DEBUG
			auto ptr = colorHist[color[0]][color[1]][color[2]];
			if (ptr >= colorTable.size())
				throw std::bad_exception();
			return colorTable[ptr];
#else
			return colorTable[colorHist[color[0]][color[1]][color[2]]];
#endif // 
		}
		static inline const size_t mappingPtr(const ColorType& color)	// ӳ������
		{
			return colorHist[color[0]][color[1]][color[2]];
		}
	protected:
		static std::vector<ColorType> colorTable;						// ��ɫӳ���
		static std::vector<std::vector<std::vector<size_t>>> colorHist;	// ��ɫֱ��ͼ
		static std::list<ColorCube> colorCubeSet;						// �ռ��б�
		static cv::Mat srcImage;										// ԭʼͼ��

	};


}

