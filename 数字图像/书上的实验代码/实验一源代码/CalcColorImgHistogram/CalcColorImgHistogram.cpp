#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
void CalcHist_OpenCV(const Mat * image,Mat & b_hist,Mat & g_hist,Mat &r_hist,int histSize)
{
	/// Separate the image in 3 places ( B, G and R )
	vector<Mat> bgr_planes;
	split( *image, bgr_planes );
	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 256 } ;
	const float* histRange = { range };//the upper boundary is exclusive
	bool uniform = true; bool accumulate = false;

	/// Compute the histograms:
	calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
	calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
}
void CalcHist_ColorImg(const Mat * image,Mat & b_hist,Mat & g_hist,Mat &r_hist,int histSize)
{
	int nRows = image->rows;
	int nCols = image->cols;
	if (image->isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	b_hist = Mat::zeros(1,histSize, CV_32F);
	g_hist = Mat::zeros(1,histSize, CV_32F);
	r_hist = Mat::zeros(1,histSize, CV_32F);
	int i,j;
	const uchar* p;
	for( i = 0; i < nRows; ++i)
	{
		p = (*image).ptr<uchar>(i);
		for ( j = 0; j < nCols*3; j+=3)
		{
			b_hist.at<float>(p[j]/(256/histSize)) ++;
			g_hist.at<float>(p[j+1]/(256/histSize)) ++;
			r_hist.at<float>(p[j+2]/(256/histSize)) ++;
		}
	}
}
void CalcHist_ColorImg(unsigned char data[],float b_hist[],float g_hist[],float r_hist[],int dataSize,int histSize)
{
	int i;
	memset(b_hist,0,histSize*sizeof(float));
	memset(g_hist,0,histSize*sizeof(float));
	memset(r_hist,0,histSize*sizeof(float));
	for(i=0;i<dataSize;i+=3)
	{
		b_hist[data[i]/(256/histSize)] ++ ;
		g_hist[data[i+1]/(256/histSize)] ++ ;
		r_hist[data[i+2]/(256/histSize)] ++ ;
	}
}
void DrawHist(const string& winname,Mat & b_hist,Mat & g_hist,Mat &r_hist,int histSize)
{
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );

	Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	/// Normalize the result to [ 0, histImage.rows ]
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

	/// Draw for each channel
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
						Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
						Scalar( 255, 0, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
						Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
						Scalar( 0, 255, 0), 2, 8, 0  );
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
						Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
						Scalar( 0, 0, 255), 2, 8, 0  );
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
	Mat src, dst;

	/// Load image
	src = imread( argv[1], CV_LOAD_IMAGE_COLOR );

	if( !src.data )
	{ return -1; }

	/// Establish the number of bins
	int histSize = 256;
	Mat b_hist, g_hist, r_hist;
	CalcHist_OpenCV(&src,b_hist,g_hist,r_hist,histSize);
	DrawHist("calcColorImgHistogram1",b_hist,g_hist,r_hist,histSize);
	//////////////////////////////////////////////////////////////////////////////////////
	CalcHist_ColorImg(&src,b_hist,g_hist,r_hist,histSize);
	DrawHist("calcColorImgHistogram2",b_hist,g_hist,r_hist,histSize);
	/////////////////////////////////////////////////////////////////////////////////////
	if (src.isContinuous())
	{
		b_hist = Mat::zeros(1,histSize, CV_32F);
		g_hist = Mat::zeros(1,histSize, CV_32F);
		r_hist = Mat::zeros(1,histSize, CV_32F);
		CalcHist_ColorImg(src.data, (float*)(b_hist.data),(float*)(g_hist.data),(float*)(r_hist.data),src.cols*src.rows*3,histSize);
		DrawHist("calcColorImgHistogram3",b_hist,g_hist,r_hist,histSize);
	}

	// Binned Histogram
	histSize = 32;
	CalcHist_OpenCV(&src,b_hist,g_hist,r_hist,histSize);
	DrawHist("calcBinnedColorImgHistogram1",b_hist,g_hist,r_hist,histSize);
	//////////////////////////////////////////////////////////////////////////////////////
	CalcHist_ColorImg(&src,b_hist,g_hist,r_hist,histSize);
	DrawHist("calcBinnedColorImgHistogram2",b_hist,g_hist,r_hist,histSize);
	/////////////////////////////////////////////////////////////////////////////////////
	if (src.isContinuous())
	{
		b_hist = Mat::zeros(1,histSize, CV_32F);
		g_hist = Mat::zeros(1,histSize, CV_32F);
		r_hist = Mat::zeros(1,histSize, CV_32F);
		CalcHist_ColorImg(src.data, (float*)(b_hist.data),(float*)(g_hist.data),(float*)(r_hist.data),src.cols*src.rows*3,histSize);
		DrawHist("calcBinnedColorImgHistogram3",b_hist,g_hist,r_hist,histSize);
	}
	waitKey(0);

	return 0;
}
