#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;
void CalcBG2DHist_OpenCV(const Mat * image,Mat & hist,int histSize[])
{
	float ranges1[] = { 0, 254 };
	float ranges2[] = { 0, 254 };
	const float* ranges[] = { ranges1, ranges2 };
	int channels[] = {0, 1};
	calcHist(image, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
}
void CalcBG2DHist(const Mat * image,Mat & hist,int histSize[])
{
	int nRows = image->rows;
	int nCols = image->cols;
	if (image->isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	hist = Mat::zeros(histSize[0],histSize[1], CV_32F);
	int i,j;
	const uchar* p;
	for( i = 0; i < nRows; ++i)
	{
		p = (*image).ptr<uchar>(i);
		for ( j = 0; j < nCols*3; j+=3)
		{
			hist.at<float>(p[j]/(256/histSize[0]),p[j+1]/(256/histSize[1])) ++;
		}
	}
}
void CalcBG2DHist(unsigned char data[],float hist[],int dataSize,int histSize[])
{
	int i;
	memset(hist,0,histSize[0]*histSize[1]*sizeof(float));
	for(i=0;i<dataSize;i+=3)
	{
		hist[data[i]/(256/histSize[0])*histSize[1]+data[i+1]/(256/histSize[1])] ++ ;
	}
}
void Draw2DHist(const string& winname,Mat & hist,int histSize[])
{
	double maxVal=0;
	minMaxLoc(hist, 0, &maxVal, 0, 0);
	int nRows = hist.rows;
	int nCols = hist.cols;
	int scale = 2;
	Mat histImg = Mat::zeros(nRows*scale, nCols*scale, CV_8UC3);
	for( int b = 0; b < nRows; b++ )
		for( int g = 0; g < nCols; g++ )
		{
			float binVal = hist.at<float>(b, g);
			int intensity = cvRound(binVal*255/maxVal);
			rectangle( histImg, Point(b*scale, g*scale),Point( (b+1)*scale - 1, (g+1)*scale - 1),
						Scalar::all(intensity),CV_FILLED );
		}
	namedWindow( winname, 1 );
	imshow( winname, histImg );
}
int main( int argc, char** argv )
{
	Mat src;
	if( argc != 2 || !(src=imread(argv[1], 1)).data )
		return -1;
	int rbins = 256, gbins = 256;
	int histSize[] = {rbins, gbins};

	namedWindow( "Source", 1 );
	imshow( "Source", src );

	Mat hist;
	///////////////////////////////////////////////////////////
	CalcBG2DHist_OpenCV(&src,hist,histSize);
	Draw2DHist("B-G Histogram1",hist,histSize);
	Mat NDColorImg( 2000, 2000, CV_8UC3, Scalar::all(128) );
	randn(NDColorImg, Scalar(128,64,150), Scalar(5,5,5));
	CalcBG2DHist_OpenCV(&NDColorImg,hist,histSize);
	Draw2DHist("ND_B-G Histogram1",hist,histSize);
	///////////////////////////////////////////////////////////
	CalcBG2DHist(&src,hist,histSize);
	Draw2DHist("B-G Histogram2",hist,histSize);
	CalcBG2DHist(&NDColorImg,hist,histSize);
	Draw2DHist("ND_B-G Histogram2",hist,histSize);
	///////////////////////////////////////////////////////////
	if (src.isContinuous())
	{
		hist = Mat::zeros(histSize[0],histSize[1], CV_32F);
		CalcBG2DHist(src.data, (float*)(hist.data),src.cols*src.rows*3,histSize);
		Draw2DHist("B-G Histogram3",hist,histSize);
		CalcBG2DHist(NDColorImg.data, (float*)(hist.data),NDColorImg.cols*NDColorImg.rows*3,histSize);
		Draw2DHist("ND_B-G Histogram3",hist,histSize);
	}

	waitKey();
}