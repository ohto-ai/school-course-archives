#include "DiscreteCosineTransform.h"


// ������ɢ���ұ任���Ƴ���Ƶ��Ϣ���ؽ�ͼ��
cv::Mat thatboy::DiscreteCosineTransform::dctCompress(cv::Mat srcImage, cv::Mat& dstImage, cv::Mat dctMask)
{
	using namespace cv;

	// ����ͨ��
	auto dctSingleChannel = [](Mat srcImage, cv::Mat dctMask)
	{
		Mat grayChannel, dctImage, dstImage;
		srcImage.convertTo(grayChannel, CV_32F, 1.0 / 255);
		dctImage = grayChannel.clone();
		dstImage = grayChannel;
		// �ֿ�
		for (int i = 0; i < grayChannel.cols / dctMask.cols; ++i)
		{
			for (int j = 0; j < grayChannel.rows / dctMask.rows; j++)
			{
				dct(grayChannel(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)), dctImage(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)));

				dctImage(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)) = dctImage(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)).mul(dctMask);

				idct(dctImage(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)), dstImage(Range(j * dctMask.rows, (j + 1) * dctMask.rows), Range(i * dctMask.rows, (i + 1) * dctMask.rows)));
			}
		}
		dstImage.convertTo(srcImage, CV_8U, 255);
		dctImage.convertTo(dctImage, CV_8U, 255);
		return dctImage;
	};

	// ͨ���ϲ�
	Mat dctImage;
	std::vector<Mat> multiChannels(srcImage.channels(), Mat());
	std::vector<Mat> multiDCTChannels;
	split(srcImage, multiChannels);
	for (auto& channel : multiChannels)
		multiDCTChannels.push_back(dctSingleChannel(channel, dctMask));
	merge(multiChannels, dstImage);
	merge(multiDCTChannels, dctImage);
	return dctImage;
}
