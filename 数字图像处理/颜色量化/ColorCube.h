#pragma once
#include <vector>
#include <list>
#include <opencv2/opencv.hpp>

namespace thatboy
{
	/* 像素颜色长方体 */
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
		// 分裂
		bool doSplitCube(int channel);
		bool splitBrotherCube();
		void reshapeCube();		// 确定空间大小
		void calacCubeColor();	// 取平均值作为该空间的代表颜色
	protected:
		// 成员
		ColorType cubeColor = ColorType(255, 255, 255);
		size_t size = 0;
		BYTE rBegin, rEnd;
		BYTE gBegin, gEnd;
		BYTE bBegin, bEnd;
	public:
		static void loadImage(const cv::Mat srcImage);
		static void splitCube(size_t cubeNumber = 256);
		static void write8bIndexBmp(std::string fileName);

		// 映射方法
		static inline const ColorType& mapping(const ColorType& color)	// 映射色彩
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
		static inline const size_t mappingPtr(const ColorType& color)	// 映射坐标
		{
			return colorHist[color[0]][color[1]][color[2]];
		}
	protected:
		static std::vector<ColorType> colorTable;						// 颜色映射表
		static std::vector<std::vector<std::vector<size_t>>> colorHist;	// 彩色直方图
		static std::list<ColorCube> colorCubeSet;						// 空间列表
		static cv::Mat srcImage;										// 原始图像

	};


}

