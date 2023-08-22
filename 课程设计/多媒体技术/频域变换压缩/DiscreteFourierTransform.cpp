#include "DiscreteFourierTransform.h"
cv::Mat thatboy::DiscreteFourierTransform::dftCompress(cv::Mat srcImage, cv::Mat& dstImage)
{
    using namespace cv;
    auto dftSingleChannel = [](cv::Mat srcImage, cv::Mat& dstImage)
    {
        Mat imgPadded;
        Mat dftImage;
        int nRows = getOptimalDFTSize(srcImage.rows);
        int nCols = getOptimalDFTSize(srcImage.cols);
        Size srcSize = srcImage.size();
        // 处理边界
        copyMakeBorder(srcImage, imgPadded, 0, nRows - srcImage.rows, 0, nCols - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
        std::vector<Mat> planes = { Mat_<float>(imgPadded), Mat::zeros(imgPadded.size(),CV_32F) };
        Mat complexImg;
        merge(planes, complexImg);

        // 进行傅里叶变换
        dft(complexImg, complexImg);                   

        // 计算 log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
        split(complexImg, planes);                      // 分离通道， planes[0] 为实数部分，planes[1]为虚数部分
        Mat imageFloat;
        magnitude(planes[0], planes[1], imageFloat);     // 求模
        imageFloat += Scalar::all(1);
        log(imageFloat, dftImage);                       // 取对数
        dftImage = dftImage(Rect(0, 0, dftImage.cols & -2, dftImage.rows & -2));

        // 重新排列傅里叶图像中的象限，使得原点位于图像中心
        auto exchangeImage = [](Mat image1, Mat image2) {
            Mat tmp;
            image1.copyTo(tmp);
            image2.copyTo(image1);
            tmp.copyTo(image2);
        };
        exchangeImage(dftImage(Rect(0, 0, dftImage.cols / 2, dftImage.rows / 2))
            , dftImage(Rect(dftImage.cols / 2, dftImage.rows / 2, dftImage.cols / 2, dftImage.rows / 2)));
        exchangeImage(dftImage(Rect(dftImage.cols / 2, 0, dftImage.cols / 2, dftImage.rows / 2))
            , dftImage(Rect(0, dftImage.rows / 2, dftImage.cols / 2, dftImage.rows / 2)));
        
        // 重建图像
        idft(complexImg, dstImage, DFT_REAL_OUTPUT);
        
        // 归一化
        resize(dstImage, dstImage, srcSize);
        normalize(dftImage, dftImage, 0, 1, CV_MINMAX);
        normalize(dstImage, dstImage, 0, 1, CV_MINMAX);
        dftImage.convertTo(dftImage, CV_8U, 255);
        dstImage.convertTo(dstImage, CV_8U, 255);
        return dftImage;
    };

    Mat dftImage;
    std::vector<Mat> multiChannels(srcImage.channels(), Mat());
    std::vector<Mat> multiDFTChannels;
    split(srcImage, multiChannels);
    for (auto& channel : multiChannels)
        multiDFTChannels.push_back(dftSingleChannel(channel, channel));

    // 合并重建图像
    merge(multiChannels, dstImage);
    merge(multiDFTChannels, dftImage);
    return dftImage;
}
