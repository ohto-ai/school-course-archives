#include "ColorCube.h"

int main()
{
	using namespace std;
	using namespace cv;
	using namespace thatboy;

	Mat srcImage, dstImage;
	srcImage = imread("baboon.jpg");	/* "baboon.jpg" */
	if (srcImage.empty())
		throw std::bad_exception();
	dstImage = srcImage.clone();

	// ���Զ�ʮ������
	auto begin = clock();
	for (size_t i = 0; i < 20; i++)
	{
		ColorCube::loadImage(srcImage);
		ColorCube::splitCube();
	}
	auto end = clock();

	cout << (end - begin) / 20000.0 << "s/��" << endl
		<< (end - begin)/1000.0 << "s/20��" << endl;

	ColorCube::write8bIndexBmp("baboon.bmp");

	for (auto iter = dstImage.begin<Vec3b>(); iter != dstImage.end<Vec3b>(); ++iter)
		*iter = ColorCube::mapping(*iter);

	imshow("ԭͼ", srcImage);
	imshow("�滻��ɫ��", dstImage);
	waitKey();
}