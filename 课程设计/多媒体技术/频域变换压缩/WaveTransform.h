#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
namespace thatboy
{
	namespace WaveTransform
	{
		cv::Mat WDT(const cv::Mat& _src, const std::string _wname, const int _level);//С���ֽ�
		cv::Mat IWDT(const cv::Mat& _src, const std::string _wname, const int _level);//С���ع�
		void wavelet_D(const std::string _wname, cv::Mat& _lowFilter, cv::Mat& _highFilter);//�ֽ��
		void wavelet_R(const std::string _wname, cv::Mat& _lowFilter, cv::Mat& _highFilter);//�ع���
		cv::Mat waveletDecompose(const cv::Mat& _src, const cv::Mat& _lowFilter, const cv::Mat& _highFilter);
		cv::Mat waveletReconstruct(const cv::Mat& _src, const cv::Mat& _lowFilter, const cv::Mat& _highFilter);

		cv::Mat wdtCompress(cv::Mat srcImage, cv::Mat& dstImage, const std::string _wname, const int _level);
	}
}