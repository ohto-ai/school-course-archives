#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>

namespace thatboy
{
    namespace DiscreteFourierTransform
    {
        cv::Mat dftCompress(cv::Mat srcImage, cv::Mat& dstImage);
    }
}

