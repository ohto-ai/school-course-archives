#include "ColorCube.h"

int main()
{
	using namespace std;
	using namespace cv;
	using namespace thatboy;

	Mat srcImage, dstImage;
	srcImage = imread("color3.png");	/* "baboon.jpg" */
	if (srcImage.empty())
		throw std::bad_exception();
	dstImage = srcImage.clone();

	// 测试二十次运算
	auto begin = clock();
	for (size_t i = 0; i < 20; i++)
	{
		ColorCube::loadImage(srcImage);
		ColorCube::splitCube();
	}
	auto end = clock();

	cout << (end - begin) / 20000.0 << "s/张" << endl
		<< (end - begin)/1000.0 << "s/20张" << endl;

	ColorCube::write8bIndexBmp("baboon.bmp");

	for (auto iter = dstImage.begin<Vec3b>(); iter != dstImage.end<Vec3b>(); ++iter)
		*iter = ColorCube::mapping(*iter);

	imshow("原图", srcImage);
	imshow("替换颜色后", dstImage);
	waitKey();
}