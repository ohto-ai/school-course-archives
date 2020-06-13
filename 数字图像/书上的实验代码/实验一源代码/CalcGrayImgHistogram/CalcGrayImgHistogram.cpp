#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void CalcHist_OpenCV(const Mat * image,Mat & hist,int histSize)
{
	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };//the upper boundary is exclusive
	bool uniform = true; bool accumulate = false;

	//Calculate Histogram
	calcHist( image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
}
void CalcHist_GrayImg(const Mat * image,Mat & hist,int histSize)
{
	int nRows = image->rows;
	int nCols = image->cols;
	if (image->isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	hist = Mat::zeros(1,histSize, CV_32F);
	int i,j;
	const uchar* p;
	for( i = 0; i < nRows; ++i)
	{
		p = (*image).ptr<uchar>(i);
		for ( j = 0; j < nCols; ++j)
		{
			hist.at<float>(p[j]/(256/histSize)) ++;
		}
	}
}
void CalcHist_GrayImg(unsigned char data[],float hist[],int dataSize,int histSize)
{
	int i;
	memset(hist,0,histSize*sizeof(float));
	for(i=0;i<dataSize;i++)
	{
		hist[data[i]/(256/histSize)] ++ ;
	}
}

void DrawHist(const string& winname,Mat & hist,int histSize)
{
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );
	hist_w = bin_w*(histSize-1)+1;
	Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
	/// Normalize the result to [ 0, histImage.rows ]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - 1 - cvRound(hist.at<float>(i-1)) ) ,
						Point( bin_w*i, hist_h - 1 - cvRound(hist.at<float>(i)) ),
						Scalar( 255, 0, 0), 2, 8, 0  );
	}
	/// Display
	namedWindow(winname, CV_WINDOW_AUTOSIZE );
	imshow(winname, histImage );
}
/**
 * @function main
 */
int main( int argc, char** argv )
{
	Mat src;
	/// Load image
	src = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);

	if( !src.data )
	{ return -1; }

	CV_Assert(src.depth() != sizeof(uchar));
	int channels = src.channels();

	if(channels != 1)
	{
		printf("img has more than one channel\n");
		return -1;
	}

	int histSize = 256;
	Mat g_hist;
	//////////////////////////////////////////////////////////////////////////////
	CalcHist_OpenCV(&src, g_hist,histSize);
	DrawHist("calcGrayImgHistogram1",g_hist,histSize);
	//////////////////////////////////////////////////////////////////////////////
	CalcHist_GrayImg(&src, g_hist,histSize);
	DrawHist("calcGrayImgHistogram2",g_hist,histSize);
	/////////////////////////////////////////////////////////////////////////////////////
	if (src.isContinuous())
	{
		g_hist = Mat::zeros(1,histSize, CV_32F);
		CalcHist_GrayImg(src.data, (float*)(g_hist.data),src.cols*src.rows,histSize);
		DrawHist("calcGrayImgHistogram3",g_hist,histSize);
	}
	
	//BinnedHistogram
	histSize = 32;
	//////////////////////////////////////////////////////////////////////////////////
	CalcHist_OpenCV(&src, g_hist,histSize);
	DrawHist("calcBinnedGrayImgHistogram1",g_hist,histSize);
	//////////////////////////////////////////////////////////////////////////////////
	CalcHist_GrayImg(&src, g_hist,histSize);
	DrawHist("calcBinnedGrayImgHistogram2",g_hist,histSize);
	//////////////////////////////////////////////////////////////////////////////////
	if (src.isContinuous())
	{
		g_hist = Mat::zeros(1,histSize, CV_32F);
		CalcHist_GrayImg(src.data, (float*)(g_hist.data),src.cols*src.rows,histSize);
		DrawHist("calcBinnedGrayImgHistogram3",g_hist,histSize);
	}

	waitKey(0);

	return 0;

}
