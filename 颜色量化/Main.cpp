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

	ColorCube::loadImage(srcImage);
	ColorCube::splitCube();
	ColorCube::write8bIndexBmp("bliss.bmp");

	for (auto iter = dstImage.begin<Vec3b>(); iter != dstImage.end<Vec3b>(); ++iter)
		*iter = ColorCube::mapping(*iter);

	imshow("Ô­Í¼", srcImage);
	imshow("Ìæ»»ÑÕÉ«ºó", dstImage);
	waitKey();
}