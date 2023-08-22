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

	// �任���ؽ�ͼ�񡾱任ͼ��=func(ԭʼͼ��, �ؽ�ͼ��[, ����...])��
    dctImage = DiscreteCosineTransform::dctCompress(srcImage, dctRebuild);
	dftImage = DiscreteFourierTransform::dftCompress(srcImage, dftRebuild);
	wdtImage = WaveTransform::wdtCompress(srcImage, wdtRebuild, "sym2"/*haar|db1*/, 3);

	absdiff(srcImage, dctRebuild, dctDiff);
	absdiff(srcImage, dftRebuild, dftDiff);
	absdiff(srcImage, wdtRebuild, wdtDiff);

	// չʾ

	imshow("Դͼ��", srcImage);

	imshow("DCTϵ��ͼ��", dctImage);
	imshow("DCT�ؽ�ͼ��", dctRebuild);
	imshow("DFTƵ��ͼ��", dftImage);
	imshow("DFT�ؽ�ͼ��", dftRebuild);
	imshow("WDT�ֽ�ͼ��", wdtImage);
	imshow("WDT�ؽ�ͼ��", wdtRebuild);

	imshow("DCT���ͼ��", dctDiff);
	imshow("DFT���ͼ��", dftDiff);
	imshow("WDT���ͼ��", wdtDiff);

	// ����

	imwrite("out/Դͼ��.jpg", srcImage);
	imwrite("out/DCTϵ��ͼ��.jpg", dctImage);
	imwrite("out/DCT�ؽ�ͼ��.jpg", dctRebuild);
	imwrite("out/DFTƵ��ͼ��.jpg", dftImage);
	imwrite("out/DFT�ؽ�ͼ��.jpg", dftRebuild);
	imwrite("out/WDT�ֽ�ͼ��.jpg", wdtImage);
	imwrite("out/WDT�ؽ�ͼ��.jpg", wdtRebuild);

	imwrite("out/DCT���ͼ��.jpg", dctDiff);
	imwrite("out/DFT���ͼ��.jpg", dftDiff);
	imwrite("out/WDT���ͼ��.jpg", wdtDiff);

	auto getFileSize = [](std::string file)->size_t
	{
		std::ifstream ifs(file);
		if (!ifs)
			return 0;

		ifs.seekg(0, ios::end);
		return ifs.tellg();
	};

	size_t oriImageSize = getFileSize("out/Դͼ��.jpg");
	size_t dctImageSize = getFileSize("out/DCT�ؽ�ͼ��.jpg");
	size_t dftImageSize = getFileSize("out/DFT�ؽ�ͼ��.jpg");
	size_t wdtImageSize = getFileSize("out/WDT�ؽ�ͼ��.jpg");

	cout << "����\t" << "��С(Byte)\t" << "���ѹ����\t" << endl;
	cout << "Դͼ��\t" << oriImageSize << "\t\t" << 1.0 * oriImageSize / oriImageSize << endl;
	cout << "DCT\t" << dctImageSize << "\t\t" << 1.0 * dctImageSize / oriImageSize << endl;
	cout << "DFT\t" << dftImageSize << "\t\t" << 1.0 * dftImageSize / oriImageSize << endl;
	cout << "WDT\t" << wdtImageSize << "\t\t" << 1.0 * wdtImageSize / oriImageSize << endl;

	waitKey(0);
	return 0;
}