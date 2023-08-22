#pragma once
#include <opencv2/opencv.hpp>

namespace thatboy
{
	namespace DiscreteCosineTransform
	{
		namespace MaskMatrix
		{
			const cv::Mat defaultDCTMask = cv::Mat_<float>(
				{ 1, 1, 1, 1, 0, 0, 0, 0
				, 1, 1, 1, 0, 0, 0, 0, 0
				, 1, 1, 0, 0, 0, 0, 0, 0
				, 1, 0, 0, 0, 0, 0, 0, 0
				, 0, 0, 0, 0, 0, 0, 0, 0
				, 0, 0, 0, 0, 0, 0, 0, 0
				, 0, 0, 0, 0, 0, 0, 0, 0
				, 0, 0, 0, 0, 0, 0, 0, 0 }
			).reshape(1, 8);
		}

		// DCTÑ¹ËõÍ¼Ïñ
		cv::Mat dctCompress(cv::Mat srcImage, cv::Mat& dstImage, cv::Mat dctMask = MaskMatrix::defaultDCTMask);
	}
}

