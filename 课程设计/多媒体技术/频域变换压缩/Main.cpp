#include "WaveTransform.h"
#include "DiscreteCosineTransform.h"
#include "DiscreteFourierTransform.h"

#include <fstream>


int main()
{
	using namespace std;
	using namespace cv;
	using namespace thatboy;
	Mat srcImage = imread("baboon.jpg"/*, IMREAD_GRAYSCALE*/);

	Mat dctImage, dctRebuild, dctDiff, dftImage, dftRebuild, dftDiff, wdtImage, wdtRebuild, wdtDiff;

	// 变换并重建图像【变换图像=func(原始图像, 重建图像[, 参数...])】
    dctImage = DiscreteCosineTransform::dctCompress(srcImage, dctRebuild);
	dftImage = DiscreteFourierTransform::dftCompress(srcImage, dftRebuild);
	wdtImage = WaveTransform::wdtCompress(srcImage, wdtRebuild, "sym2"/*haar|db1*/, 3);

	absdiff(srcImage, dctRebuild, dctDiff);
	absdiff(srcImage, dftRebuild, dftDiff);
	absdiff(srcImage, wdtRebuild, wdtDiff);

	// 展示

	imshow("源图像", srcImage);

	imshow("DCT系数图像", dctImage);
	imshow("DCT重建图像", dctRebuild);
	imshow("DFT频谱图像", dftImage);
	imshow("DFT重建图像", dftRebuild);
	imshow("WDT分解图像", wdtImage);
	imshow("WDT重建图像", wdtRebuild);

	imshow("DCT误差图像", dctDiff);
	imshow("DFT误差图像", dftDiff);
	imshow("WDT误差图像", wdtDiff);

	// 保存

	imwrite("out/源图像.jpg", srcImage);
	imwrite("out/DCT系数图像.jpg", dctImage);
	imwrite("out/DCT重建图像.jpg", dctRebuild);
	imwrite("out/DFT频谱图像.jpg", dftImage);
	imwrite("out/DFT重建图像.jpg", dftRebuild);
	imwrite("out/WDT分解图像.jpg", wdtImage);
	imwrite("out/WDT重建图像.jpg", wdtRebuild);

	imwrite("out/DCT误差图像.jpg", dctDiff);
	imwrite("out/DFT误差图像.jpg", dftDiff);
	imwrite("out/WDT误差图像.jpg", wdtDiff);

	auto getFileSize = [](std::string file)->size_t
	{
		std::ifstream ifs(file);
		if (!ifs)
			return 0;

		ifs.seekg(0, ios::end);
		return ifs.tellg();
	};

	size_t oriImageSize = getFileSize("out/源图像.jpg");
	size_t dctImageSize = getFileSize("out/DCT重建图像.jpg");
	size_t dftImageSize = getFileSize("out/DFT重建图像.jpg");
	size_t wdtImageSize = getFileSize("out/WDT重建图像.jpg");

	cout << "类型\t" << "大小(Byte)\t" << "相对压缩比\t" << endl;
	cout << "源图像\t" << oriImageSize << "\t\t" << 1.0 * oriImageSize / oriImageSize << endl;
	cout << "DCT\t" << dctImageSize << "\t\t" << 1.0 * dctImageSize / oriImageSize << endl;
	cout << "DFT\t" << dftImageSize << "\t\t" << 1.0 * dftImageSize / oriImageSize << endl;
	cout << "WDT\t" << wdtImageSize << "\t\t" << 1.0 * wdtImageSize / oriImageSize << endl;

	waitKey(0);
	return 0;
}