#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
/**
 * @function main
 */
int main( int argc, char** argv )
{
	int height,width;
	height = 2000;
	width = 2000;
	Mat NDColorImg( height, width, CV_8UC3, Scalar::all(128) );
	randn(NDColorImg, Scalar(128,100,150), Scalar(30,15,10));
	namedWindow("color normally distributed", CV_WINDOW_AUTOSIZE );
	imshow("color normally distributed", NDColorImg );
	imwrite("cnd.bmp",NDColorImg);

	Mat NDGrayImg( height, width, CV_8UC1, Scalar::all(128) );
	randn(NDGrayImg, 128, 20);
	namedWindow("gray normally distributed", CV_WINDOW_AUTOSIZE );
	imshow("gray normally distributed", NDGrayImg );
	imwrite("gnd.bmp",NDGrayImg);
	
	waitKey(0);

	return 0;
}
