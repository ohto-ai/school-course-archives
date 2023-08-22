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
        // ����߽�
        copyMakeBorder(srcImage, imgPadded, 0, nRows - srcImage.rows, 0, nCols - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));
        std::vector<Mat> planes = { Mat_<float>(imgPadded), Mat::zeros(imgPadded.size(),CV_32F) };
        Mat complexImg;
        merge(planes, complexImg);

        // ���и���Ҷ�任
        dft(complexImg, complexImg);                   

        // ���� log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
        split(complexImg, planes);                      // ����ͨ���� planes[0] Ϊʵ�����֣�planes[1]Ϊ��������
        Mat imageFloat;
        magnitude(planes[0], planes[1], imageFloat);     // ��ģ
        imageFloat += Scalar::all(1);
        log(imageFloat, dftImage);                       // ȡ����
        dftImage = dftImage(Rect(0, 0, dftImage.cols & -2, dftImage.rows & -2));

        // �������и���Ҷͼ���е����ޣ�ʹ��ԭ��λ��ͼ������
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
        
        // �ؽ�ͼ��
        idft(complexImg, dstImage, DFT_REAL_OUTPUT);
        
        // ��һ��
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

    // �ϲ��ؽ�ͼ��
    merge(multiChannels, dstImage);
    merge(multiDFTChannels, dftImage);
    return dftImage;
}
