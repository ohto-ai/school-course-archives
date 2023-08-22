#include "WaveTransform.h"

using namespace std;
using namespace cv;
using namespace thatboy;

Mat WaveTransform::WDT(const Mat& _src, const string _wname, const int _level) 
{
    Mat_<float> src = Mat_<float>(_src);
    Mat dst = Mat::zeros(src.rows, src.cols, src.type());
    int row = src.rows;
    int col = src.cols;

    //高通低通滤波器
    Mat lowFilter;
    Mat highFilter;
    wavelet_D(_wname, lowFilter, highFilter);
    for (size_t nLevel = 0; nLevel < _level; nLevel++)
    {
        // 行小波变换
        for (int i = 0; i < row; i++)
        {
            // 取出src中要处理的数据的一行
            Mat oneRow = Mat::zeros(1, col, src.type());

            for (int j = 0; j < col; j++)
                oneRow.at<float>(0, j) = src.at<float>(i, j);

            oneRow = waveletDecompose(oneRow, lowFilter, highFilter);
            for (int j = 0; j < col; j++)
                dst.at<float>(i, j) = oneRow.at<float>(0, j);
        }

        // 小波列变换
        for (int j = 0; j < col; j++)
        {
            Mat oneCol = Mat::zeros(row, 1, src.type());

            for (int i = 0; i < row; i++)
                oneCol.at<float>(i, 0) = dst.at<float>(i, j);
            oneCol = (waveletDecompose(oneCol.t(), lowFilter, highFilter)).t();

            for (int i = 0; i < row; i++)
                dst.at<float>(i, j) = oneCol.at<float>(i, 0);
        }

        //更新 
        row /= 2;
        col /= 2;
        src = dst;
    }
    return dst;
}

Mat WaveTransform::IWDT(const Mat& _src, const string _wname, const int _level)
{
    Mat src = Mat_<float>(_src);
    Mat dst = src.clone();
    int N = src.rows;
    int D = src.cols;

    //高低通滤波器
    Mat lowFilter;
    Mat highFilter;
    wavelet_R(_wname, lowFilter, highFilter);

    //小波变换
    int row = N / std::pow(2., _level - 1);
    int col = D / std::pow(2., _level - 1);

    while (row <= N && col <= D)
    {
        //列逆变换
        for (int j = 0; j < col; j++)
        {
            Mat oneCol = Mat::zeros(row, 1, src.type());

            for (int i = 0; i < row; i++)
                oneCol.at<float>(i, 0) = src.at<float>(i, j);
            oneCol = (waveletReconstruct(oneCol.t(), lowFilter, highFilter)).t();

            for (int i = 0; i < row; i++)
                dst.at<float>(i, j) = oneCol.at<float>(i, 0);

        }
        //行逆变换
        for (int i = 0; i < row; i++)
        {
            Mat oneRow = Mat::zeros(1, col, src.type());
            for (int j = 0; j < col; j++)
                oneRow.at<float>(0, j) = dst.at<float>(i, j);
            oneRow = waveletReconstruct(oneRow, lowFilter, highFilter);
            for (int j = 0; j < col; j++)
                dst.at<float>(i, j) = oneRow.at<float>(0, j);
        }
        row *= 2;
        col *= 2;
        src = dst;
    }

    return dst;
}


void WaveTransform::wavelet_D(const string _wname, Mat& _lowFilter, Mat& _highFilter)
{
    if (_wname == "haar" || _wname == "db1")
    {
        int N = 2;
        _lowFilter = Mat::zeros(1, N, CV_32F);
        _highFilter = Mat::zeros(1, N, CV_32F);

        _lowFilter.at<float>(0, 0) = 1 / sqrtf(N);
        _lowFilter.at<float>(0, 1) = 1 / sqrtf(N);

        _highFilter.at<float>(0, 0) = -1 / sqrtf(N);
        _highFilter.at<float>(0, 1) = 1 / sqrtf(N);
    }
    else if (_wname == "sym2")
    {
        int N = 4;
        float h[] = { -0.4830, 0.8365, -0.2241, -0.1294 };
        float l[] = { -0.1294, 0.2241,  0.8365, 0.4830 };

        _lowFilter = Mat::zeros(1, N, CV_32F);
        _highFilter = Mat::zeros(1, N, CV_32F);

        for (int i = 0; i < N; i++)
        {
            _lowFilter.at<float>(0, i) = l[i];
            _highFilter.at<float>(0, i) = h[i];
        }
    }
}
void WaveTransform::wavelet_R(const string _wname, Mat& _lowFilter, Mat& _highFilter)
{
    if (_wname == "haar" || _wname == "db1")
    {
        int N = 2;
        _lowFilter = Mat::zeros(1, N, CV_32F);
        _highFilter = Mat::zeros(1, N, CV_32F);


        _lowFilter.at<float>(0, 0) = 1 / sqrtf(N);
        _lowFilter.at<float>(0, 1) = 1 / sqrtf(N);

        _highFilter.at<float>(0, 0) = 1 / sqrtf(N);
        _highFilter.at<float>(0, 1) = -1 / sqrtf(N);
    }
    else if (_wname == "sym2")
    {
        int N = 4;
        float h[] = { -0.1294,-0.2241,0.8365,-0.4830 };
        float l[] = { 0.4830, 0.8365, 0.2241, -0.1294 };

        _lowFilter = Mat::zeros(1, N, CV_32F);
        _highFilter = Mat::zeros(1, N, CV_32F);

        for (int i = 0; i < N; i++)
        {
            _lowFilter.at<float>(0, i) = l[i];
            _highFilter.at<float>(0, i) = h[i];
        }
    }
}


Mat WaveTransform::waveletDecompose(const Mat& _src, const Mat& _lowFilter, const Mat& _highFilter)
{
    assert(_src.rows == 1 && _lowFilter.rows == 1 && _highFilter.rows == 1);
    assert(_src.cols >= _lowFilter.cols && _src.cols >= _highFilter.cols);
    Mat src = Mat_<float>(_src);

    int D = src.cols;

    Mat lowFilter = Mat_<float>(_lowFilter);
    Mat highFilter = Mat_<float>(_highFilter);

    //频域滤波或时域卷积；ifft( fft(x) * fft(filter)) = cov(x,filter) 
    Mat dst1 = Mat::zeros(1, D, src.type());
    Mat dst2 = Mat::zeros(1, D, src.type());

    filter2D(src, dst1, -1, lowFilter);
    filter2D(src, dst2, -1, highFilter);

    //下采样
    //数据拼接
    for (int i = 0, j = 1; i < D / 2; i++, j += 2)
    {
        src.at<float>(0, i) = dst1.at<float>(0, j);//lowFilter
        src.at<float>(0, i + D / 2) = dst2.at<float>(0, j);//highFilter
    }
    return src;
}


Mat WaveTransform::waveletReconstruct(const Mat& _src, const Mat& _lowFilter, const Mat& _highFilter)
{
    assert(_src.rows == 1 && _lowFilter.rows == 1 && _highFilter.rows == 1);
    assert(_src.cols >= _lowFilter.cols && _src.cols >= _highFilter.cols);
    Mat src = Mat_<float>(_src);

    int D = src.cols;

    Mat lowFilter = Mat_<float>(_lowFilter);
    Mat highFilter = Mat_<float>(_highFilter);

    // 插值;
    Mat Up1 = Mat::zeros(1, D, src.type());
    Mat Up2 = Mat::zeros(1, D, src.type());

    // Mat roi1(src, Rect(0, 0, D / 2, 1));
    // Mat roi2(src, Rect(D / 2, 0, D / 2, 1));
    // 插值为0

    for (int i = 0, cnt = 0; i < D / 2; i++, cnt += 2)
    {
        Up1.at<float>(0, cnt) = src.at<float>(0, i);     // < 前一半
        Up2.at<float>(0, cnt) = src.at<float>(0, i + D / 2); // < 后一半
    }
 
    // 线性插值

    // 前一半低通，后一半高通
    Mat dst1 = Mat::zeros(1, D, src.type());
    Mat dst2 = Mat::zeros(1, D, src.type());
    filter2D(Up1, dst1, -1, lowFilter);
    filter2D(Up2, dst2, -1, highFilter);
    // 结果相加
    dst1 = dst1 + dst2;
    return dst1;

}

cv::Mat thatboy::WaveTransform::wdtCompress(cv::Mat srcImage, cv::Mat& dstImage, const std::string wname, const int level)
{
    using namespace cv;

    Mat wdtImage;
    std::vector<Mat> multiChannels(srcImage.channels(), Mat());
    std::vector<Mat> multiWDTChannels;
    split(srcImage, multiChannels);
    for (auto& channel : multiChannels)
    {
        channel.convertTo(channel, CV_32F, 1.0 / 255);

        // wdt 及 重建
        Mat imgWave = WDT(channel, wname, level);
        channel = IWDT(imgWave, wname, level);

        // 
        imgWave.convertTo(imgWave, CV_8U, 255);
        channel.convertTo(channel, CV_8U, 255);
        multiWDTChannels.push_back(imgWave);
    }
    // 合并通道
    merge(multiChannels, dstImage);
    merge(multiWDTChannels, wdtImage);
    return wdtImage;
}
